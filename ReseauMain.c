#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hachage.h"
#include "SVGwriter.h"

int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Nombre de parametres incorrect\n");
        printf("./ReseauMain [type structure]\n");
        printf("1: liste; 2: table hachage; 3: arbre\n");
        return 1;
    }
    FILE *f = fopen("00014_burma.cha","r");
    Chaines * c = lectureChaines(f);
    Reseau *R = NULL;

    if (atoi(argv[1]) == 1){
        //Methode liste
        printf("reconstitueReseauListe\n");
        R = reconstitueReseauListe(c);
        printf("afficheReseauSVG\n");
        afficheReseauSVG(R, "reseauListe");
        printf("ecrireReseau\n");
        ecrireReseau(R, fopen("reseauListe.txt", "w"));
        return 0;
    }
    if (atoi(argv[1]) == 2){
        //Methode hachage
        R = reconstitueReseauHachage(c, comptePointsTotal(c));
        afficheReseauSVG(R, "reseauHachage");
        ecrireReseau(R, fopen("reseauHachage.txt", "w"));
        return 0;
    }
    if (atoi(argv[1]) == 3){
        //Methode arbre
        
        return 0;
    }
    fclose(f);
    return 0;
}