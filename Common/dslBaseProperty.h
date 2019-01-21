#ifndef dslBasePropertyH
#define dslBasePropertyH
#include "dslObject.h"
#include "dslIniFile.h"
#include "dslStringUtils.h"
#include "dslCommonExporter.h"
#include "dslTypeInfo.h"
#include <string>
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;
using std::ostream;
class IniFile;

//abstract class for inifile parameters
//a non template base class allow us to store derived objects,
//of any type, in a vector for example
class DSL_COMMON BaseProperty : public DSLObject
{
	public:
                                                        BaseProperty();
                                                        BaseProperty(const string& lbl);
        virtual                                         ~BaseProperty();

        //Interface
        virtual string                                  getINIRecord() {return string("Setup in baseclass!");}
        virtual bool                                    assignValueFromString(const string& val) = 0;
        virtual string                                  getLabel() = 0;
        virtual string                                  getValueAsString() const = 0;
        virtual void*                                   getValueHandle() = 0;
        virtual void*                                   getEditValueHandle() = 0;

        virtual ObjectType                              getPropertyType() = 0;
        virtual bool                                    read(IniFile* iniFile, const string& section) = 0;
        virtual bool                                    write(IniFile* iniFile, const string& section) = 0;

        virtual const char*                             c_str() const;

        //Utilities
        bool					                        doReadFromINI();
        bool					                        wasRead();
        bool					                        wasWritten();

                                                        //Modification idea is when we are using setting forms and OK, Cancel button
        bool                                            setEditMode(bool val);
        virtual void                                    applyEdit() = 0;

                                                        //Sets modified flag to false
        void                   			                discardEdit();
        bool                                            isInEditMode();
        void					                        setModified();
        bool					                        isModified();

	protected:
                                                        //In Edit mode, a properties value is not modified,
                                                        //but only its temporary value. A properties temporary
                                                        //value is copied to its value by calling the applyEdit() function.
        bool                                            mIsInEditMode;
        bool  					                        mIsModified;
        bool  					                        mDoReadFromINI;
        bool  					                        mWasRead;
        bool  					                        mWasWritten;

        string			                                mKey;
        string					                        mComment;
        string					                        mHint;
};

}
#endif
