#ifndef dslCompilerSpecificsH
#define dslCompilerSpecificsH

#if defined(_MSC_VER)
#pragma warning(disable : 4996) // _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4018) // int to unsigned int comparison
#pragma warning(disable : 4482) // prefixing enums...
#pragma warning(disable : 4251) // _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4221) // empty cpp file

#define __FUNC__ __FUNCDNAME__
#define __func__ __FUNCDNAME__

#define getcwd _getcwd
#define snprintf _snprintf
#endif

#if defined(__BORLANDC__)
#pragma warn -8012             //comparing unsigned and signed
#pragma warn -8004             //variable never used
#endif


#endif
