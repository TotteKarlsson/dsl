#include "dslLogger.h"
#include "dslData.h"
#include "dslDataWriter.h"
#include "dslDataReader.h"
//---------------------------------------------------------------------------
#pragma argsused
using namespace std;
using namespace dsl;

#include "Moleculix-autolink.h"
int main()
{
    string logPrefix("data");

    FILE *logFile;
    logFile = fopen("log.txt","w");
//    LogOutput::setLogFile(*logFile);
//    LogOutput::setLogPrefix(logPrefix);
    LogOutput::mLogToConsole = (true);
    int rowSize = 4096, colSize = 2144;
    dslData< complex<double> > *Data1 = new dslData< complex<double> >(rowSize, colSize);
    dslData< complex<double> > *Data2 = new dslData< complex<double> >(rowSize, colSize);

    Data1->Fill();
    Data2->ZeroAll();

    dslDataWriter< complex<double> > writer(Data1);
    dslDataReader< complex<double> > reader(Data1);

    if(!writer.Write("test1.dat", ffBINARY))
    {
        return -1;
    }

    //  if(!reader.Read("test1.dat", ffBINARY))
    if(!reader.Read("test1.dat", dfMoleculix, ffBINARY))
    {
        return -1;
    }

    if(!writer.Write("test2.dat", ffASCII))
    {
        return -1;
    }

    //  if(!reader.Read("test2.dat", ffASCII))
    if(!reader.Read("test2.dat"))
    {
        return -1;
    }

    if(!writer.Write("test3.dat", ffASCII))
    {
        return -1;
    }

    //  fstream *fileS1 = new fstream("test1.dat", ios::out|ios::binary);
    //  complex<double> nr(1,2);
    //  string test = "nisse";
    //
    //  fileS1->write((char *) &nr, sizeof(nr));
    //  fileS1->close();
    //
    //  complex<double> nr2(2,2);
    //  fstream *fileS2 = new fstream("test1.dat", ios::in|ios::binary);
    //  fileS2->read((char *)&nr2, sizeof(nr2));
    //  fileS2->close();
    //  cout<<nr2;
    return 0;
}
//---------------------------------------------------------------------------
//  FILE *fileP = fopen("test2.dat", "wt");
//  dslFileHeader test;
//  test.header = "hejsan";
////  fwrite(&test, sizeof(test), 1, fileP);
//  dslData< complex<double> > Data(5,5);
//  Data.Fill();
//  complex<double> nr1;
//  for(int i = 0; i < 5; i++){
//    fwrite(&Data.data(i+1,i+1), sizeof(Data.data(i+1,i+1)), 1, fileP);
//  }
//  fclose(fileP);
//
//  dslFileHeader test2;
//  fileP = fopen("test2.dat", "rt");
////  fread(&test2, sizeof(test2), 1, fileP);
//  dslData< complex<double> > Data2(5,5);
//
//  complex<double> nr;
//  for(int i = 0; i < 5; i++)
//    fread(&nr, sizeof(nr), 1, fileP);
//  fclose(fileP);
//
//  cout<<nr;





