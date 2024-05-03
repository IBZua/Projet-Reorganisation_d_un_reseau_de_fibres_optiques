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
    FILE *finput = fopen("00014_burma.cha","r");
    FILE *foutput;
    Chaines * c = lectureChaines(finput);
    Reseau *R = NULL;

    switch(atoi(argv[1])){
        case 1:
            //Methode liste
            printf("reconstitueReseauListe\n");
            R = reconstitueReseauListe(c);
            printf("afficheReseauSVG\n");
            afficheReseauSVG(R, "reseauListe");
            printf("ecrireReseau\n");
            foutput = fopen("reseauListe.txt", "w");
            ecrireReseau(R, foutput);
            libereReseauListe(R);
            break;
        case 2:
            //Methode hachage
            printf("reconstitueReseauHachage\n");
            R = reconstitueReseauHachage(c, comptePointsTotal(c));
            printf("afficheReseauSVG\n");
            afficheReseauSVG(R, "reseauHachage");
            foutput = fopen("reseauHachage.txt", "w");
            ecrireReseau(R, foutput);
            libereReseauListe(R);
            break;
        case 3:
            //Methode arbre
            break;
        default: 
            printf("Parametres incorrect\n");
            printf("./ReseauMain [type structure]\n");
            printf("1: liste; 2: table hachage; 3: arbre\n");
            break;
    }
    libererChaines(c);
    fclose(finput);
    fclose(foutput);
    return 0;
}