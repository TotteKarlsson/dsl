
#pragma hdrstop
#include "dslDataProperties.h"


namespace dsl
{

dslDataProperties::dslDataProperties(int* rowSize, int* colSize)
:
rowDimSize(*rowSize),
colDimSize(*colSize),
rowBlockSize(0),
colBlockSize(0),
isModified(false),
isReadFromDisk(false),
autoScale(true)
{
}

dslAxesScaleProps::dslAxesScaleProps()
{
    scaleFactor = 1;
    autoScale = false;
}

}
