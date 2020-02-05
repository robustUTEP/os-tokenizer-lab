#beginning of Makefile

all: printFile

CFLAGS = -g -O2

printFile: printFile.o strcopy.o readlines.o
	${CC} -o $@ $^		# clever aliases: $@ = output $^ = input
clean:
	rm -f  *.o printFile printFile.exe

demo: printFile
	./printFile Makefile

# end of Makefile
