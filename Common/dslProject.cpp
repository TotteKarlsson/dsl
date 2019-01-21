#pragma hdrstop
#include "dslProject.h"
#include "dslFileUtils.h"
#include "dslLogger.h"


namespace dsl
{

using namespace tinyxml2;

Project::Project(const string& fName, const string& fExt)
:
mIsNeverSaved(true),
mIsModified(false),
mFileName(fName),
mProjectName(fName),
mFileExtension(fExt),
mProjectRoot(nullptr),
mRootNode(nullptr),
mParent(nullptr)
{}

Project::Project(const Project& p)
{
    mIsModified 	= p.mIsModified;
    mIsNeverSaved 	= p.mIsNeverSaved;
    mProjectName 	= p.mProjectName;
    mFileFolder  	= p.mFileFolder;
    mFileName		= p.mFileName;
    mFileExtension	= p.mFileExtension;

//    mTheXML			= p.mTheXML;
    mProjectRoot	= p.mProjectRoot;
    mRootNode		= p.mRootNode;
}

Project::~Project()
{
    notifyObservers(SubjectBeingDestroyed);

    Project* c = mChilds.getFirst();
    while(c)
    {
		////Does this not notify twice? (delete below)
        //c->notifyObservers(SubjectBeingDestroyed);
        delete c;
        c = mChilds.getNext();
    }
    mChilds.clear();
}

void Project::setParent(Project* p)
{
    mParent = p;
}

Project* Project::getParent()
{
    return mParent;
}

Project* Project::getProjectRoot()
{
    Project* parent = mParent;
    while(parent != nullptr)
    {
        Project* parentParent = parent->getParent();
        if(!parentParent)
        {
            break;

        }

        parent = parentParent;
    }
    return parent != nullptr ? parent : this;
}

Project* Project::getChild(int i)
{
	return mChilds.getProject(i);
}

int	Project::getNumberOfChilds()
{
	int sz =  mChilds.count();
	return sz;
}

bool Project::removeChild(Project* child)
{
    //Remove from container
    return mChilds.remove(child);
}

bool Project::setFileFolder(const string& fFolder)
{
  	if(folderExists(fFolder))
    {
    	mFileFolder = fFolder;
    	return true;
    }
    Log(lError) << fFolder <<" do not exist!";
    return false;
}

XMLDocument& Project::getXMLDoc()
{
    return mTheXML;
}

bool Project::isNeverSaved()
{
    return mIsNeverSaved;
}

bool Project::existOnDisk()
{
    return (mIsNeverSaved == true) ? false : true;
}

bool Project::isModified()
{
    return mIsModified;
}

void Project::setFileName(const string& fName)
{
    mFileName = fName;
}

void Project::setModified()
{
    mIsModified = true;
}

void Project::resetModifiedFlag()
{
    mIsModified = false;
}

bool Project::loadXMLFromFile(const string& thePath)
{
    close();    //Clear any previous XML

    if(thePath.size())
    {
	    mFileFolder = getFilePath(thePath);
        mFileName 	= getFileNameNoPath(thePath);
    }

    XMLError err = mTheXML.LoadFile(joinPath(mFileFolder, mFileName).c_str());
    if(err)
    {
        //throw
        return false;
    }

    //Means the project do exist on file
    mIsNeverSaved = false;

    mRootNode = mTheXML.FirstChild();
    mProjectRoot = mTheXML.RootElement();

    //Read project name
    XMLElement* name = mRootNode->FirstChildElement("name");

	if(name)
    {
    	mProjectName = name->GetText();
    }
    return true;
}

string Project::getFileName()
{
    return mFileName;
}

bool Project::isOpen()
{
    return (mTheXML.RootElement() != nullptr) ? true : false;
}

//Implement in descendants
bool Project::open(const string& fName)
{
    return false;
}

bool Project::close()
{
    mFileName = "";
    mTheXML.Clear();
    mProjectRoot = nullptr;
    mRootNode = nullptr;
    return true;
}

XMLElement* Project::newElement(const string& name)
{
    return mTheXML.NewElement(name.c_str());
}

XMLElement* Project::getXML(const string& name)
{
    if(!mProjectRoot)
    {
        return nullptr;
    }

    XMLElement* lookup = mProjectRoot->FirstChildElement(name.c_str());
    return lookup;
}

string Project::getXML()
{

	XMLPrinter p;
    mTheXML.Print( &p );
   	// p.CStr() has a const char* to the XML

    return p.CStrSize() ? string(p.CStr()) : string("");
}

bool Project::addNode(XMLNode* node)
{
    if(!mProjectRoot)
    {
        return false;
    }

    mProjectRoot->InsertEndChild(node);
    return true;
}

bool Project::save(const string& path)
{
    if(path.size())
    {
        return saveToFile(path);
    }
    return false;
}

bool Project::saveToFile(const string& fName)
{
    if(fName.size())
    {
        mFileName = getFileNameNoPath(fName);
    }

    string f = joinPath(mFileFolder, mFileName);
    mTheXML.SaveFile(f.c_str());
    mIsNeverSaved = false;
    mIsModified = false;
    return true;
}

string Project::getProjectName() const
{
    return mProjectName;
}

void Project::setProjectName(const string& name)
{
	mProjectName = name;
}

string Project::getModelVersion()
{
    XMLElement* version = mProjectRoot->FirstChildElement("version");
    if(version)
    {
        return string(version->GetText());
    }
    return "";
}

}
