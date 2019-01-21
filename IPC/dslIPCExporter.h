#ifndef IPCExporterH
#define IPCExporterH

#if defined(DSL_STATIC)
    #define DSL_IPC
#else
    #if defined(EXPORT_IPC)
        #define DSL_IPC __declspec(dllexport)
    #else
        #define DSL_IPC __declspec(dllimport)
    #endif
#endif

#endif
