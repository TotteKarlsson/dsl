
#pragma hdrstop
#include "dslFelixDataReader.h"
#pragma argsused


bool dslFelixDataReader::Read(const string& fileName, const DATA_FORMAT& format, const FILE_FORMAT& fType)
{
////  FILE *fp = fopen(Data->GetFileName().c_str(), "rb");
////  if(fp)
//{
////    long map[5];
////    int four = 4;
////    long *longData = nullptr;
////     /// First read the header
////
////    long nread, istat;
////    long key, count;
////    long lone = 1;
////
////    nread = (long) fread(&key,four,lone,fp);
////    if (nread != 1)
////      return false;
////
////    /* evaluate the byte key, and create the swapping map */
////    istat = bytmap(&key,map);
////    if (istat != 0)
////     return false;
////
////    //test check the key
////    bytswa(map,&lone,&key);
////    if(key !=  0x4030201)
////      return false;
////
////    /* next read the # of words */
////    nread = (long) fread(&count,four,lone,fp);
////    if (nread != 1)
////     return false;
////
////    /* byte swap the count */
////    bytswa(map,&lone,&count);
////    if(count < 1)
////     return false;
////
////    /* now read that many words of header */
////    longData = new long[count];
////    nread = (long) fread(longData,four,count,fp);
////    if (nread != count)
////     return false;
////
////    /* byte swap the header contents */
////    bytswa(map, &count, longData);
////    //Decode felix header and put relevant extracted information into file info
////    long nrOfDataPoints = longData[94];
////    int dataType  = longData[95];
////    int domain    = longData[96];
////    int axisType  = longData[97];
////    float SW        = ((float*)longData)[110];
////    float specFreq  = ((float*)longData)[111];
////    float refShift  = ((float*)longData)[112];
////    float refPoint  = ((float*)longData)[113];
////    float phase0    = ((float*)longData)[114];
////    float phase1    = ((float*)longData)[115];
////
////    ////////////////////////READ DATA /////////////////////////////////
////    // First is an int telling how many points of data there is to read.
////    // this is the number of points in each experiment
////    // there may be several experiments however and that
////    // number is obtained by inspecting the file with the
////    // code after the swap..
////
////    long curPos = ftell(fp); //Store the position in the file
////    //allocate that many elements
////    int nrOfExp = 0;
////    do{
////      fread(&count,four,1,fp);
////      bytswa(map, &lone, &count);
////      delete[] longData;
////      longData  = new long[count];
////      nread = (long) fread(longData,four,count,fp);
////      if(nread)
////        nrOfExp++;
////    }while(!feof(fp));
////    delete[] longData ;
////    //rewind the file
////    rewind(fp);
////    //Go back to where we were
////    fseek(fp, curPos, 0);
////
////    switch(dataType)
//{
////      case 0: //Real N_Words re1 re2 ....
////      break;
////      case 1: //COMPLEX N_Words re1 im1 re2 im2....
////        Data->Resize(nrOfExp, nrOfDataPoints);
////        for(int expNr = 1; expNr < nrOfExp + 1; expNr++)
//{
////          long nrOft2Pts;
////          fread(&nrOft2Pts,four,1,fp);
////          longData  = new long[nrOft2Pts];
////          bytswa(map, &lone, &nrOft2Pts);
////          //long test = (long) fread(longData,four,nrOft2Pts,fp); //do something sensible with test...
////          fread(longData,four,nrOft2Pts,fp); //do something sensible with test...
////          bytswa(map, &nrOft2Pts, longData);
////          for(int pointNr = 1, i = 0; i < nrOft2Pts; i+=2, pointNr++)//
////            Data->Element(expNr, pointNr) = complex<double> (((float*)longData)[i], ((float*)longData)[i+1]);
////          delete[] longData;
////
////        }
////      break;
////      default://Integer.. don't know what this is yet..
////      break;
////    }
////
////    if(SW)
//{
////      switch(axisType)
//{
////        case 0://None
////          Data->GetColAxis()->SetAxis(0,1./SW);
////        break;
////        case 1: //points
////          Data->GetColAxis()->SetAxis(0,1./SW);
////        break;
////        case 3: //ppm
////        break;
////        default:
////          Data->GetColAxis()->SetAxis(0,1./SW);
////        break;
////      }
////    }
////    //Fill in the extra file info
////    string tempString = "This data was read from a file in FELIX new format";
////    Data->GetStringSet()->push_back(tempString);
////
////    fclose(fp);
////    return true;
////  }
////  return false;

}

