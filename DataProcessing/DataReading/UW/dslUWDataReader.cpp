
#pragma hdrstop
#include "UWDataFileUtil.h"
#include "dslUWDataReader.h"
#pragma argsused


bool dslUWReader::Read(const string& fileName, const DATA_FORMAT& format, const FILE_FORMAT& fType)
{
    FILE *fileP = fopen(fileName.c_str(), "rb");
      if(!fileP)
    {
        return false;
    }
    int stringLength;
    string aString;
    char *stringP = nullptr;
    Data->GetStringSet()->clear();
    Data->GetStringSet()->push_back("This data was read from file in the dslUWBINARY format");
    Data->GetStringSet()->push_back(string("Data File Name: ") + Data->GetFileName());

    ////////////// Time
    stringP = get_time(fileP, &stringLength);
    if(stringP)
    {
        aString = "This data was taken on: ";
        aString += stringP;
        Data->GetStringSet()->push_back(aString);
        if(stringP)
        {
            free(stringP);
        }

        ////////////// Pulse Program Name
        stringP = get_pp_name(fileP, &stringLength);
        aString = "Pulse Program File: ";
        aString += stringP;
        Data->GetStringSet()->push_back(aString);

        if(stringP)
            free(stringP);

        ///////////// Symbol Table
        Data->GetStringSet()->push_back("");
        Data->GetStringSet()->push_back("======= Symbol table =======");
        stringP = get_symbol_table(fileP, &stringLength);
        char *ch = stringP;
        //Make Strings
        string aString;
        int i = 0;
        do
        {
            while(*ch != '\n')
            {
                aString += *ch;
                ch++;
                i++;
            }
            //Remove the first three characters
            aString.erase(0,3);

            //Remove everything after second space
            while(aString.rfind(" ") != aString.find(" "))
            {
                aString.erase(aString.rfind(" "));
            }
            Data->GetStringSet()->push_back(aString);
            aString = "";
            ch++;
            i++;
        }while(i < stringLength);

        if(stringP)
        {
            free(stringP);
        }

        //////////// Global Symbols
        Data->GetStringSet()->push_back("");
        Data->GetStringSet()->push_back("======= Global Symbols =======");
        GLOBAL_SYMBOLS* gSymbols = get_global_symbols(fileP, &stringLength);
        aString = "Size in the t2 dimension is : ";
        aString += toString(gSymbols->size);
        Data->GetStringSet()->push_back(aString);

        //////////// Pulse Program
        Data->GetStringSet()->push_back("");
        Data->GetStringSet()->push_back("======= Pulse Program =======");
        stringP = get_pulse_program(fileP, &stringLength);
        ch = stringP;
        i = 0;
        aString.clear();
        do
        {
            while(*ch != '\n')
            {
                aString += *ch;
                ch++;
                i++;
            }
            Data->GetStringSet()->push_back(aString);
            aString = "";
            ch++;
            i++;

        }while(i < stringLength);

        if(stringP)
        {
            free(stringP);
        }
        /////////////// Data
        //Check how many rows to read.. ugly
        int NrOfRows = 0;
        do
        {
            (COMPLEX_INT *) stringP = get_data(fileP, &stringLength, ++NrOfRows);
            free(stringP);
        }while(stringP != nullptr);

        free(stringP);
        Data->Resize(NrOfRows, gSymbols->size);

        /*** Read the actual data ***/
        for(int row = 1; row < Data->RSize() + 1; row++)
        {
            aString = string("Exp number") + toString(row).c_str();
            Data->GetStringSet()->push_back(aString);
            (COMPLEX_INT *) stringP = get_data(fileP,  &stringLength, (row-1));
            for(int col = 1;col < (Data->CSize() + 1);col++)
            {
                Data->data(row,col) = complex<double> (((COMPLEX_INT *)stringP)[(col-1)].real, ((COMPLEX_INT *)stringP)[(col-1)].imag);
            }
            free(stringP);
        }

        Data->GetColAxis()->SetAxis(0.0, 1./gSymbols->sw);
        Data->GetRowAxis()->SetAxis(0, 1);
        Data->SetOriginalDataFormat(dfUW);
        Data->GetStringSet()->push_back("Finished reading file....");

        // Clean up
        free(gSymbols);
        fclose(fileP);
        return true;
    }
      return false;
}

