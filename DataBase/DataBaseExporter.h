#ifndef DataBaseExporterH
#define DataBaseExporterH

#if defined(DSL_STATIC)
    #define DSL_DB
#else
    #if defined(EXPORT_DATABASE)
        #define DSL_DB __declspec(dllexport)
    #else
        #define DSL_DB __declspec(dllimport)
    #endif

    #if defined(PACKAGED_DATABASE)
        #define DSL_DB __declspec(package)
    #endif

#endif

//Forward declarations;
struct sqlite3;
struct sqlite3_stmt;
#if defined(_WIN32)
	typedef __int64 sqlite_int64;
#elif defined(__GNUC__)
	typedef long long sqlite_int64;
#elif defined(__APPLE__)
	typedef long long sqlite_int64;

#endif

////////////////////////////////////////////////////////////////////////////////////
////// Prototypes for SQLite functions not included in SQLite DLL, but copied below
////// from SQLite encode.c
////////////////////////////////////////////////////////////////////////////////////

namespace dsl
{
int sqlite3_encode_binary(const unsigned char *in, int n, unsigned char *out);
int sqlite3_decode_binary(const unsigned char *in, unsigned char *out);
}

//disable warnings on extern before template instantiation
#define CPPSQLITE_ERROR 1000
static const bool DONT_DELETE_MSG=false;
#pragma warning (disable : 4231)

#endif
