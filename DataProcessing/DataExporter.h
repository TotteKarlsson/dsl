#ifndef DataExporterH
#define DataExporterH

#if defined(DSL_STATIC)
    #define MTK_DATA
#else
    #if defined(EXPORT_DATA)
        #define MTK_DATA __declspec(dllexport)
    #else
        #define MTK_DATA __declspec(dllimport)
    #endif
#endif

#endif
