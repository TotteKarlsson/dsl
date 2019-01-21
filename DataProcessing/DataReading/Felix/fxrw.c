#pragma hdrstop
/**fxrw.c**/
/*
      Felix I/O of 1-D data via C routines.    V 1.1    Oct, 1990
      Allows transparent sharing of binary data files by various
      platforms, where byte ordering of disk storage may differ.
      This method ASSUMES that internal bit interpretations of
      32-bit words are IDENTICAL on both platforms, and only byte
      order within each word when written/read from disk is to
      be unscrambled.
*/
 
#include <stdio.h>
#include <io.h>
#include <string.h>

#ifdef dos
#include <stdio.h>
#endif
  /* keep a byte map in retained area */
  static long map[5];
  /* keep the file descriptors for reading and writing */
#ifdef dos
  static FILE *luin = NULL;
  static FILE *luout = NULL;
#endif
#ifndef dos
  static int luin = 0;
  static int luout = 0;
#endif
  /* standard success and error values */
  long iok = 0;
  long ierr = -1;
/*************
      fxnopn   - open a new type data file for reading or writing
                 mode = 0 = open for reading
                        1 = open for writing a new file
                        2 = open for appending to existing file
*************/

#include "fxrw.h"
#include "bytes.h"

int FXNOPN(int* mode,char* name, int* len)
//  int *mode;
//  char *name;
//  int *len;
  {
    char cname[80];
    int llen;
    llen = *len;
    strncpy(cname,name,llen);
    cname[llen] = '\0';
    switch ((int) *mode) {
#ifdef dos
    case 0:
      luin = fopen(cname,"rb");
      if (luin == NULL) goto noifile;
      fseek(luin,0L,0);
      return(iok);
    case 1:
      luout = fopen(cname,"wb");
      if (luout == NULL) goto noifile;
      fseek(luout,0L,0);
      return(iok);
    case 2:
      luout = fopen(cname,"ab");
      if (luout == NULL) goto noifile;
      fseek(luout,0L,2);
      return(iok);
    default:
      return(ierr);
    }
#endif
#ifndef dos
    case 0:
      luin = open(cname,0);
      if (luin == -1) goto noifile;
      lseek(luin,0L,0);
      return(iok);
    case 1:
      luout = creat(cname,0644);
      if (luout == -1) goto noifile;
      lseek(luout,0L,0);
      return(iok);
    case 2:
      luout = open(cname,1);
      if (luout == -1) goto noifile;
      lseek(luout,0L,2);
      return(iok);
    default:
      return(ierr);
    }
#endif
  noifile:
    printf("file open failed:  %s\n",cname);
    return(ierr);
  }
/*************
      fxnclo   - close a new type data file
                 mode = 0 = close reading (input) file
                 mode = 1 = close writing (output) file
*************/
  long FXNCLO(mode)
  long *mode;
  {
/* only close a file that is "realy" open (i.e. fd > sterr) */
#ifdef dos
    if (*mode == 0) {
      if (luin != NULL) fclose(luin);
    }
    else {
      if (luout != NULL) fclose(luout);
    }
#endif
#ifndef dos
    if (*mode == 0) {
      if (luin > 2) close(luin);
    }
    else {
      if (luout > 2) close(luout);
    }
#endif
    return(iok);
  }
/*************
      fxnrea   - read a 1-D spectra from new type data file
*************/
  long FXNREA(n,data)
  long *n;
  long data[];
  {
    int one = 1;
    long lone = 1;
    int four = 4;
    long count;
    int cnt;
    long nread;
    int nbytes;
    *n = 0L;
    /* first read the # of words */
#ifdef dos
    nread = (long) fread(&count,four,one,luin);
    if (nread < 1) return(nread);
    if (nread != 1) return(ierr);
#endif
#ifndef dos
    nread = (long) read(luin,&count,4);
    if (nread < 1) return(nread);
    if (nread != 4) return(ierr);
#endif
    /* byte swap the count */
    BYTSWA(map,&lone,&count);
    if (count < 1) return(ierr);
    /* now read that many words of data */
#ifdef dos
    cnt = count;
    nread = (long) fread(data,four,cnt,luin);
    if (nread != count) return(ierr);
#endif
#ifndef dos
    nbytes = count * 4;
    nread = (long) read(luin,data,nbytes);
    if (nread != nbytes) return(ierr);
#endif
    /* byte swap the data */
    BYTSWA(map,&count,data);
    /* pass back # of points */
    *n = count;
    return(count);
  }
