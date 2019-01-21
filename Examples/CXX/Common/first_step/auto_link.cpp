
#if defined(DSL_STATIC)
    #pragma comment(lib, "dslCommon-static.lib")
#else
    #if defined(SRTL)
        #pragma comment(lib, "dslCommon-srtl.lib")
    #else
        #pragma comment(lib, "dslCommon.lib")
    #endif
#endif

