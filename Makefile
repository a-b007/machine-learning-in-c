run: fileio.o main.o regression.o
	gcc -o run fileio.o main.o regression.o

fileio.o: fileio.c fileio.h
	gcc -c fileio.c

main.o: main.c fileio.h regression.h
	gcc -c main.c

regression.o: regression.c regression.h
	gcc -c regression.c

clean:
	rm -f *.o run