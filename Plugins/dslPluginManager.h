#ifndef dslPluginManagerH
#define dslPluginManagerH
#include <vector>
#include <string>
#include <sstream>
#include <ostream>
#include <set>
#include <map>
#include <list>
#include "dslPluginsExporter.h"
#include "dslConstants.h"
#include "dslStringList.h"
#include "Poco/SharedLibrary.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::stringstream;
using std::string;
using std::vector;
using std::set;
using std::map;
using std::list;
using std::pair;
using std::ostream;
using dsl::gEmptyString;

using Poco::SharedLibrary;

class Plugin;
class PluginManager;
//! The Plugin is created after loading its SharedLibrary
typedef Poco::SharedLibrary* PluginLib;

//Convenient function pointers
typedef Plugin*     (*createPluginFunc)(PluginManager*);
typedef bool        (*destroyPluginFunc)(Plugin* );
typedef int         (*pluginObjectInstanceCountFunc)();

//Observe the difference between the PluginLib object and an instances of a created "Plugin", i.e. an instanc of a
//class defined by the plugin lib and created by calling the plugin lib function create()
//A client of the manager are not interested in the PluginLib itself, but the class instances, i.e. plugins, that the
//library provide..

class DSL_PLUGINS PluginManager
{
    public:
                                                    PluginManager(const string& pluginFolder = gPluginFolder, const string& plugin_prefix = gEmptyString);
    	virtual                                     ~PluginManager();

        virtual bool                                loadPlugin(const string& pluginName = gEmptyString);

                                                    //!Loading a plugin involve to load its shared lib, and execute
                                                    //!the plugins create function.
        virtual size_t                              loadPlugins();
        virtual bool                                unload(Plugin* plugin = nullptr);
        virtual bool                                unloadAll();
        virtual string                              getInfo() const;

        Plugin*                                     getPlugin(const string& pName);
        Plugin*                                     getPlugin(int i);
        StringList                                  getPluginNames() const;


        bool                                        setPluginDir(const string& dir);
        string                                      getPluginDir() const;
        size_t                                      getNumberOfPlugins() const;

        bool                                        hasLoadErrors() const;
        string                                      getLoadErrors() const;
        void                                        clearLoadErrors();
        string                                      getPluginPrefix();
        string                                      getPluginSuffix();
        void                                        setPluginPrefix(const string& p);
        void                                        setPluginSuffix(const string& s);

        DSL_PLUGINS friend ostream&                 operator<<(ostream& os, PluginManager& pm);

    protected:
        string                                      mPluginFolder;
        string                                      mPluginExtension;
        string                                      mPluginPrefix;
        string                                      mPluginSuffix;
        stringstream                                mLoadPluginErrors;

        virtual unsigned int                        loadPluginLibs(set<string>& files);
        virtual Plugin*                             createPlugin(const string& pluginLibName);

        StringList                                  getPluginLibsNames() const;
        PluginLib                                   getPluginLib(const string& name);
        PluginLib                                   getFirstPluginLib() const;
        PluginLib                                   getNextPluginLib() const;
        PluginLib                                   getPreviousPluginLib() const;
        PluginLib                                   getCurrentPluginLib() const;

        //Todo: create a structure, holding libName, lib and Plugin*
        //, and store in one container
        mutable map<string, PluginLib>              mPluginLibs;
        mutable map<string, PluginLib>::iterator    mPluginLibsIter;
        virtual bool                                loadPluginLib(const string& libName);

        mutable list< Plugin* >                     mPlugins;
        mutable list< Plugin* >::iterator           mPluginsIter;
};

}
#endif
