#include <stdio.h>
#include "Struct_File.h"
#include "Graphe.h"


int main(int argc, char * argv[]){
    if (argc != 2) {
        printf("Nombre de parametres incorrect\n");
        printf("./ReorganiseReseau [nom de l'instance]\n");
        return 1;
    }

   
    Reseau * r = NULL;
    FILE * f = fopen(argv[1], "r");
    
    printf("lectureChaines\n");
    Chaines * c = lectureChaines(f);
    printf("reconstitueReseauListe \n");
    r = reconstitueReseauListe(c);
    
    printf("creerGraphe\n");
    Graphe * g = creerGraphe(r);
    afficherGraphe(g);

    int ppnbarr = plusPetitNbArretes(g, 3, 9);
    printf("plusPetitNbArretes (entre 3 et 9) : %d\n",ppnbarr);

    printf("reorganiserReseau\n");
    int rr = reorganiseReseau(r);
    
    if (rr) {
        printf("Pour toute arête du graphe, le nombre de chaı̂nes qui passe par cette arête est inférieur à gamma\n\n");
    } else {
        printf("Il existe au moin une arete du graphe, telle que le nombre de chaı̂nes qui passe par cette arête est superieur à gamma\n\n");
    }
    
    libereReseauListe(r);
    libererChaines(c);
    libererGraphe(g);
    
    fclose(f);
}