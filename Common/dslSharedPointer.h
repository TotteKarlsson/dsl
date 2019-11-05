#ifndef dslSharedPointerH
#define dslSharedPointerH

#if defined(__BORLANDC__) && !defined(__clang__)
    #include <boost/tr1/memory.hpp>
	#include <boost/make_shared.hpp>
    #define dsl_shared_ptr std::tr1::shared_ptr

#elif defined(_MSC_VER) || defined (__clang__)
	#include <memory>
	#define dsl_shared_ptr std::shared_ptr

#endif


#endif
