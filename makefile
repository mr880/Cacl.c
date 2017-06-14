all: calc format

calc: calc.c
	gcc -Wall -lm -o calc calc.c

format: format.c
	gcc -Wall -std=c99 -lm -o format format.c

clean:
	rm -f *.o calc format
