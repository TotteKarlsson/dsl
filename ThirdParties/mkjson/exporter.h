#ifndef mkjsonExporterH
#define mkjsonExporterH

#if defined (_WIN32)
	#if defined(MKJSON_STATIC)
		#define MKJSON_API
	#else
		#if defined(EXPORT_MKJSON)
			#define MKJSON_API __declspec(dllexport)
		#else
			#define MKJSON_API __declspec(dllimport)
		#endif
	#endif
#else
	#define MKJSON_API
#endif

#endif
