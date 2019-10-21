#ifndef dslSharedPointerH
#define dslSharedPointerH

#if defined(__BORLANDC__) && !defined(__clang__)
    #include <boost/tr1/memory.hpp>
	#include <boost/make_shared.hpp>
    using std::tr1::shared_ptr;
#elif defined(_MSC_VER)
	#include <memory>
	using std::shared_ptr;
#elif defined(__clang__)
    #include <memory>
    using std::shared_ptr;
#endif


#endif
