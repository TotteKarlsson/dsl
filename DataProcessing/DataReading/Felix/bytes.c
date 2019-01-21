#pragma hdrstop
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

#include <stdio.h>
#include "bytes.h"

//#define BYTKEYP    bytkey
//#define BYTMAPP    bytmap
//#define BYTSWAP    bytswa

/*    define a scramble mapping scratch area, 4 bytes = 1 int
      (two words of storage defined as both byte and integer)  */
  struct bytbuf {
         union {
           char bitem[4];
           long iitem[1];
         } ub;
  } wordin, wordout;
 
  static long localkey = 0x04030201;
 
/*************
      bytkey - make the byte order key on local host machine.
*************/
  long BYTKEYP()
  {
    return(localkey);
  }
/*************
      bytmap - build a byte-swapping map from a foreign byte key.
               Given a byte key read in from a binary file header,
               compare the potentially scrambled key against the
               local key and build an "unscramble map" for use on
               all subsequent data read from that binary file.
*************/
  long bytmap(long* filekey,long  map[])
  //long *filekey;
  //long map[5];
  {
    int i, ival;
    int check[4];
    long map2[5];
    long BYTKEYP();
    long ierr = -1;
/* first field of map gets:  "yes/no scrabling"  1 = true = "keys
                                                     do not match" */
    map[0] = !((*filekey) == BYTKEYP());
/* if keys don't match, decode the given key... */
    if (map[0]) {
      wordin.ub.iitem[0] = *filekey;
/* prep to check that each value is seen exactly once */
      for (i=0; i<4; i++) check[i] = 0;
/* ...make a vector of integers 0,1,2,3 in the same order as the
   input key's byte values 1,2,3,4     */
      for (i=0; i<4; i++) {
        ival = ((int) wordin.ub.bitem[i]) - 1;
        if (ival < 0) goto badkey;
        if (ival > 3) goto badkey;
        if (check[ival]) goto badkey;
        check[ival] = 1;
        map2[i+1] = ival;
      }
/* map from foreign byte order is now ready;  but we now need
   to map from byte order to "bytes in an word" order...*/
      wordin.ub.iitem[0] = BYTKEYP();
      for (i=0; i<4; i++) {
        ival = ((int) wordin.ub.bitem[i]) - 1;
        if (ival < 0) goto badkey;
        if (ival > 3) goto badkey;
        check[i] = ival;
      }
/* combine the two maps */
      for (i=0; i<4; i++) map[i+1] = map2[check[i]+1];
 
    }
    else {
      for (i=0; i<4; i++) map[i+1] = i;
    }
    return(0);
  badkey:
    printf("Invalid byte key.\n");
    return(ierr);
  }
/*************
      bytswa - do byte swapping to an array of data.
               Once the map has been made, all data can be unscrambled
               one array at a time, in place.
*************/
void  bytswa(long map[5],long *n, long data[])
  //long map[5];            /* existing byte map */
  //long *n;                /* number of 32-bit words in "data" array */
  //long data[];            /* the array of data to be unscrambled */
  {
    long i, ii;
/* only need byte swapping when first map element non-zero */
    if (map[0]) {
/* do each word in the array one at a time */
      for (i=0; i<(*n); i++) {
/* move one word to scratch area */
        wordin.ub.iitem[0] = data[i];
/* shuffle the bytes into second scratch area */
        for (ii=0; ii<4; ii++)
                 wordout.ub.bitem[(map[ii+1])] = wordin.ub.bitem[ii];
/* move the one unscrambled word back into array */
        data[i] = wordout.ub.iitem[0];
      }
    }
    return;
}
