#ifndef dslVCLCommonExporterH
#define dslVCLCommonExporterH

///////////////////////////////////////////////////////////////

#if defined (_WIN32)
	#if defined(VCLCOMMON_STATIC)
		#define VCLCOMMON
	#else
		#if defined(EXPORT_VCLCOMMON)
			#define VCLCOMMON __declspec(dllexport)
		#else
			#define VCLCOMMON __declspec(dllimport)
		#endif
	#endif
#else
	#define VCLCOMMON
#endif

#pragma warn -8118
#endif
