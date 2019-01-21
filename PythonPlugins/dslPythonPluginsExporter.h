#ifndef dslPythonPluginsExporterH
#define dslPythonPluginsExporterH

#if defined(_WIN32)
    #if defined(EXPORT_PYTHON_PLUGINS)
        #define DSL_PYTHONPLUGINS __declspec(dllexport)
    #else
        #define DSL_PYTHONPLUGINS __declspec(dllimport)
    #endif
#else
    #define DSL_PYTHONPLUGINS
#endif

#endif

