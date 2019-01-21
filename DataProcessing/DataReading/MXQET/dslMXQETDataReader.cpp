
#pragma hdrstop
#include "dslMXQETDataReader.h"
#pragma argsused


bool dslMXQETDataReader::Read(const string& fileName, const DATA_FORMAT& format, const FILE_FORMAT& fType)
{
    FILE *fp = fopen(fileName.c_str(), "rb");
    if(!fp)
    {
        return false;
    }

    /////////////////// HEADER /////////////////////////
    //First read the recordlength.. this is a four byte number telling the record length
    //in bytes
    int recL1;
    fread(&recL1,4,1,fp);
    //then read the records
    //Allocate integers
    int nrOfRecords = recL1/4;
    //The first half of the records are ints, the last half are floats
    int *intRecord = new int[nrOfRecords];
    int ints[16];
    float floats[16];
    fread(intRecord, 4, nrOfRecords, fp);

    for(int i = 0; i < nrOfRecords/2; i++)
    {
        ints[i] = intRecord[i];
          floats[i] =  *(float*) &intRecord[i + 16];
    }

    int recL2;
    fread(&recL2,4,1,fp);//Then read the record length again

    if(recL1 != recL2)
    {
        return false;
    }

    //////////////// END OF HEADER  //////////////////////////////////
    //Process header
    int nrOfDataPoints = ints[1];

    //second record is the SW
    float SW = floats[1];

    //float specFreq = floats[2];
    //int   axisType = ints[4];
    //float refPoint = floats[4];

    //////////////// DATA ////////////////////////////////
    //First read the recordlength.. this is a four byte number telling the record length
    //in bytes
    fread(&recL1,4,1,fp);

    nrOfRecords = recL1/4;
    //The first half of the records are ints, the last half are floats

    //First record is an int saying how many data points
    float* re = new float[0];
    float* im = new float[0];
    delete [] intRecord;
    intRecord = new int[nrOfRecords];
    fread(intRecord,4,nrOfRecords,fp);

    //int rec1 = intRecord[0];
    int point = 1;
    Data->Resize(1, nrOfDataPoints);
    for(int i = 1; i < nrOfDataPoints + 1; i++)
    {
        *re  = (*(float*) &intRecord[point]);
          *im =  (*(float*) &intRecord[point + 1]);
          Data->Element(1,i) = complex<double> (*re, *im);
          point += 2;
    }
    delete []re;
    delete []im;
    delete [] intRecord;
    fread(&recL2,4,1,fp);//Then read the record length again

    if(recL1 != recL2)
    {
        return false;
    }
    //post processing
    if(SW)
    {
        double dwell = SW/nrOfDataPoints;
          double offset = -SW/2;
          Data->GetColAxis()->SetAxis(offset,dwell);
    }
    else
    {
        Data->GetColAxis()->SetAxis(0,1);
    }

    fclose(fp);
    return true;
}

