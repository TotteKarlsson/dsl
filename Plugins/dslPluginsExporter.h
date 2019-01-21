#ifndef dslPluginsExporterH
#define dslPluginsExporterH

#if defined(_WIN32)
    #if defined(EXPORT_PLUGINS)
        #define DSL_PLUGINS __declspec(dllexport)
    #else
        #define DSL_PLUGINS __declspec(dllimport)
    #endif
#else
    #define DSL_PLUGINS
#endif

#endif

