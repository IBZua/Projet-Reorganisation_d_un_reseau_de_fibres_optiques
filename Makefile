CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CC = gcc

PROGRAMS = main ReseauMain

.PHONY: all clean

all: $(PROGRAMS)

Hachage.o: Hachage.c
	$(CC) $(CFLAGS) -c $<

Reseau.o: Reseau.c
	$(CC) $(CFLAGS) -c $<

SVGwriter.o: SVGwriter.c
	$(CC) $(CFLAGS) -c $<

Chaine.o: Chaine.c
	$(CC) $(CFLAGS) -c $<

ChaineMain.o: ChaineMain.c
	$(CC) $(CFLAGS) -c $<

ReseauMain.o: ReseauMain.c
	$(CC) $(CFLAGS) -c $<

main: Chaine.o ChaineMain.o SVGwriter.o Reseau.o
	$(CC) -o $@ $^ $(CFLAGS) -lm

ReseauMain: Chaine.o SVGwriter.o Reseau.o Hachage.o ReseauMain.o
	$(CC) -g -o $@ $^ $(CFLAGS) -lm

clean:
	rm -f *.o *~ $(PROGRAMS)
