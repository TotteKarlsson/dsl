
#pragma hdrstop
#include "dslSimpsonDataReader.h"


#pragma argsused


bool dslSimpsonDataReader::Read(const string& fileName, const DATA_FORMAT& format, const FILE_FORMAT& fType)
{
    //The header has the following format
    //SIMP
    //NP=512
    //SW=7878
    //.....
    //....
    //TYPE=FID
    //DATA
    // re im
    // re im
    //END

    File inFile(fileName);
    fstream* inF;
    inFile.Open(ffASCII, dslIn);

      if(!inFile.PStream())
    {
        return false;
    }
    inF = inFile.PStream();
    Data->GetStringSet()->clear();
    Data->GetStringSet()->push_back("This data was read from file in the dfSimpson format");
    Data->GetStringSet()->push_back(string("File name: ") + Data->GetFilePath() + Data->GetFileName());
    char trash[201];
    int buf_size = 200;
    string str, result;

    inF->getline(trash, buf_size);
    str = trash;
    vector<string> lines;

    if(str != "SIMP")
    {
        return false;
    }
    else
    {
      lines.push_back(str);
    }

    // Read in all string until the data section
    do
    {
        inF->getline(trash, buf_size);
          str = trash;
          lines.push_back(str);

    }while(str != "DATA");

    //How many points in the "direct dimension" ?
    // Find the line with NP=
    for(unsigned int i = 0; i < lines.size(); i++)
    {
        int test = lines.at(i).find("NP=");
          if(test != -1)
        {
            str = lines.at(i);
            break;
          }
    }

    int numberOfPoints;
    str.erase(0,3);
    char *endptr;
    numberOfPoints = strtod(str.c_str(), &endptr);

    /*** Find SW= ***/
    for(unsigned int i = 0; i < lines.size(); i++)
    {
        if(lines.at(i).find("SW=") != -1)
        {
            str = lines.at(i);
            break;
          }
    }

    double SW;
    Data->GetStringSet()->push_back(str);
    str.erase(0,3);
    SW = strtod(str.c_str(), &endptr);

       /////////////////////////////////////////////////////
       /*** Find TYPE= ***/
    for(unsigned int i = 0; i < lines.size(); i++)
    {
        if(lines.at(i).find("TYPE=") != -1)
        {
            str = lines.at(i);
            break;
          }
    }

       //Read the type of data: FID or SPEC this will tell us how assign the x-axis
    Data->GetStringSet()->push_back(str);
    str.erase(0,5);
    string datatype = str;

    //Check if this is a 2D data set
   /*** Find TYPE= ***/
    bool isTwoD = false;
    for(unsigned int i = 0; i < lines.size(); i++)
    {
        if(lines.at(i).find("NI=") != -1)
        {
            str = lines.at(i);
            isTwoD = true;
            break;
          }
    }

    int secDim = 1;
    if(isTwoD)
    {
        str.erase(0,3);
          secDim = atoi(str.c_str());
    }

    /*** Resize Data ***/
       int nrOfRows = secDim, nrOfCols = numberOfPoints;
       Data->Resize(nrOfRows, nrOfCols);
       string tempString;
       tempString = "Size of data: ";
       tempString += toString(nrOfRows).c_str();
       tempString += "x";
       tempString += toString(nrOfCols).c_str();
       Data->GetStringSet()->push_back(tempString);

      //Advance to the data section, that is after a line containing "DATA"
      /*** Find DATA= ***/
    for(unsigned int i = 0; i < lines.size(); i++)
    {
        if(lines.at(i).find("DATA") != -1)
        {
            str = lines.at(i);
            break;
          }
    }

       if(str != "DATA")
        return false;

       /*** Now Read in the actual data***/
       int PointNumber = 0;
       double re, im;
    for(int Row = 1; Row < Data->RSize() + 1; Row++)
    {
        for(int Col = 1; Col < Data->CSize() +1; Col++)
        {
            //First column is the real number and the second column is the imaginary number
            inF->getline(trash, buf_size);
            str = trash;

            re = atof(str.substr(0, str.find(" ")).c_str());
            im = atof(str.substr(str.find(" "), str.size()).c_str());

            Data->Element(Row,Col) = complex<double> (re,im);
            PointNumber++;
          }
       }

       //depending of the type of the data we have to assign different axis
       if(datatype == "FID")
    {
        Data->GetColAxis()->SetAxis(0,1./SW);
       }
       else
       {
           Data->GetColAxis()->SetAxis(-SW/2, SW/nrOfCols);
       }

       Data->GetRowAxis()->SetAxis(0,1);
       tempString = toString(PointNumber).c_str();
       tempString += " numbers read in to dslData";
       Data->GetStringSet()->push_back(tempString);
       Data->SetOriginalDataFormat(dfSimpson);
       return true;
}

