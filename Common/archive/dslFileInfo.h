#ifndef dslFileInfoH
#define dslFileInfoH
#include "dslConstants.h"
#include "dslObject.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_COMMON FileInfo : public DSLObject
{
	public:
									FileInfo(const DATA_FORMAT& dF = dfMoleculix, const FILE_FORMAT& fF = ffASCII);
		FileInfo&                 	operator = (const FileInfo& fN);

		void         				SetDataFormat(const DATA_FORMAT& dF);
		DATA_FORMAT  				GetDataFormat() const ;

		void         				SetFileFormat(const FILE_FORMAT& fF);
		FILE_FORMAT				    GetFileFormat() const ;

	private:
		DATA_FORMAT                 mDataFormat;
		FILE_FORMAT                 mFileFormat;
};

}
#endif
