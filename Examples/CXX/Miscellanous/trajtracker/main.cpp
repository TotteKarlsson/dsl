#ifdef USEPCH
#include "pch.h"
#endif
#include <fstream>
#include "dslCurve.h"
#include "dslCurveViewer.h"
#include "dslExplorer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "dslExplorer.h"
//#include "mvlinsUtils.h"
//#include "MVLINSObject.h"
#include "dslIPCMessage.h"


using namespace dsl;
using std::fstream;
int main(int argc, char* argv[])
{
//    string testfile = "test_XYZ.dsl";
//    Explorer * expl = new Explorer;
//    Curve* traj;
//    traj = new Curve(expl);
//
//    if(!traj->Read(testfile.c_str()))
//    {
//        cout<<"The file "<<testfile<<" could not be read. exiting...\n";
//        exit(0);
//    }
//
//    bool terminateMe = false;
//    IPCMessage msgIn;
//    vector<IPCMessage> msgBuffer;   //In principle, there can be many messages to send
//    while(terminateMe == false)
//    {
//        if(msgIn.read(cin))
//        {
//            msgBuffer.push_back(msgIn);
//            //traj->GetData()->
//            traj->GetCurve()->RenderXYZRow(1);
//            traj->ShowTube();
//            expl->Render();
////            expl->explore();
//
//            //Send any messages to standard out
//            for(u_int i = 0; i < msgBuffer.size(); i++)
//            {
//                msgBuffer[i].write(cout);
//            }
//            msgBuffer.clear();
//        }
//    }
    return 0;
}

