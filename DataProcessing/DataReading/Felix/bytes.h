#ifndef bytesH
#define bytesH
/**bytes.c**/
/*
      Byte Unscramble manipulation routines.    V 1.1   Oct, 1990
      Allows transparent sharing of binary data files by various
      platforms, where byte ordering of disk storage may differ.
      This method ASSUMES that internal bit interpretations of
      32-bit words are IDENTICAL on both platforms, and only byte
      order within each word when written/read from disk is to
      be unscrambled.
      Usage:  1.  when writing a new binary file, include a byte
                  key in the header.  call function "bytkey()" to
                  get the integer value of the byte key for inclusion
                  in the new file header.
              2.  when reading the binary file, extract the byte key
                  from the header and create a byte map by calling
                  the function "bytmap(filekey,map)".
                  The map is an integer array with 5elements, where
                  the first element will be zero when the keys match.
                  Define storage for the map array in a static global
                  area.
              3.  Pass all other data read from the file through the
                  filter routine "bytswa(map,n,data)".  The array of
                  data is returned with every word in the proper byte
                  order for the local host machine.
*/



//#define BYTKEYP    bytkey
//#define BYTMAPP    bytmap
//#define BYTSWAP    bytswa

#include ".\..\Common\MTK_DATAer.h"
void MTK_DATA bytswa(long map[5], long *n, long data[]);
long MTK_DATA bytmap(long* filekey, long map[5]);
long MTK_DATA bytkey();

#endif




