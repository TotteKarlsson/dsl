#ifndef dslProjectH
#define dslProjectH
#include "dslSubject.h"
#include "tinyxml2/tinyxml2.h"
#include "dslProjects.h"
//---------------------------------------------------------------------------

namespace dsl
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLElement;
    using tinyxml2::XMLNode;

class DSL_COMMON Project : public Subject
{
    public:
                                                Project(const string& fName = gEmptyString, const string& fExt = gEmptyString);
                                                Project(const Project& p);
        virtual                                 ~Project();

                                                //!The save function captures a project properties etc
                                                //!and adds it to the XML. If a fileName is given, it also saves it to file
        virtual bool                            save(const string& fName = gEmptyString);
        virtual bool							setFileFolder(const string& fFolder);

                                                //!Load XML from file
        virtual bool                            loadXMLFromFile(const string& path = gEmptyString);

                                                //!Save XML to file
        virtual bool                            saveToFile(const string& path = gEmptyString);
        virtual string                          getXML();

        bool                                    isOpen();
        virtual bool         	                isModified();

                                                //Delete data associated with project
        virtual bool                            deleteData(){return false;}

        virtual bool                            open(const string& fName = gEmptyString);
        virtual bool                            close();

		string									getProjectName() const;
		void									setProjectName(const string& name);
        string                                  getFileName();
        void                                    setFileName(const string& fName);
        string									getFileFolder(){return mFileFolder;}
        void									setFileExtension(const string& e){mFileExtension = e;}

        void                                    setModified();
        void                                    resetModifiedFlag();
        bool                                    isNeverSaved();
        bool                                    existOnDisk();
        string                                  getModelVersion();
        virtual string                          getPresentXMLModelVersion() = 0;

        XMLDocument&                            getXMLDoc();

        void                                    setParent(Project* p);
        Project*        			            getParent();
        size_t									getNumberOfChilds();
        Project*								getChild(int i);
        bool                                    removeChild(Project* child);
        Project*                                getProjectRoot();

        virtual dsl::XMLElement*           		addToXMLDocument(dsl::XMLDocument& doc, dsl::XMLNode* docRoot) = 0;
		virtual dsl::XMLElement*                addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLElement* node) = 0;
        void                                    beforeRemove();

    protected:
        bool                                    mIsModified;
        bool                                    mIsNeverSaved;
        string                                  mProjectName;

        string									mFileFolder;
        string                                  mFileName;
        string                                  mFileExtension;

                                                //ParentProject
		Project*         			            mParent;

        XMLDocument                             mTheXML;
        XMLElement*                             mProjectRoot;
        XMLNode*                                mRootNode;
        bool                                    addNode(tinyxml2::XMLNode* node);
        XMLElement*                             getXML(const string& name);
        XMLElement*                             newElement(const string& name);

        										//!Childs can be various types of objecs, e.g. renderprojects and volumes
        Projects								mChilds;
};

}
#endif
