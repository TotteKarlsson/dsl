#pragma hdrstop
#include "dslExeFile.h"
#pragma package(smart_init)

namespace dsl
{

ExeFile::ExeFile(const string& name)
{
    mFileName = name;
//    Properties = new TStringList;
//    FillProperties();
//    UpdateStringsFromProperties();
    messageHandling = SHOWMESSAGE;
}

ExeFile::~ExeFile()
{
//	delete Properties;
}

//bool ExeFile::HasIniFile()
//{
//	//Check if the exe has an associated INI file
//    string fName = mFileName.GetFileNameNoExtension();
//    fName+=".ini";
//    fName = mFileName.GetPath() + "\\" + fName;
//    return FileExists(fName);
//}

//void ExeFile::FillProperties()
//{
//	Properties->Add("Name=<none>");
//    Properties->Add("Executable Name=<none>");
//    Properties->Add("Executable Folder=<none>");
//    Properties->Add("Script File=<none>");
//    Properties->Add("Message Handling=IGNOREMESSAGE");
//    Properties->Add("Script Files Folder=<none>");
//    Properties->Add("Help File=<none>");
//    Properties->Add("ScriptFileExtension=<none>");
//
//}

String ExeFile::getMessageHandlingAsString()
{
    switch(messageHandling)
    {
    	case IGNOREMESSAGE: return "IGNOREMESSAGE";
    	case CATCHMESSAGE:  return "CATCHMESSAGE";
    	case SHOWMESSAGE:   return "SHOWMESSAGE";
    }
    return "";
}

//void ExeFile::UpdateStringsFromProperties()
//{
//    Name                     = Properties->Values["Name"];
//    ExecutableName           = Properties->Values["Executable Name"];
//    ExecutableFolder         = Properties->Values["Executable Folder"];
//    ScriptFile               = Properties->Values["Script File"];
//    String tempStr           = Properties->Values["Message Handling"];
//    ScriptsFolder            = Properties->Values["Script Files Folder"];
//    HelpFile                 = Properties->Values["Help File"];
//    ScriptFileExtension      = Properties->Values["ScriptFileExtension"];
//
//    //enum MESSAGEHANDLING {IGNOREMESSAGE = 0, CATCHMESSAGE, SHOWMESSAGE};
//    if(tempStr == "IGNOREMESSAGE")
//    {
//    	messageHandling = IGNOREMESSAGE;
//    }
//    else if(tempStr == "CATCHMESSAGE")
//    {
//    	messageHandling = CATCHMESSAGE;
//    }
//    else
//    {
//    	messageHandling = SHOWMESSAGE;
//    }
//}

//void ExeFile::SetProperties(const TStringList* Source)
//{
//    TStringList *list = new TStringList(*Source);
//    for(int i = 0; i < list->Count; i++)
//    {
//        if(list->Strings[i].Pos("=") > 1)
//        {
//            String nStr = list->Names[i];
//            //      String val =  Source->Values[Properties->Names[i]];
//            String val =  list->Values[nStr];
//            int DI = Properties->IndexOfName(nStr);
//            if(DI > -1)
//            //        Properties->Values[DI] = Source->Values[Properties->Names[i]];
//            Properties->Values[nStr] = val;
//        }
//    }
//    UpdateStringsFromProperties();
//}
//
}
