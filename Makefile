CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CC = gcc

PROGRAMS = main

.PHONY: all clean

all: $(PROGRAMS)

SVGwriter.o: SVGwriter.c
	$(CC) $(CFLAGS) -c $<

Chaine.o: Chaine.c
	$(CC) $(CFLAGS) -c $<

ChaineMain.o: ChaineMain.c
	$(CC) $(CFLAGS) -c $<

main: Chaine.o ChaineMain.o SVGwriter.o
	$(CC) -o $@ $^ $(CFLAGS) -lm
	
clean:
	rm -f *.o *~ $(PROGRAMS)
