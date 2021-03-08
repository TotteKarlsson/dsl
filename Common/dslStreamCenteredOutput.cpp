#pragma hdrstop
#include "dslStreamCenteredOutput.h"
//---------------------------------------------------------------------------
namespace dsl
{

StreamCenteredOutput centered(const string& str)
{
    return StreamCenteredOutput(str);
}

StreamCenteredOutput::StreamCenteredOutput(const std::string& str)
: strVal(str)
{}

dsl::uint StreamCenteredOutput::width() const
{
    return strVal.size();
}

std::ostream& operator<<(std::ostream& s, const dsl::StreamCenteredOutput& c)
{
    std::streamsize w = s.width();
    if (w > c.width())
    {
        std::streamsize left = (w + c.width()) / 2;
        s.width(left);
        s << c.strVal;
        s.width(w - left);
        s << "";
    }
    else
    {
        s << c.strVal;
    }
    return s;
}

}





