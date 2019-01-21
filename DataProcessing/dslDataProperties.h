#ifndef dslDataPropertiesH
#define dslDataPropertiesH
#include "dslObject.h"
#include "DataExporter.h"

namespace dsl
{

class MTK_DATA mtkAxesScaleProps : public DSLObject
{
    public:
                    mtkAxesScaleProps();
        double         scaleFactor;
        bool         autoScale;
};

class MTK_DATA mtkDataProperties : public DSLObject
{
	public:
                            mtkDataProperties(int* rowSize, int* colSize);
        bool                 isModified;
        bool                 isReadFromDisk;
        bool                 isSaved;

        int&                rowDimSize;
        int&                colDimSize;
        int                 rowBlockSize;
        int                 colBlockSize;
        bool                 autoScale;
        mtkAxesScaleProps   leftAxis;
        mtkAxesScaleProps   rightAxis;
        mtkAxesScaleProps   bottomAxis;
        mtkAxesScaleProps   topAxis;

	private:
};

}
#endif

