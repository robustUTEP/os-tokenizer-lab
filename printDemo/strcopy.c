#include "strcopy.h" 		/* for consistency */
#include "stdlib.h"		/* for malloc */

char *strcopy(char *inStr)	/* like strdup */
{
  char *pStr, *copy, *pCopy;
  size_t len;
  for (pStr = inStr; *pStr; pStr++) // count # chars in str
    ;
  len = pStr - inStr + 1;
  copy = pCopy = (char *)malloc(len); // allocate memory to hold  copy 
  for (pStr = inStr; *pStr; pStr++) // duplicate 
    *(pCopy++) = *pStr;
  *pCopy = 0;			// terminate copy 
  return copy;
}
