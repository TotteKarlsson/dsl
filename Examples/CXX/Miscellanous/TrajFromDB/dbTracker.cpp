#ifdef WINDOWS
#ifdef USEPCH
#include "pch.h"
#endif
#pragma hdrstop
#endif
//==============================

#include <iostream>
#include <iomanip>
#include "dslCurve.h"
#include "dslCurveViewer.h"
#include "dslExplorer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"

#include "usr_getopt.h"
#include "mvlinsUtils.h"
#include "MVLINSObject.h"
#include "dbclient.h"

using namespace std;

int main(int argc, char * argv[])
{
    int c;
    string iniFileName;
    bool terminateMe = false;
    while ((c = usr_getopt(argc, argv, ("i:"))) != -1)
    {
        switch (c)
        {
            case ('i'): iniFileName = optarg; break;
            case ('?'): // illegal option
                {
                    string str = argv[0];
                    string msg = ("-i\"Read from ini file\" sets the ini file to read from\n");
                    cout<<"Illegal option\t"<<argv[optind-1]<<endl;
                    cout<<msg<<endl;
                }
            default: exit(0);
        }
    }

    string testfile = "test_XYZ.dsl";
    Explorer * expl = new Explorer;
    Curve* traj;
    traj = new Curve(expl);
    if(!traj->Read(testfile.c_str()))
    {
        cout<<"The file "<<testfile<<" could not be read. exiting...\n";
        exit(0);
    }

    traj->GetCurve()->RenderXYZRow(1);
    traj->ShowTube();
    expl->explore();


    DBClient dbClient;

    dbClient.ReadIniFile(iniFileName);

    //"General" setup
    dbClient.Setup();
    clog<<"After Dipole MySQL Setup..\n"<<endl;

    //Connect to the database
    if(!dbClient.ConnectToDataBase())
    {
        dbClient.LogError("DBClient could not connect to the database, exiting..");
        terminateMe = true;
    }

    //Check that required database tables are in the database
    if(!terminateMe)
    {
        if(!dbClient.CheckAndCreateTables())
        {
            dbClient.LogError("DBClient could not Create database tables, exiting..");
            terminateMe = true;
        }
    }

    IPCMessage msgIn;
    vector<IPCMessage> msgBuffer;   //In principle, there can be many messages to send
    while(terminateMe == false)
    {
        if(msgIn.read(cin))
        {
            //The following function handles any input.
            dbClient.HandleIPCMessage(msgIn);
            terminateMe = dbClient.TerminateMe();

            if(terminateMe)
                break;

            //Any output from dbClient is popped here
            msgBuffer = dbClient.PopMessageBuffer();

            //Send any messages to standard out
            for(u_int i = 0; i < msgBuffer.size(); i++)
            {
                msgBuffer[i].write(cout);
            }
        }
    }
    //Terminating nicely
    clog<<"DBClient is exiting...\n";
    clog.flush();
}


