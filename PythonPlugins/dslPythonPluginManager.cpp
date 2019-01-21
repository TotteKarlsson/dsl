#pragma hdrstop
#include "dslPythonPluginManager.h"
//#include "atATObject.h"
#include <iomanip>
#include "dslPlugin.h"
#include "Poco/Glob.h"
#include "dslLogger.h"
#include "dslUtils.h"
#include "dslFileUtils.h"
#include "dslException.h"
#include "dslPythonPlugin.h"
#include "dslPythonInterpreter.h"
//---------------------------------------------------------------------------

namespace dsl
{

using namespace std;
using Poco::SharedLibrary;
using Poco::Glob;

PythonPluginManager::PythonPluginManager(const string& pluginFolder, const string& plugin_prefix)
:
PluginManager(pluginFolder, plugin_prefix),
mPI(NULL)
{
    mPluginExtension = "py";
}

PythonPluginManager::~PythonPluginManager()
{}

bool PythonPluginManager::assignInterpreter(PythonInterpreter* pi)
{
    mPI = pi;
    return true;
}

PythonInterpreter* PythonPluginManager::getPythonInterpreter()
{
    return mPI;
}

bool PythonPluginManager::loadPlugin(const string& pluginName)
{
    return false;
}

int PythonPluginManager::loadPlugins()
{
	if(!mPI->isInitialized())
    {
        //Setup the python interperter
	    mPI->initialize();
    }

    set<string> files;
    string globPath =  joinPath(mPluginFolder, getPluginPrefix() + "*." + mPluginExtension);

    //Get all plugins in plugin folder
   	Glob::glob(globPath, files, Glob::GLOB_CASELESS);
    int i = loadPluginLibs(files);
    Log(lInfo) << "Found " << files.size() << " Python plugin " << (files.size() == 1 ? "library" : "libraries");

    //Try to create plugins
    mPluginLibsIter = mPluginLibs.begin();
    while(mPluginLibsIter != mPluginLibs.end())
    {
        string pLibName = (*mPluginLibsIter).first;
        Log(lDebug) <<"Creating plugin using library: "<<pLibName;

        Plugin* p = createPlugin(pLibName);
        if(p)
        {
            Log(lDebug) << "Created plugin: "<<p->getName();
        }
        else
        {
            Log(lError) << "Failed to create plugin from library: "<<pLibName;
        }
        ++mPluginLibsIter;
    }

    PyEval_ReleaseLock();
    return mPlugins.size();
}

PythonPlugin* PythonPluginManager::createBarePlugin(const string& dummyName)
{
    //Get a loaded plugin with name and call the createPlugin function
    PythonPlugin* pPlugin(NULL);

    //Python plugins are dynamically allocated using the PythonPlugin class that 'manages' the Python execution
    pPlugin = dynamic_cast<PythonPlugin*>(dsl::createPlugin(this));

    //Use the pluginLib container to store plugin pointers for Python plugins
    mPluginLibs[dummyName] = (SharedLibrary*) pPlugin;
    mPlugins.push_back(pPlugin);

    return pPlugin;
}

Plugin* PythonPluginManager::createPlugin(const string& pLibName)
{
    //Get a loaded plugin with name and call the createPlugin function
    Plugin* thePlugin = (Plugin*) getPluginLib(pLibName);
    PythonPlugin* pPlugin(NULL);
    if(!thePlugin)
    {
        //Python plugins are dynamically allocated using the PythonPlugin class that 'manages' the Python execution
        pPlugin = dynamic_cast<PythonPlugin*>(dsl::createPlugin(this));

        //Execute some Python code to populate plugin information
        //Put this in a thread later, and use the GIL for python
        try
        {
            PyObject* pyModule 				= mPI->loadModule(pLibName);
            if(!pyModule)
            {
                throw(DSLException(string("Failed to load Python module: ") + pLibName));
            }

            pPlugin->assignPyModule(pyModule);
            PyObject* f					 	= mPI->setupFunction(pyModule, "createPluginMetaData");
            PyObject* res 					= mPI->executeFunction(f, pPlugin);

            //We may check return values later on..
            Py_DecRef(f);
            Py_DecRef(res);

            //Then the properties
            f							 	= mPI->setupFunction(pyModule, "createPluginProperties");
            res								= mPI->executeFunction(f, pPlugin);
            Py_DecRef(f);
            Py_DecRef(res);

 	        PyObject* execute 	 			=  mPI->setupFunction(pyModule, "execute");
            if(execute)
            {
            	pPlugin->assignExecuteFunction(execute);
            }
            else
            {
                Log(lError) << "This plugin don't have an execute function! Disaster..!";
            }

            //Use the pluginLib container to store plugin pointers for Python plugins
            mPluginLibs[pLibName] = (SharedLibrary*) pPlugin;
            mPlugins.push_back(pPlugin);
            pPlugin->setLibraryName(getFileNameNoExtension(pLibName));
        }
        catch(const DSLException& e)
        {
            Log(lError) << "Exception: " << e.what();
            delete pPlugin;
            pPlugin = NULL;
        }
        catch(...)
        {
            Log(lError) << "Some bad stuff is going on..";
        }
    }
    else
    {
        Log(lWarning) << "The plugin: " << pLibName << " is already created.";
    }

    return pPlugin;
}

int PythonPluginManager::loadPluginLibs(set<string>& files)
{
    int nrOfLoadedPlugins = 0;
    clearLoadErrors();
    stringstream errors;

    //Throw if plugin folder don't exist
    if(!folderExists(mPluginFolder))
    {
        errors<<"The plugin folder: \""<<mPluginFolder<<"\" do not exist..";
        Log(lDebug)<<errors.str();
        mLoadPluginErrors << errors.str();
        throw(DSLException(errors.str()));
    }

    set<string>::iterator it = files.begin();
    //Try to load.. failing to load a plugin do not mean we abort. Catch and report the problem
    for (; it != files.end(); ++it)
    {
        string pluginFName = getFileNameNoPath(*it);
        Log(lInfo)<<"Loading plugin: "<<pluginFName;
        try
        {
            bool res = loadPluginLib(pluginFName);
            if(!res)
            {
                Log(lError)<<"There was a problem loading the plugin with fileName: "<<pluginFName;
                continue;
            }
            nrOfLoadedPlugins++;
        }
        catch(...)
        {
            Log(lError)<<"There was a serious problem loading the plugin: "<<pluginFName;
        }
    }
    return nrOfLoadedPlugins;
}

bool PythonPluginManager::loadPluginLib(const string& libFName)
{
    //This is a private function that catches any throws occuring
    //Catch and save the error message below, in the catch
    stringstream info;
    try
    {
        string libName(libFName);

        //Check if Plugin is already loaded first
        if(getPluginLib(libName))
        {
            info<<"The Plugin: "<<libName<<" is already loaded";
            Log(lWarning)<<info.str();
            return true;
        }

        if(!hasFileExtension(libName))
        {
            libName = libFName + ".py";
        }

        string fullName = joinPath(mPluginFolder, libName);

        if(!fileExists(fullName))
        {
            info<<"The plugin: "<<fullName<<" could not be found";
            throw(info.str());
        }

        //Add plugin to map
        mPluginLibs[getFileNameNoExtension(libFName)] = NULL;
        //Success..
        return true;
    }
    catch(const string& msg) //We have to catch exceptions here. Failing to load a plugin should not throw, just return false.
    {
        info<<"========== In attempt to load plugin: "<<libFName<<" ==========="<<endl;
        info<<"Plugin loading exception: "<<msg;
        mLoadPluginErrors<<info.str();
        Log(lError)<<info.str();
        return false;
    }
    catch(const DSLException& e)
    {
        info<<"========== In attempt to load plugin: "<<libFName<<" ==========="<<endl;
        info<<"DSLException: "<<e.what()<<endl;
        mLoadPluginErrors<<info.str();
        Log(lError)<<info.str();
        return false;
    }
    catch(...)
    {
        info<<"========== In attempt to load plugin: "<<libFName<<" ==========="<<endl;
        info<<"Unknown error occured attempting to load plugin"<<libFName;
        mLoadPluginErrors<<info.str();
        Log(lError)<<info.str();
        return false;
    }
}

string PythonPluginManager::getInfo() const
{
    stringstream info;
    info<<setw(50)<<left<<"Plugin Folder: "                    <<mPluginFolder<<"\n";
    info<<setw(50)<<left<<"Plugin Extensions: "                <<mPluginExtension<<"\n";
    info<<setw(50)<<left<<"Plugin Prefix: "                    <<mPluginPrefix<<"\n";
    info<<setw(50)<<left<<"Number of loaded plugins:"          <<getNumberOfPlugins()<<"\n";
    info<<setw(50)<<left<<"Number of created plugin objects:"  <<mPlugins.size()<<"\n";
    if(getNumberOfPlugins())
    {
        info<<setw(25)<<left<<"Plugin Libraries"<<"\n";
        mPluginLibsIter = mPluginLibs.begin();
        while(mPluginLibsIter != mPluginLibs.end())
        {
            PythonPlugin* pp = (PythonPlugin*) ((*mPluginLibsIter).second);
            info << "  "<<setw(25) << left << mPluginFolder << "\n";
            ++mPluginLibsIter;
        }
    }
    return info.str();
}

bool PythonPluginManager::unloadAll()
{
    //This involves destructing each PluginObject and their host library

    //First all plugin objects
    bool result(true);
    mPluginsIter = mPlugins.begin();
    while(mPluginsIter != mPlugins.end())
    {
        result = false;
        Plugin* p = (*mPluginsIter);
        pluginObjectInstanceCountFunc pic = nullptr;
        if(p)
        {
            list< Plugin* >::iterator toErase = mPluginsIter;
            ++mPluginsIter;
            mPlugins.erase(toErase);
        }
        else
        {
            Log(lError) << "Bad stuff going on in plugin container!";
           ++mPluginsIter;
        }
    }

    //Now unload the DLL libraries
    mPluginLibsIter = mPluginLibs.begin();
    while(mPluginLibsIter != mPluginLibs.end())
    {
        Log(lInfo) <<"Unloading: "<<(*mPluginLibsIter).first;

        //Todo: check if there are plugin instances before deleting..

        map<string, PluginLib>::iterator toErase = mPluginLibsIter;
        ++mPluginLibsIter;
        mPluginLibs.erase(toErase);
    }

    return true;
}

bool PythonPluginManager::unload(Plugin* plugin)
{
    if(!plugin)
    {
        return unloadAll();
    }

    bool result(false);
//    int nrPlugins = getNumberOfPlugins();
//
//    for(vector< dslPlugin >::iterator it = mPluginLibs.begin(); it != mPluginLibs.end(); it++)
//    {
//        dslPlugin *aPluginLib = &(*it);
//        if(aPluginLib)
//        {
//            SharedLibrary *pluginLibHandle    = aPluginLib->first;
//            Plugin        *aPlugin            = aPluginLib->second;
//
//            if(aPlugin == plugin)
//            {
//                destroyPlugin(aPlugin);
//
//                plugin = nullptr;
//                //Then unload
//                if(pluginLibHandle)
//                {
//                    pluginLibHandle->unload();
//                    //Research this delete pluginLibHandle;
//                }
//
//                //And remove from container
//                aPluginLib->first = nullptr;
//                aPluginLib->second = nullptr;
//                aPluginLib = nullptr;
//
//                //Reset the plugins iterator to a valid one
//                mPluginLibsIter = mPluginLibs.erase(it);
//                result = true;
//                break;
//            }
//        }
//    }
    return result;
}


}
