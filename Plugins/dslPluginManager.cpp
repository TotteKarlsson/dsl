#pragma hdrstop
#include "dslPluginManager.h"
#include "dslPlugin.h"
#include "dslLogger.h"
#include "dslException.h"
#include "dslUtils.h"
#include "dslFileUtils.h"
#include "Poco/Glob.h"
#include <iomanip>
//---------------------------------------------------------------------------

namespace dsl
{

using namespace std;
using Poco::SharedLibrary;
using Poco::Glob;

static const char*  getPluginLibsExtension();
static const char*  getOSPlatformPluginPrefix();

#if defined(__BORLANDC__)
    #define exp_fnc_prefix "_"
#else
    #define exp_fnc_prefix ""
#endif

class DSL_PLUGINS PluginMissingSymbolException : public DSLException
{
    public:
    	PluginMissingSymbolException(const string& msg);
};

PluginMissingSymbolException::PluginMissingSymbolException(const string& msg)
:
DSLException(msg)
{}

bool destroyPlugin(Plugin *plugin);

PluginManager::PluginManager(const std::string& folder, const string& plugin_prefix)
:
mPluginFolder(folder),
mPluginExtension(getPluginLibsExtension()),
mPluginPrefix(plugin_prefix)
{}

PluginManager::~PluginManager()
{
    unloadAll();
}

bool PluginManager::setPluginDir(const string& dir)
{
    mPluginFolder = dir;
    return folderExists(mPluginFolder);
}

string PluginManager::getPluginDir() const
{
    return mPluginFolder;
}

string PluginManager::getPluginPrefix()
{
    return mPluginPrefix;
}

string PluginManager::getPluginSuffix()
{
    return mPluginSuffix;
}

void PluginManager::setPluginPrefix(const string& p)
{
    mPluginPrefix = getOSPlatformPluginPrefix() + p;
}

void PluginManager::setPluginSuffix(const string& s)
{
    mPluginSuffix = s;
}

string PluginManager::getInfo() const
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
            PluginLib pl = (*mPluginLibsIter).second;
            info<<"  "<<setw(25)<<left<< getFileNameNoExtension(pl->getPath())<<"\n";
            ++mPluginLibsIter;
        }
    }
    return info.str();
}

StringList PluginManager::getPluginNames() const
{
    StringList names;
    mPluginsIter = mPlugins.begin();
    while(mPluginsIter != mPlugins.end())
    {
        names.append((*mPluginsIter)->getName());
        ++mPluginsIter;
    }
    return names;

}

PluginLib PluginManager::getFirstPluginLib() const
{
    mPluginLibsIter = mPluginLibs.begin();
    if(mPluginLibsIter != mPluginLibs.end())
    {
        return (*mPluginLibsIter).second;
    }
    return nullptr;
}

PluginLib PluginManager::getCurrentPluginLib() const
{
    if(mPluginLibsIter != mPluginLibs.end())
    {
        return (*mPluginLibsIter).second;
    }
    return nullptr;
}

PluginLib PluginManager::getNextPluginLib() const
{
    if(mPluginLibsIter != mPluginLibs.end())
    {
        mPluginLibsIter++;
        if(mPluginLibsIter != mPluginLibs.end())
        {
            return (*mPluginLibsIter).second;
        }
    }
    return nullptr;
}

PluginLib PluginManager::getPreviousPluginLib() const
{
    if(mPluginLibsIter != mPluginLibs.end())
    {
        mPluginLibsIter--;
        if(mPluginLibsIter != mPluginLibs.end())
        {
            return (*mPluginLibsIter).second;
        }
    }
    return nullptr;
}

Plugin* PluginManager::getPlugin(const string& pName)
{
    //Plugins are stored in a list -> iterate through this list
    mPluginsIter = mPlugins.begin();
    int j = 0;

    while(mPluginsIter != mPlugins.end())
    {
        Plugin* p =  *(mPluginsIter) ;
        if(p && (p->getName() == pName))
        {
            return p;
        }

        j++;
    }

    return nullptr;
}

