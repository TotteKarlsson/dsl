#ifndef dslPropertiesContainerH
#define dslPropertiesContainerH
#include "dslObject.h"
#include "dslProperties.h"
#include "dslSharedPointer.h"
#include <list>
//---------------------------------------------------------------------------
namespace dsl
{

using std::list;

class DSL_COMMON PropertiesContainer : public DSLObject
{
    public:
                        							PropertiesContainer();
                        							~PropertiesContainer();
        void                                        append(dsl_shared_ptr<Properties> ps);
        dsl_shared_ptr<Properties>                      getSection(const string& s);
        bool                                        enableEdits();
        bool                                        disableEdits();
        bool                                        discardEdits();
        int                                         applyEdits();

    protected:
        list< dsl_shared_ptr<Properties> >  			mSections;
        list< dsl_shared_ptr<Properties> >::iterator 	mSectionIterator;
};

}


#endif
