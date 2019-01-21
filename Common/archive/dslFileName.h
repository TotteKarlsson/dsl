#ifndef dslFileNameH
#define dslFileNameH
#include "dslObject.h"
#include "dslConstants.h"
#include "dslCommonExporter.h"
#include <string>
#include <ostream>
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;
using std::ostream;

class DSL_COMMON FileName : public DSLObject
{
	public:
                                    FileName(const string& name = gEmptyString, const string& path = gEmptyString);
                                    FileName(const FileName& fN);
                                   ~FileName();
        FileName&					operator = (const FileName& fN);
        FileName&					operator = (const string& fN);
        FileName&					operator = (const char* fN);
        bool                        operator !=(const char* fN);
                                    operator string();// {return mPathAndName;}
        bool                        setPath(const string& path);
        void                        setFileName(const string& name);
        void                        setNameAndPath(const string& path, const string& name);
        void                        setFileNameAndPath(const string& name);

        string                      getFileName() const;
        string                      getPath() const;
        const string                getPathAndFileName() const;
        string                      get();
        string                      getFileNameNoExtension() const;
        uint                        size();

	private:
        mutable string              mPathAndName;
        string                      mPath;
        string                      mName;
        void                        makeFileString();
};

DSL_COMMON std::ostream& operator         <<(std::ostream &os, FileName &obj);

}
#endif
