#ifndef dslPluginMetaDataH
#define dslPluginMetaDataH
#include "dslPluginsExporter.h"
#include "dslObject.h"
#include <string>
#include <map>
//---------------------------------------------------------------------------
namespace dsl
{
using std::string;
using std::map;

//Use a container for this..
class DSL_PLUGINS PluginMetaData : public dsl::DSLObject
{
    public:
                                                PluginMetaData(const string& name, const string& category);
//		virtual									~PluginMetaData();

        string                                  getAll();
        bool                                    add(const string& lbl, const string& info);

        string                                  getAuthor();
        void                                    setAuthor(const string& val);

        string                                  getDescription();
        void                                    setDescription(const string& val);

        void                                    setLibraryName(const string& val);
        string                                  getLibraryName();

        void                                    setVersion(const string& val);
        string                                  getVersion();

        string                                  getHint();
        void                                    setHint(const string& val);

		string                                  getCategory();
        void                                    setCategory(const string& val);

        string                                  getCopyright();
        void                                    setCopyright(const string& val);

        string                                  getPluginName();
        void                                    setPluginName(const string& val);

    protected:
    	map<string, string>                     mData;
};

}
#endif