Plugin* PluginManager::getPlugin(int i)
{
    //Plugins are stored in a list -> iterate through this list
    mPluginsIter = mPlugins.begin();
    int j = 0;
    while(mPluginsIter != mPlugins.end())
    {
        if(j == i)
        {
            return *(mPluginsIter);
        }
        ++mPluginsIter;
        j++;
    }

    return nullptr;
}

Plugin* PluginManager::createPlugin(const string& pLibName)
{
    //Get a loaded plugin with name and call the createPlugin function
    PluginLib pLib = getPluginLib(pLibName);
    if(!pLib)
    {
        //Try to load
        if(!loadPluginLib(pLibName))
        {
            return nullptr;
        }
        else
        {
            pLib = getPluginLib(pLibName);
        }

        if(!pLib)
        {
            return nullptr;
        }
    }

    //Create a new plugin
    createPluginFunc create = (createPluginFunc) pLib->getSymbol(string(exp_fnc_prefix) + "createPlugin");

    //Execute the create function
    Plugin* aPlugin = create(this);
    if(aPlugin)
    {
        aPlugin->setLibraryName(getFileNameNoExtension(pLibName));
        mPlugins.push_back(aPlugin);
    }
    return aPlugin;
}

bool PluginManager::loadPlugin(const string& pluginName)
{
    stringstream errors;
    //Throw if plugin folder don't exist
    if(!folderExists(mPluginFolder))
    {
        errors<<"The plugin folder: \""<<mPluginFolder<<"\" do not exist..";
        Log(lError)<<errors.str();
        mLoadPluginErrors << errors.str();
        throw(DSLException(errors.str()));
    }

    Log(lInfo)<<"Loading plugin: "<<pluginName;
    try
    {
        if(!loadPluginLib(pluginName))
        {
            Log(lError)<<"There was a problem loading the plugin: "<<pluginName;
            return false;
        }
    }
    catch(...)
    {
        Log(lError)<<"There was a problem loading the plugin: "<<pluginName;
    }

    return true;
}

