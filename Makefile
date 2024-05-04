CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CC = gcc

PROGRAMS = main ReseauMain ChaineMain GenRMain

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

ArbreQuat.o: ArbreQuat.c
	$(CC) $(CFLAGS) -c $<

ChaineMain.o: ChaineMain.c
	$(CC) $(CFLAGS) -c $<

main.o: main.c
	$(CC) $(CFLAGS) -c $<

ReseauMain.o: ReseauMain.c
	$(CC) $(CFLAGS) -c $<

GenRMain.o: GenRMain.c
	$(CC) $(CFLAGS) -c $<

GenRMain: Chaine.o SVGwriter.o Reseau.o Hachage.o ArbreQuat.o GenRMain.o
	$(CC) -o $@ $^ $(CFLAGS) -lm

main: Chaine.o SVGwriter.o Reseau.o Hachage.o ArbreQuat.o main.o
	$(CC) -o $@ $^ $(CFLAGS) -lm

ChaineMain: Chaine.o ChaineMain.o SVGwriter.o Reseau.o
	$(CC) -g -o $@ $^ $(CFLAGS) -lm

ReseauMain: Chaine.o SVGwriter.o Reseau.o Hachage.o ArbreQuat.o ReseauMain.o
	$(CC) -g -o $@ $^ $(CFLAGS) -lm

clean:
	rm -f *.o *~ $(PROGRAMS)
