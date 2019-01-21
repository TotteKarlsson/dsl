#if defined(DSL_STATIC)
	#pragma comment(lib, "dslCommon-static.lib")
#else
	#pragma comment(lib, "dslCommon.lib")
#endif


#pragma comment(lib, "poco_foundation-static")
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "libcurl.lib")

#if defined(DSL_STATIC)
	#pragma link "vcl.lib" //Checklst
	#pragma link "vclx.lib" //Checklst
	#pragma link "vclactnband.lib"
#else
	#pragma link "vclx.bpi" //Checklst
	#pragma link "vclactnband.bpi"
#endif