//Returns number of succesfully loaded & created plugins
size_t PluginManager::loadPlugins()
{
    set<string> files;
    string globPath =  joinPath(mPluginFolder, getPluginPrefix() + "*." + mPluginExtension);

    //Get all plugins in plugin folder
    Glob::glob(globPath, files, Glob::GLOB_CASELESS);
    int i = loadPluginLibs(files);
    Log(lInfo) << "Found " << i << " plugin libraries";

    //Try to create plugins
    mPluginLibsIter = mPluginLibs.begin();
    while(mPluginLibsIter != mPluginLibs.end())
    {
        string pLibName = (*mPluginLibsIter).first;
        Log(lDebug) <<"Creating plugin using library: "<<(*mPluginLibsIter).first;

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
    return (unsigned int) mPlugins.size();
}

unsigned int PluginManager::loadPluginLibs(set<string>& files)
{
    unsigned int nrOfLoadedPlugins = 0;
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
                Log(lError)<<"There was a problem loading the plugin: "<<pluginFName;
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

bool PluginManager::loadPluginLib(const string& lib)
{
    //This is a private function that catches any throws occuring
    //Catch and save the error message below, in the catch
    stringstream info;
    try
    {
        string libName(lib);

        //Check if Plugin is already loaded first
        if(getPluginLib(libName))
        {
            info<<"The Plugin: "<<libName<<" is already loaded";
            Log(lWarning)<<info.str();
            return true;
        }

        //Clients don't have to supply extension, different on different platforms
        if(!hasFileExtension(libName))
        {
            libName = lib + "." + getPluginLibsExtension();
        }
        string fullName = joinPath(mPluginFolder, libName);

        if(!fileExists(fullName))
        {
            info<<"The plugin library: "<<fullName<<" could not be found";
            throw(info.str());
        }

        //Remember to de allocate this one
        SharedLibrary *libHandle = new SharedLibrary;

        //This one throws at a lower level if there is a problem..
        libHandle->load(fullName);

        //Validate the plugin
        if(!libHandle->hasSymbol(string(exp_fnc_prefix) + "createPlugin"))
        {
            libHandle->unload();
            throw(PluginMissingSymbolException("The plugin is missing the createPlugin(void*) function!"));
        }

        //Validate the plugin
        if(!libHandle->hasSymbol(string(exp_fnc_prefix) + "destroyPlugin"))
        {
            libHandle->unload();
            throw("The plugin is missing the destroyPlugin(Plugin*) function!");
        }

        mPluginLibs[getFileNameNoExtension(lib)] = libHandle;

        //Success..
        return true;
    }
    catch(const string& msg) //We have to catch exceptions here. Failing to load a plugin should not throw, just return false.
    {
        info<<"========== In attempt to load plugin: "<<lib<<" ==========="<<endl;
        info<<"Plugin loading exception: "<<msg;
        mLoadPluginErrors<<info.str();
        Log(lError)<<info.str();
        return false;
    }
    catch(const PluginMissingSymbolException& e)
    {
        info<<"========== In attempt to load plugin: "<<lib<<" ==========="<<endl;
        info<<"PluginMissingSymbolException: "<<e.what()<<endl;
        mLoadPluginErrors<<info.str();
        Log(lError)<<info.str();
        return false;
    }
    catch(const DSLException& e)
    {
        info<<"========== In attempt to load plugin: "<<lib<<" ==========="<<endl;
        info<<"DSLException: "<<e.what()<<endl;
        mLoadPluginErrors<<info.str();
        Log(lError)<<info.str();
        return false;
    }
    catch(const Poco::Exception& ex)
    {
        info<<"========== In attempt to load plugin: "<<lib<<" ==========="<<endl;
        info<<"POCO DSLException: "<<ex.displayText()<<endl;
        mLoadPluginErrors<<info.str();
        Log(lError)<<info.str();
        return false;
    }
    catch(...)
    {
        info<<"========== In attempt to load plugin: "<<lib<<" ==========="<<endl;
        info<<"Unknown error occured attempting to load plugin"<<lib;
        mLoadPluginErrors<<info.str();
        Log(lError)<<info.str();
        return false;
    }
}

bool PluginManager::unloadAll()
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
            p->terminate(true);
            //Get the destroyPlugin function and call it
            string pLibName = p->getLibraryName();
            PluginLib pl = getPluginLib(pLibName);
            if(pl)
            {
                //Destroy a  plugin
                destroyPluginFunc destroy = (destroyPluginFunc) pl->getSymbol(string(exp_fnc_prefix) + "destroyPlugin");
                result = destroy(p);
            }
        }

        if(result)
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
        delete (*mPluginLibsIter).second;

        map<string, PluginLib>::iterator toErase = mPluginLibsIter;
        ++mPluginLibsIter;
        mPluginLibs.erase(toErase);
    }

    return true;
}

bool PluginManager::unload(Plugin* plugin)
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

PluginLib PluginManager::getPluginLib(const string& libName)
{
    //Clients don't have to supply extension, different on different platforms
    string fName(libName);
    if(hasFileExtension(fName))
    {
        fName = getFileNameNoExtension(fName);
    }

    return mPluginLibs[fName];
}

StringList PluginManager::getPluginLibsNames() const
{
    StringList names;
    for(mPluginLibsIter = mPluginLibs.begin(); mPluginLibsIter != mPluginLibs.end(); mPluginLibsIter++)
    {
        names.append((*mPluginLibsIter).first);
    }

    return names;
}

size_t PluginManager::getNumberOfPlugins() const
{
    return mPluginLibs.size();
}

bool PluginManager::hasLoadErrors() const
{
    return mLoadPluginErrors.str().size() != 0 ? true : false;
}

string PluginManager::getLoadErrors() const
{
    return mLoadPluginErrors.str();
}

void PluginManager::clearLoadErrors()
{
    mLoadPluginErrors.str("");
}

const char* getPluginLibsExtension()
{
    #if defined(_WIN32)
        return "dll";
    #elif defined(__linux__)
        return "so";
    #else
        // OSX
        return "dylib";
    #endif
}

const char* getOSPlatformPluginPrefix()
{
    #if defined(_WIN32)
        return "";
    #elif defined(__linux__)
        return "lib";
    #else
        return "DEFINE_PLATFORM";
    #endif
}

ostream& operator << (ostream& st, PluginManager& pm)
{
    st<<pm.getInfo();
    return st;
}


//bool hasFileExtension(const string& fName)
//{
//    return (fName.find_last_of(".") != string::npos) ? true : false;
//}

}
