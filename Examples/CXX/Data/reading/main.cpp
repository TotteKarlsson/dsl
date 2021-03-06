//---------------------------------------------------------------------------
#include "dslDataReader.h"
#include "dslDataWriter.h"
#include "dslFile.h"
#include "dslLogger.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma argsused
using namespace std;
using namespace dsl;
int main()
{
//    LogOutput::mLogToConsole = true;
//    int rowSize = 16, colSize = 1;
//    dslData< complex<double> > Data1(rowSize, colSize);
//    Data1.FillRandom();
//
//    Log(lInfo)<<Data1;
//
//    dslDataWriter< complex<double> >* writer = new dslDataWriter< complex<double> >(&Data1);
//    string outFName = "test1.dat";
//    writer->Write(outFName, ffASCII);
//
//    Data1.Resize(1,1);
//
//    list<DATA_FORMAT  > dFormats;
//    dFormats.push_back(dfMoleculix);
////    dFormats.push_back(dslINTEGER);
////    dFormats.push_back(dfDouble);
////    dFormats.push_back(dfComplex);
////    dFormats.push_back(dfSimpson);
////    dFormats.push_back(dslMXQETFORMAT);
////    dFormats.push_back(dfUW);
//
//    string dataFolder = "P:\\DataFiles\\DataFormats\\dslFormat\\TwoD";
//    dslDataReader< complex<double> >* reader = new dslDataReader< complex<double> >(Data1);
//    list<DATA_FORMAT  >::iterator iter;
//    bool readOK = false;
//    bool writeOK = false;
//
//    for(iter = dFormats.begin(); iter != dFormats.end(); iter++)
//    {
//        DATA_FORMAT   dFormat = (*iter);
//
//        switch(dFormat)
//        {
//            case dfMoleculix:
//                Log(lInfo)<<"Reading dfMoleculix";
//                readOK = reader->Read(dataFolder + "\\full.dsl");
//                writeOK = writer->Write("dslFormatFull.dsl");
//            break;
//
////            case dslINTEGER:
////                Log(lInfo)<<"Reading dslINTEGER";
////            break;
////
////            case dfDouble:
////                Log(lInfo)<<"Reading dfDouble";
////            break;
////
//            case dfComplex:
//                Log(lInfo)<<"Reading dfComplex";
//            break;
////            case dfSimpson:
////                dataFolder = "P:\\DataFiles\\DataFormats\\Simpson";
////                reader = new dslSimpsonDataReader(Data1);
////                reader->Read(dataFolder + "//csa.spe");
////                Log(lInfo)<<"Reading UW_BINARY";
////            break;
////
////            case dslMXQETFORMAT:
////                dataFolder = "P:\\DataFiles\\DataFormats\\FTNMR";
////                reader = new dslMXQETDataReader(Data1);
////                reader->Read(dataFolder + "//static_1.spc");
////                delete reader;
////                Log(lInfo)<<"Reading UW_BINARY";
////            break;
////
////            case dfUW:
////                dataFolder = "P:\\DataFiles\\DataFormats\\UW";
////                reader = new dslUWReader(Data1);
////                reader->Read(dataFolder + "//uw_1.dat");
////                Log(lInfo)<<"Reading UW_BINARY";
////            break;
//
//            default:
//            break;
//        }
//
//        if(readOK)
//        {
//            Log(lInfo)<<"Read data OK!";
//            for(unsigned int i = 1; i < Data1.CSize() + 1; i++)
//            {
//                cout<<"Row "<<i<<" "<<Data1.Element(1,i)<<endl;
//            }
//        }
//        else
//        {
//            Log(lError)<<"Data was not read OK!";
//
//        }
//
//        if(writeOK)
//        {
//            Log(lInfo)<<"Wrote Data OK!";
//        }
//        else
//        {
//            Log(lError)<<"Data was not written OK!";
//
//        }
//
//    }

  return 0;
}
 
#include "Moleculix-autolink.h"

        
