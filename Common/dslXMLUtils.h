#ifndef dslXMLUtilsH
#define dslXMLUtilsH
#include "dslCommonExporter.h"
#include "dslUtils.h"
#include "tinyxml2/tinyxml2.h"
#include "dslStringList.h"
#include <string>
#include <vector>
//---------------------------------------------------------------------------


namespace dsl
{
    using std::string;
    using std::vector;
    using tinyxml2::XMLElement;
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLNode;

    DSL_COMMON vector<double> getDoubleAttributes(const tinyxml2::XMLElement* elem, const StringList& lbls);
    DSL_COMMON vector<double> getRecordOfDoubles(const tinyxml2::XMLElement* element, const string& name, const StringList& lbls);
    DSL_COMMON vector<double> getListOfDoublesAttribute(const tinyxml2::XMLElement* elem, const string& lbl);

}
#endif
