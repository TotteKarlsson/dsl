#ifndef dslDataProcessPropertiesH
#define dslDataProcessPropertiesH
#include <string>
#include "dslObject.h"
#include "DataExporter.h"

namespace dsl
{
using std::string;

class mtkPhasing;
class mtkProcessProperties;

class MTK_DATA mtkDataProcessProperties : public DSLObject
{
    public:
        mtkProcessProperties*               mRowDimProc;
        mtkProcessProperties*               mColDimProc;

	public:
										mtkDataProcessProperties();
										  ~mtkDataProcessProperties();
		void                                Read();
		void                                Read(const string& File);
		void                                Write(const string& File);
		void                                Write();

		mtkProcessProperties*               GetRowDimProperties(){return mRowDimProc;}
		mtkProcessProperties*               GetColDimProperties(){return mColDimProc;}
};

}
#endif
