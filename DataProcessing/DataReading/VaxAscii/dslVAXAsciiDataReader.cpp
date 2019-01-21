
#pragma hdrstop
#include "dslVaxAsciiDataReader.h"
#pragma argsused


bool dslVaxAsciiDataReader::Read(const string& fileName, const DATA_FORMAT& format, const FILE_FORMAT& fType)
{
////The header has the following format
////  params      16
////            4096,  0.00000000E+00
////               1,  0.50000000E+03
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////               0,  0.00000000E+00
////data      4096
////  0.21610000E+04, -0.79000000E+03
////  0.25050000E+04, -0.18140000E+04
//// .....................................
////data      4096
////  0.21610000E+04, -0.79000000E+03
////  0.25050000E+04, -0.18140000E+04
//// ...................................
////Line 1:
////This is the parameter header line, which contains the keyword params and the number of parameter data lines. The format is:
////params, i8
////Lines 2-17:
////These are the data parameters. These lines all contain one integer and one real number.
////Many of these parameters are unused. The essential parameters are named explicitly.
////For parameters that are equivalent to a Felix reserved symbol,the symbol name is given in parentheses.
//// The format is:
////1x,i15,2x,e15.8
////Line 2:
////This line contains the number of data points (datsiz) and the spectrum width (swidth).
////Line 3:
////This line contains the data type (datype) and the spectrometer frequency (sfreq).
////Line 4:
////The first datafield in this line is unused, the second is the reference shift (refsh).
////Line 5:
////This line contains the axis type (axtype) and the reference point (refpt).
////Line 6:
////This line is unused.
////Line 7:
////The first datafield in this line is unused, while the second is the zero-order phase (phase0).
////Line 8:
////The first datafield in this line is unused, while the second contains the first-order phase (phase1).
////Lines 9-17:
//
//      if(Data->GetFile()->Open(ffASCII, dslIn))
//    {
//    fstream* inF = Data->GetFile()->PStream();
//    char trash[201];
//    int buf_size = 200;
//    string tempStr, resultStr;
//
//    //Try to read 18 lines
//    vector<string> header;
//    for(int i = 0; i < 18; i++)
//{
//      inF->getline(trash, buf_size);
//      header.push_back(trash);
//    }
//    //First line
//    tempStr = header.at(0);
//    resultStr = dslEatRecord(tempStr);
//    if(resultStr != "params")
//{
//      return false;
//    }
//    resultStr = dslEatRecord(tempStr); // second record is number of parameters
//    int nrOfParams = atoi(resultStr.c_str());
//
//    //Second line
//    tempStr = header.at(1);
//    resultStr = dslEatRecord(tempStr);
//    //first record is number of datapoints
//    int nrOfDataPoints = atoi(resultStr.c_str());
//    //second record is the SW
//    resultStr = dslEatRecord(tempStr);
//    double SW = atof(resultStr.c_str());
//
//    //third line
//    //Line 5:Axtype and refpoint
//    tempStr = header.at(2);
//    resultStr = dslEatRecord(tempStr);
//    //first record is number of datapoints
//    //int axisType = atoi(resultStr.c_str());
//
//    //second record is the refpoint
//    resultStr = dslEatRecord(tempStr);
//    //int refPoint = (int) atof(resultStr.c_str());
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//// READING DATA GOES HERE
/////////////////////////////////////////////////////////
//    //Find out how many rows of data, dats equal to the number of lines containing the word data
//    //rewind file
//    inF->seekg(0,ios_base::beg);
//
//    int nrOfRows = 0;
//    while(inF->getline(trash, buf_size))
//      if(strstr(trash,"data"))
//        nrOfRows++;
//
//    if(inF->eof())
//      inF->clear();
//    //rewind file
//    inF->seekg(0,ios_base::beg);
//
//    /*** Resize Data ***/
//    Data->Resize(nrOfRows, nrOfDataPoints);
//    string tempString;
//    tempString = "Size of data: ";
//    tempString += toString(nrOfRows).c_str();
//    tempString += "x";
//    tempString += toString(nrOfDataPoints).c_str();
//    Data->GetStringSet()->push_back(tempString);
//
//    //Advance to the first datasection, that is nrOfparams + 3
//    int lineNr = 1;
//    while(lineNr++ !=  nrOfParams + 3)
//    inF->getline(trash, buf_size);
//
//    /*** Now Read in the actual data***/
//    int PointNumber = 0;
//    double re, im;
//      for(int Row = 1; Row < Data->RSize() + 1; Row++)
//{
//       for(int Col = 1; Col < Data->CSize() +1; Col++)
//{
//        //First column is the real number and the second column is the imaginary number
//        inF->getline(trash, buf_size);
//        tempStr = trash;
//        resultStr = dslEatRecord(tempStr);
//        re = atof(resultStr.c_str());
//        resultStr = dslEatRecord(tempStr);
//        im = atof(resultStr.c_str());
//        Data->Element(Row,Col) = complex<double> (re,im);
//        PointNumber++;
//      }
//    }
//
//    if(SW)
//{
//      double dwell = SW/nrOfDataPoints;
//      double offset = -SW/2;
//      Data->GetColAxis()->SetAxis(offset,dwell);
//    }else
//      Data->GetColAxis()->SetAxis(0,1);
//
//    Data->GetRowAxis()->SetAxis(0,1);
//    tempString = toString(PointNumber).c_str();
//    tempString += " numbers read..";
//    Data->GetStringSet()->push_back(tempString);
//    Data->GetStringSet()->push_back("The following lines is the header:");
//    for(unsigned int i = 0; i < header.size(); i++)
//      Data->GetStringSet()->push_back(header.at(i));
//
//    Data->SetOriginalDataFormat(dfVAX_ASCII);
//    Data->GetFile()->Close();
//    return true;
//  }
//  return false;

}

