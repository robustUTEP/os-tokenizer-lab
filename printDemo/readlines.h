#ifndef ReadlinesIncluded
#define ReadlinesIncluded

int countLines(int fd, int *pMaxLineLen);
char **readLines(int fd, int *numLinesP, int *maxLineLenP);

#endif // included
