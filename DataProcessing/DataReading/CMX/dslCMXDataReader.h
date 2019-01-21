////template<> inline
////bool mtkDataReader< complex<double> >::CMX2DBinary(fstream* inF)
//{
////    /*** This routine expects an file with the following format :
////    real_row (all Experiments)
////      1
////      |
////      .
////      q
////
////    imag_row (all Experiments)
////      1
////      .
////      .
////      n
////        The function reads in values (in the file supplied in fileName) into
////        the data-vector until something of the following occurs.
////        1) End of file is reached
////        2) Size of internal datamatrix is reached  ***/
////
////    if(inF)
//{
////      int NrOfRows, NrOfCols, buf = 0, i = 17;
////      double ExpIncr,t1Start, ArrayValue, DW, ValueRealPart, ValueImagPart;
////      char Str[200], ch, TempStr[100], charSt[20], IncrFile[100];
////      complex<double>  I(0,1),cpxNr(0,0);
////      strcpy(IncrFile,"Increment2D.dat");
////      enum {Arrayed, TwoD, SingleShot} ExpType;
////      string aString;
////      double incr;
////      //Change current directory
////      chdir(Data->GetFilePath().c_str());
////      /*** Check for size of the data file ***/
////      if(GetParameterInFile("acq", "al=",NrOfCols))
//{
////
////        aString = "Size in the t2 dimension is : " + toString(NrOfCols);
////        Data->GetStringSet()->push_back(aString);
////
////        if(GetParameterInFile("acq", "array_num_values",NrOfRows))
//{
////            /*** This is an arrayed experiment ***/
////            aString = "Processing arrayed experiment..";
////            Data->GetStringSet()->push_back(aString);
////            aString = "Number of experiments in the array: " + toString(NrOfRows);
////            Data->GetStringSet()->push_back(aString);
////            ExpType = Arrayed;
////        }
////        else if(GetParameterInFile("acq", "al2",NrOfRows))
//{
////        /*** This is a true 2Dimensional experiment ***/
////            aString = "Processing 2D experiment..";
////            Data->GetStringSet()->push_back(aString);
////            aString = "Number of secondary experiments in the data set: " + toString(NrOfRows);
////            Data->GetStringSet()->push_back(aString);
////            ExpType = TwoD;
////        }else{
////          /*** This is a single aqusition ***/
////          aString = "Processing single FID..";
////          Data->GetStringSet()->push_back(aString);
////          ExpType = SingleShot;
////          NrOfRows = 1;
////        }
////        Data->Resize(NrOfRows, NrOfCols);
////
////        /*** Read the actual data ***/
////        for(int row=1;row<Data->RSize() + 1;row++)
//{/*** Real part ***/
////          aString = "Exp number" + toString(row);
////          Data->GetStringSet()->push_back(aString);
////          for(int col = 1;col < (Data->CSize() + 1);col++)
//{
////            inF->read((char *)&buf,4);
////            ValueRealPart = convertCMXNumber(buf);
////            Data->data(row,col) = complex<double> (ValueRealPart);
////          }
////        }
////        for(int row=1;row<Data->RSize() + 1;row++)
//{/*** Complex part.. ***/
////          for(int col = 1;col < (Data->CSize() + 1);col++)
//{
////            inF->read((char *)&buf,4);
////            ValueImagPart = convertCMXNumber(buf);
////            cpxNr = ValueImagPart*I;
////            Data->data(row,col) += cpxNr;
////          }
////        }
////
////        /*** Set axis attributes ***/
////        switch(ExpType)
//{
////          case Arrayed:
////            aString = "Setting Axes for arrayed experiment.";
////            Data->GetStringSet()->push_back(aString);
////            /*** Find name of arrayed variable and put these onto the row axis ***/
////            GetLineInFileContaining("acq", "array_num_values", Str);
////
////            /*** Remove array_num_values_ from the line***/
////            while((ch = Str[i]) != '=')
//{
////              Str[i-17] = ch;
////              i++;
////            }
////            Str[i-17] = '\0';
////            aString = "The arrayed parameter is :" + string(Str);
////            Data->GetStringSet()->push_back(aString);
////
////            /*** Find the actual numbers of this one .. ***/
////            for(i = 0; i < NrOfRows; i++)
//{
////                strcpy(TempStr,Str);
////                strcat(TempStr,"[");
////                strcat(TempStr,itoa(i,charSt,10));
////                strcat(TempStr,"]");
////                GetParameterInFile("acq", TempStr, ArrayValue);
////                Data->GetRowAxis()->SetElement(i+1) = ArrayValue;
////            }
////            incr = Data->GetRowAxis()->GetIncrement();
////          break;
////          case TwoD:
////            aString ="Setting Axes for 2D experiment.";
////            Data->GetStringSet()->push_back(aString);
////            IncrementFromFile(IncrFile);
////            aString = "t1 is starting at : " + toString(Data->GetRowAxis()->GetOffset());
////            Data->GetStringSet()->push_back(aString);
////            aString = "Current Experiment increment = " + toString(Data->GetRowAxis()->GetIncrement());
////            Data->GetStringSet()->push_back(aString);
////            //Setting Axes arbitrarily
////            Data->GetRowAxis()->SetAxis(1,1);
////          break;
////      }
////
////      //Data->Writer->IncrementToFile(IncrFile);
////      GetParameterInFile("acq", "dw=", DW);
////      Data->GetColAxis()->SetAxis(0.0, DW);
////      Data->SetOriginalDataFormat(dfCMX);
////      return true;
////    }else
////     return false;
////  }
////  return false;
////}
//
////bool mtkDataReader< complex<double> >::CMX2DAscii(char *fileName)
//{
////  /*** This routine expects an file with the following format :
////  t2PointNr   "Tab"   ExpNr    "Tab"  real_row
////    |                     |               |
////    1
////    .
////    q
////                              ExpNr n
////      t2PointNr   "Tab"   ExpNr    "Tab"  imag_row
////    |                     |               |
////    1
////    .
////    .
////    n
////      The function reads in values (in the file supplied in fileName) into
////      the data-vector until something of the following occurs.
////      1) End of file is reached
////      2) Size of internal datamatrix is reached  ***/
////   int NumberOfLines = 0,row, col, buf_size = 100;
////   double Dummy, ValueRealPart, ValueImagPart;
////   char *OneLine = new char[buf_size];
////    complex<double>  I(0,1),cpxNr(0,0);
////
////   fstream inF;
////   inF.open(fileName,ios::in);
////   if(!inF)
//{
////      cout<<"File :"<<fileName<<" not found\n exiting program...\n";
////      mtkExit();
////   }
////   /*** Check the file to see how many data points ***/
////          do{
////              inF.getline(OneLine,buf_size);
////              NumberOfLines++;
////            }while(!inF.eof());
////            NumberOfLines--;
////            inF.close();
////          cout<<"Number Of complex points:\t"<<NumberOfLines/2<<"\n";
////          inF.open(fileName,ios::in);
////
////      for(row=1;row<Data->RSize() + 1;row++)
//{
////           cout<<"Col number"<<row<<"\n";
////           for(col = 1;col < (Data->CSize() + 1);col++)
//{
////               inF>>Dummy;                        /*** Dummy value ***/
////               Data->GetRowAxis()->Element(col) = Dummy;
////               inF>>Dummy;  /*** Dummy value ***/
////               Data->GetColAxis()->Element(row) = Dummy;  /*** Dummy value ***/
////               inF>>ValueRealPart;
////               cpxNr = complex<double> (ValueRealPart,0);
//////                 Data->data(row,col) = ValueRealPart;
////               Data->data(row,col) = cpxNr;
////           } /*** Complex part comes next ***/
////   }
////
////  for(row=1;row<Data->RSize() + 1;row++)
//{
////           for(col = 1;col < (Data->CSize() + 1);col++)
//{
////               inF>>Dummy;                        /*** Dummy value ***/
////               //Data->GetRowAxis()[col] = Dummy;
////               inF>>Dummy;  /*** Dummy value ***/
////               //Data->GetColAxis()[row] = Dummy;  /*** Dummy value ***/
////
////               inF>>ValueImagPart;
////               cpxNr = ValueImagPart*I;
////               Data->data(row,col) += cpxNr;
////           }
////   }
////   inF.close();
////   cout<<"Data is filled....\n";
////};
//
