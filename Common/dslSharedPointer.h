#ifndef dslSharedPointerH
#define dslSharedPointerH

//Borland old compiler is using boost shared pointers :(

#if defined(__BORLANDC__) && !defined(__clang__)

    #include <boost/tr1/memory.hpp>
	#include <boost/make_shared.hpp>
    #define dsl_shared_ptr std::tr1::shared_ptr
    #define dsl_dynamic_pointer_cast boost::dynamic_pointer_cast

#elif defined(_MSC_VER) || defined (__clang__)

	#include <memory>
	#define dsl_shared_ptr std::shared_ptr
    #define dsl_dynamic_pointer_cast std::dynamic_pointer_cast

#endif


#endif
