#ifndef MathExporterH
#define MathExporterH

#if defined (_WIN32)
#if defined(DSL_STATIC)
    #define DSL_MATH
#else
    #if defined(EXPORT_MATH)
        #define DSL_MATH __declspec(dllexport)
    #else
        #define DSL_MATH __declspec(dllimport)
    #endif
	#endif
#else
	#define DSL_MATH
#endif

#endif
