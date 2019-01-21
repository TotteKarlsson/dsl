#ifndef fxrwH
#define fxrwH
/**fxrw.h**/
//This header was written by mtk...
//put the prototypes here..
/*
      Felix I/O of 1-D data via C routines.    V 1.1    Oct, 1990
      Allows transparent sharing of binary data files by various
      platforms, where byte ordering of disk storage may differ.
      This method ASSUMES that internal bit interpretations of
      32-bit words are IDENTICAL on both platforms, and only byte
      order within each word when written/read from disk is to
      be unscrambled.
*/

#define FXNOPN    fxnopn
#define FXNCLO    fxnclo
#define FXNREA    fxnrea
#define FXNRHD    fxnrhd
#define FXNWHD    fxnwhd
#define FXNWRI    fxnwri
#define BYTKEY    bytkey
#define BYTMAP    bytmap
#define BYTSWA    bytswa

//#include ".\..\mtkCommon\MTK_DATAer.h"
//int  MTK_DATA FXNOPN(int *mode, char* name, int* len);
//long MTK_DATA FXNREA(long* n, long data[]);
//long FXNREA(long* n, long data[]);
#endif