/*************
      fxnwri   - write a 1-D spectra to new type data file
*************/
  long FXNWRI(n,data)
  long *n;
  long data[];
  {
    int one = 1;
    int four = 4;
    long count;
    int cnt;
    long nwrit;
    int nbytes;
    count = (*n);
    if (count < 1) return(ierr);
    /* first write the # of words */
#ifdef dos
    nwrit = (long) fwrite(&count,four,one,luout);
    if (nwrit != 1) return(ierr);
#endif
#ifndef dos
    nwrit = (long) write(luout,&count,4);
    if (nwrit != 4) return(ierr);
#endif
    /* now write that many words of data */
#ifdef dos
    cnt = count;
    nwrit = (long) fwrite(data,four,cnt,luout);
    if (nwrit != count) return(ierr);
#endif
#ifndef dos
    nbytes = count * 4;
    nwrit = (long) write(luout,data,nbytes);
    if (nwrit != nbytes) return(ierr);
#endif
    /* pass back # of points */
    return(count);
  }
/*************
      fxnrhd - read a 1-D header from new type data file
*************/
  long FXNRHD(n,data)
  long *n;
  long data[];
  {
    int one = 1;
    long lone = 1;
    int four = 4;
    long key, count;
    int cnt;
    long nread, istat;
    int nbytes;
    long BYTMAP();
    /* first read the byte order key */
#ifdef dos
    nread = (long) fread(&key,four,one,luin);
    if (nread != 1) return(ierr);
#endif
#ifndef dos
    nread = (long) read(luin,&key,4);
    if (nread != 4) return(ierr);
#endif
    /* evaluate the byte key, and create the swapping map */
    istat = BYTMAP(&key,map);
    if (istat != 0) return(ierr);
    /* next read the # of words */
#ifdef dos
    nread = (long) fread(&count,four,one,luin);
    if (nread != 1) return(ierr);
#endif
#ifndef dos
    nread = (long) read(luin,&count,4);
    if (nread != 4) return(ierr);
#endif
    /* byte swap the count */
    BYTSWA(map,&lone,&count);
    if (count < 1) return(ierr);
    /* now read that many words of header */
#ifdef dos
    cnt = count;
    nread = (long) fread(data,four,cnt,luin);
    if (nread != count) return(ierr);
#endif
#ifndef dos
    nbytes = count * 4;
    nread = (long) read(luin,data,nbytes);
    if (nread != nbytes) return(ierr);
#endif
    /* byte swap the header contents */
    BYTSWA(map,&count,data);
    /* pass back # of words in header */
    *n = count;
    return(count);
  }
/*************
      fxnwhd - write a 1-D header to new type data file
*************/
  long FXNWHD(n,data)
  long *n;
  long data[];
  {
    int one = 1;
    int four = 4;
    long key, count;
    int cnt;
    long nwrit;
    long BYTKEY();
    int nbytes;
    /* first write the byte order key */
    key = BYTKEY();
#ifdef dos
    nwrit = (long) fwrite(&key,four,one,luout);
    if (nwrit != 1) return(ierr);
#endif
#ifndef dos
    nwrit = (long) write(luout,&key,4);
    if (nwrit != 4) return(ierr);
#endif
    /* next write the # of words */
    count = (*n);
#ifdef dos
    nwrit = (long) fwrite(&count,four,one,luout);
    if (nwrit != 1) return(ierr);
#endif
#ifndef dos
    nwrit = (long) write(luout,&count,4);
    if (nwrit != 4) return(ierr);
#endif
    /* now write that many words of header */
#ifdef dos
    cnt = count;
    nwrit = (long) fwrite(data,four,cnt,luout);
    if (nwrit != count) return(ierr);
#endif
#ifndef dos
    nbytes = count * 4;
    nwrit = (long) write(luout,data,nbytes);
    if (nwrit != nbytes) return(ierr);
#endif
    return(count);
  }
