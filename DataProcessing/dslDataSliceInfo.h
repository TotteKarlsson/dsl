#ifndef dslDataSliceInfoH
#define dslDataSliceInfoH
#include "dslObject.h"
#include "DataExporter.h"

namespace dsl
{

template <class T>
class mtkVector;
class MTK_DATA mtkDataSliceInfo : DSLObject
{
	public:
		mtkDataSliceInfo();
		~mtkDataSliceInfo();
		int sliceNrStart;
		int sliceNrEnd;
		int sliceIncrement;
		mtkVector<int>* GetSlices();
		void SetNumberOfSlices(int nrOfSlices);

	private:
		mtkVector<int>* slices;
};

}
#endif
