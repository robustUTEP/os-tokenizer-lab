#include <sys/types.h>		/* for lseek, read */
#include <unistd.h>		/* for lseek, read */
#include <sys/stat.h>		/* for read */
#include <fcntl.h>		/* for read */
#include <stdlib.h>		/* for malloc */
#include <assert.h>		/* for assert */

#include "assert2.h"		/* for assert2 */
#include "strcopy.h"  		/* for strcopy */
#include "readlines.h"		/* for consistency */

#define BUFLEN 4096		/* read buffer length */

char *copyStrN(char *str, int numChars) /* fresh zero-terminated copy of N chars from str  */
{
  char *copy = (char *)malloc(numChars + 1);
  assert2(copy, "Can't alloc memory for line copy");
  char *copyP = copy, *pStrLast = str + numChars;
  while (str != pStrLast) 
    *(copyP++) = *(str++);
  *copyP = 0;			/* terminate copy */
  return copy;
}

// Count the number of lines in open file fd.
// Also computes maximum line length
int countLines(int fd, int *pMaxLineLen)
{
  char buf[BUFLEN], *pBuf, *pBufLimit; /* read buffer */
  char curChar;		       /* current character */
  int numBytesRead;	       /* from last read */
  int numLines = 0, lineLen = 0, maxLineLen = 0;
  
  while(numBytesRead = read(fd, &buf, BUFLEN)) { /* until end of file... */
    assert2(numBytesRead > 0, "error reading file");
    pBufLimit = buf + numBytesRead; // immediately following last byte read 
    for (pBuf = buf; pBuf != pBufLimit; pBuf++) { // ...every character in buf
      curChar = *pBuf;
      if (curChar == '\n') {
	numLines++;
	maxLineLen = lineLen > maxLineLen ? lineLen : maxLineLen;
	lineLen = 0;
      } else 
	lineLen ++;
    }
  }
  if (curChar != '\n') { // notice if last line isn't terminated
    numLines++;
    maxLineLen = lineLen > maxLineLen ? lineLen : maxLineLen; /* maxLineLen = max(lineLen, maxLineLen) */
  }
  if (pMaxLineLen) *pMaxLineLen = maxLineLen;
  return numLines;
}

// Reads lines from open fd
// Fd must be seekable
// Returns 0 terminated vector of strings
//   Also, sets *numLinesP and *maxLineLenP if nonzero.
char **readLines(int fd, int *numLinesP, int *maxLineLenP)
{
  int numBytesRead, numLines, maxLineLen;
  char readBuf[BUFLEN], *pReadBuf, *pReadBufLimit, curChar;
  char **lines, *lineBuf, **pLines;
  off_t fileOffset;

  // determine # of lines & maximum line len
  fileOffset = lseek(fd, 0, SEEK_CUR); /* save initial file offset */
  assert2(fileOffset >= 0, "input file must be seekable");  

  numLines = countLines(fd, &maxLineLen); 

  fileOffset = lseek(fd, fileOffset, SEEK_SET); /* rewind file */
  assert2(fileOffset >= 0, "can't rewind file");

  /* allocate vector to store lines */
  pLines = lines = (char **)malloc(sizeof(char*) * (numLines + 1)); 
  assert2(lines, "can't allocate memory to store vector of input lines");
  
  lineBuf = (char *)malloc(maxLineLen+1); /* allocate line buffer */
  assert2(lineBuf, "can't allocate linebuf");
  
  /* read and copy lines from file into lines */
  char *pLineBuf = lineBuf;
  while (numBytesRead = read(fd, &readBuf, BUFLEN)) { /* read until end of file */
    assert2(numBytesRead >= 0, "error reading input file");
    char *pReadBufLimit = readBuf + numBytesRead;
    for (pReadBuf = readBuf; pReadBuf != pReadBufLimit; pReadBuf++) {
      curChar = *pReadBuf;
      if (curChar == '\n') {	// line terminator found
	*(pLines++) = copyStrN(lineBuf, pLineBuf - lineBuf);
	pLineBuf = lineBuf;	// reset lineBuf before reading next line
      } else			/* append current char into lineBuf */
	*(pLineBuf++) = curChar;
    }
    if (pLineBuf != lineBuf)	/* last line was not terminated by a newline */
      *(pLines++) = copyStrN(lineBuf, pLineBuf - lineBuf);
  }
  assert(pLines - lines == numLines);
  *pLines = 0;			/* terminate vector */
  free(lineBuf);
  return lines;
}
