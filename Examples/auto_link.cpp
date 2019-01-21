#pragma hdrstop
//Link examples with the following libraries

#if defined(STATIC_DSL)
    #pragma comment(lib, "dslCommon-static.lib")
    #pragma comment(lib, "dslMath-static.lib")
    #pragma comment(lib, "dslDataBase-static.lib")
    #pragma comment(lib, "dslGraphics-static.lib")
    #pragma comment(lib, "dslMolecule-static.lib")
    #pragma comment(lib, "dslSpin-static.lib")
#else
    #pragma comment(lib, "dslCommon.lib")
    #pragma comment(lib, "dslDataBase.lib")
    #pragma comment(lib, "dslMath.lib")
    #pragma comment(lib, "dslGraphics.lib")
    #pragma comment(lib, "dslMolecule.lib")
#endif



