
#pragma hdrstop
//==============================
#include <sstream>
#include "dslStringUtils.h"
#include "dslIPCDataMessage.h"
//#include "dslDataWriter.h"


using std::stringstream;

//dslIPCDataMessage::dslIPCDataMessage(dslComplexData* data)
//: IPCMessage("NMR_DATA")
//{
//    //Create a message holding data
//    type = NMR_DATA;
//    SetHeader("NMR_DATA");
//
//    stringstream stream;
//    if(data)
//    {
//        dslDataWriter< complex<double> > writer(data);
//        stream<<writer.GetAsString();
//        ipc_data.push_back(stream.str());
//    }
//}


