#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"
#include "SVGwriter.h"


int main(int argc, char* argv[]){
	Chaines* c = (Chaines*)malloc(sizeof(Chaines));
	FILE *f = fopen(argv[1], "r");
	c = lectureChaines(f);
	fclose(f);
	afficheChainesSVG(c, "img1");
	f = fopen(argv[2],"w");
	printf("commence ecrire\n");
	ecrireChaines(c, f);
	fclose(f);
	printf("%d\n",comptePointsTotal(c));
	return 0;
}