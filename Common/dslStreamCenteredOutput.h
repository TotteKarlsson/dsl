#ifndef dslStreamCenteredOutputH
#define dslStreamCenteredOutputH
#include "dslCommonExporter.h"
#include <iomanip>
#include <iostream>
#include <string>
#include "dslConstants.h"
//---------------------------------------------------------------------------
namespace dsl
{

using std::string;

class StreamCenteredOutput;

DSL_COMMON StreamCenteredOutput centered(const string& str);

class DSL_COMMON StreamCenteredOutput
{
    friend
    DSL_COMMON std::ostream& operator<<(std::ostream& s, const dsl::StreamCenteredOutput& c);
    //std::ostream& operator<<(std::ostream& s, const StreamCenteredOutput& c);


    public:
        StreamCenteredOutput(const std::string& str);
        dsluint width() const;

    private:
        string strVal;
};

}



#endif
