#ifndef dslPythonPluginManagerH
#define dslPythonPluginManagerH
#include "dslPluginManager.h"
#include "dslPythonPluginsExporter.h"
#include "dslPythonInterpreter.h"
//---------------------------------------------------------------------------

namespace dsl
{

class PythonPlugin;
class DSL_PYTHONPLUGINS PythonPluginManager : public PluginManager
{
    public:
    												PythonPluginManager(const string& pluginFolder = gPluginFolder, const string& plugin_prefix = gEmptyString);
    	virtual                                     ~PythonPluginManager();
		virtual string 								getInfo() const;
        virtual bool                                loadPlugin(const string& pluginName = gEmptyString);
        bool                                        assignInterpreter(PythonInterpreter* pi);
                                                    //!Loading a plugin involve to load its shared lib, and execute
                                                    //!the plugins create function.
        virtual int                                 loadPlugins();

		PythonPlugin* 			   					createBarePlugin(const string& dummyName);

		Plugin* 				   					createPlugin(const string& pluginLibName);
        virtual bool                                unload(Plugin* plugin = nullptr);
        virtual bool                                unloadAll();
        PythonInterpreter*       		            getPythonInterpreter();

    protected:
        virtual int                                 loadPluginLibs(set<string>& files);
        virtual bool                                loadPluginLib(const string& libFName);
        PythonInterpreter*                          mPI;
};

}
#endif
