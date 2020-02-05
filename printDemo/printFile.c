// for puts
#include <stdio.h>

// for exit
#include <stdlib.h>

// for perror
#include <errno.h>

// for open()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// for close
#include <unistd.h>

#include "readlines.h"
#include "assert2.h"

int main(int argc, char **argv) {

  int ifd, ofd = 1;		/* file descriptors (1=default output) */

  char **lines, **pLines;
  int lineNum = 0, maxLineLen;

  /* checked if invoked correctly */
  if (argc != 2) {		/* one parameter expected */
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(1);
  }

  /* read lines from input file */
  ifd = open(argv[1], O_RDONLY);
  if (ifd < 0) {
    fputs(argv[0], stderr);
    perror(": can't open input file");
    exit(1);
  }
  lines = readLines(ifd, 0, &maxLineLen);
  close(ifd);

  /* print lines */
  {
    for (pLines = lines; *pLines; pLines++) {
      printf("%06d:\t%s\n", ++lineNum, *pLines);
      free(*pLines);
    }
  }
  free(lines);
  fflush(stdout);
  return 0;
}

  
