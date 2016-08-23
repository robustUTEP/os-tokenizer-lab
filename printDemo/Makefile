all: printFile

CFLAGS = -g -O2

printFile: printFile.o strcopy.o readlines.o
	cc -o printFile printFile.o strcopy.o readlines.o
clean:
	rm -f  *.o printFile printFile.exe
