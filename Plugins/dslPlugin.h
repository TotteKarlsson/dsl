#ifndef dslPluginH
#define dslPluginH
#include <sstream>
#include <string>
#include "dslPluginsExporter.h"
#include "dslProperties.h"
#include "dslPluginsExporter.h"
#include "dslPluginMetaData.h"

namespace dsl
{
    using std::string;
    using dsl::gEmptyString;
    using dsl::gNoneString;
    class PluginManager;

class DSL_PLUGINS Plugin
{
    friend PluginManager;
    public:
                                                Plugin(const string& name = gEmptyString, const string& cat = gNoneString, const PluginManager* pm = nullptr);
        virtual                                 ~Plugin();

        bool                                    addProperty(dsl::BaseProperty* p);

        virtual bool                            execute(DSLObject* obj = nullptr, bool inThread = false) = 0;
        virtual void                            terminate(bool waitForThread = false);
        virtual bool                            assignMetaData(const PluginMetaData& mData);
        bool                                    isBeingTerminated() const;
        bool                                    wasTerminated()     const;
        virtual bool                            isWorking()         const;
        virtual string                          getInfo();
        virtual string                          getExtendedInfo();

                                                //!Plugin specific properties
        virtual Properties*                     getProperties();
        virtual StringList                      getPropertyNames();
        virtual BaseProperty*                   getProperty(const string& param);

        template <class T>
        void        		                    setPropertyValue(const string& nameOf, const T& value);

        template <class T>
        T       	                            getPropertyValue(const string& nameOf);

        virtual bool                            resetPlugin();
        virtual string                          getStatus();

                                                //Get some Plugin MetaData
        PluginMetaData                          getPluginMetaData();
        string                                  getName();
        string                                  getLibraryName();
        string                                  getAuthor();
        string                                  getCategory();
        string                                  getDescription();
        string                                  getHint();
        string                                  getVersion();
        string                                  getCopyright();

        string                                  getPropertyValueAsString(const string& param);
        int	                                    getPropertyValueAsInteger(const string& param);
        void*                                   getPropertyValueHandle(const string& param);
        void                                    setPropertyByString(const string& nameOf, const string& value);

        const PluginManager*           			getPluginManager() const;
        void                                    setLibraryName(const string& libName);

    protected:
        PluginMetaData                          mMetaData;

        virtual void                            setPropertyValueFromVoid(const string& nameOf, const void* value);

                                                //!These are plugin specific (data) properties
        Properties                              mProperties;
        bool                                    mTerminate;
        bool                                    mIsWorking;

                                                //!The subject is handed to the plugin in its execute function
                                                //!The subject is a DSL object that the plugin is allowed to do work on
                                                //The subject should perhaps be passed as a void*
        DSLObject*                              mSubject;
        const PluginManager*               		mPM;
};

template <class T>
void Plugin::setPropertyValue(const string& nameOf, const T& value)
{
    setPropertyValueFromVoid(nameOf, (void*) &value);
}



}



#endif
