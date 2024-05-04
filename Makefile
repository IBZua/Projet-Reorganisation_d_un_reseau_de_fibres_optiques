CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CC = gcc

PROGRAMS = main ReseauMain GrapheMain

.PHONY: all clean

all: $(PROGRAMS)

ArbreQuat.o: ArbreQuat.c
	$(CC) $(CFLAGS) -c $<

Hachage.o: Hachage.c
	$(CC) $(CFLAGS) -c $<

Reseau.o: Reseau.c
	$(CC) $(CFLAGS) -c $<

SVGwriter.o: SVGwriter.c
	$(CC) $(CFLAGS) -c $<

Chaine.o: Chaine.c
	$(CC) $(CFLAGS) -c $<

Graphe.o: Graphe.c
	$(CC) $(CFLAGS) -c $<

Struct_File.o: Struct_File.c
	$(CC) $(CFLAGS) -c $<

Struct_Liste.o: Struct_Liste.c
	$(CC) $(CFLAGS) -c $<

main.o: main.c
	$(CC) $(CFLAGS) -c $<

ChaineMain.o: ChaineMain.c
	$(CC) $(CFLAGS) -c $<

ReseauMain.o: ReseauMain.c
	$(CC) $(CFLAGS) -c $<

GrapheMain.o: GrapheMain.c 
	$(CC) $(CFLAGS) -c $<

main: Chaine.o SVGwriter.o Reseau.o Hachage.o ArbreQuat.o main.o
	$(CC) -o $@ $^ $(CFLAGS) -lm

ReseauMain: Chaine.o SVGwriter.o Reseau.o Hachage.o ReseauMain.o ArbreQuat.o
	$(CC) -g -o $@ $^ $(CFLAGS) -lm

GrapheMain: Chaine.o SVGwriter.o Reseau.o GrapheMain.o Struct_File.o Struct_Liste.o Graphe.o
	$(CC) -g -o $@ $^ $(CFLAGS) -lm

clean:
	rm -f *.o *~ $(PROGRAMS)
