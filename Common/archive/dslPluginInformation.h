#ifndef dslPluginInformationH
#define dslPluginInformationH
#include "dslCommonExporter.h"
#include "dslClassProperty.h"
#include <string>
//---------------------------------------------------------------------------

namespace dsl
{
using std::string;

class DSL_COMMON PluginInformation : public DSLObject
{
    public:
                                                    PluginInformation();
        virtual                                     ~PluginInformation();

        ClassProperty<string, PluginInformation>    Name;
        string                                      getName() const;
        void                                        setName(const string& s);

//        ClassProperty<string, PluginInformation>    LibraryName;
//        ClassProperty<string, PluginInformation>    Author;
//        ClassProperty<string, PluginInformation>    Category;
//        ClassProperty<string, PluginInformation>    Description;
//        ClassProperty<string, PluginInformation>    Hint;
//        ClassProperty<string, PluginInformation>    Version;
//        ClassProperty<string, PluginInformation>    Copyright;

    protected:
        string                                      mName;
        string                                      mLibraryName;
        string                                      mAuthor;
        string                                      mCategory;
        string                                      mDescription;
        string                                      mHint;
        string                                      mVersion;
        string                                      mCopyright;

};

}
#endif
