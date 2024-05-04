#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ArbreQuat.h"

/* Q 6.3 */
int main(void) {
    srand((unsigned)time(NULL));
  
    clock_t temps_debut;
    clock_t temps_fin;
    double temps;
    
    FILE *f1 = fopen("sortie_liste.txt", "w");
    FILE *f2 = fopen("sortie_HABR.txt", "w");
    Reseau *R = NULL;
    Chaines *chaines = NULL;
    
    int nbPointsChaine = 100;
    int xmax = 5000;
    int ymax = 5000;
    int nbChaines = 500;
    
    for (nbChaines = 500 ; nbChaines <= 5000 ; nbChaines += 500) {
        printf("nbChaines = %d\n", nbChaines);
        chaines = generationAleatoire(nbChaines, nbPointsChaine, xmax, ymax);
        
        //liste
        fprintf(f1, "%d ", nbChaines);
        temps_debut = clock();
        R = reconstitueReseauListe(chaines);
        temps_fin = clock();
        temps = ((double)(temps_fin - temps_debut)) / CLOCKS_PER_SEC;
        fprintf(f1, "%f\n", temps);
        libereReseauListe(R);
        
        // table de hachage et arbre
        fprintf(f2, "%d ", nbChaines);
        
        // temps de calcul pour la table de hachage
        //taille 5000 
        temps_debut = clock();
        R = reconstitueReseauHachage(chaines, 5000);
        temps_fin = clock();
        temps = ((double)(temps_fin - temps_debut)) / CLOCKS_PER_SEC;
        fprintf(f2, "%f ", temps);
        libereReseauListe(R);
        
        // taille 50000
        temps_debut = clock();
        R = reconstitueReseauHachage(chaines, 50000);
        temps_fin = clock();
        temps = ((double)(temps_fin - temps_debut)) / CLOCKS_PER_SEC;
        fprintf(f2, "%f ", temps);
        libereReseauListe(R);
        
        //taille 500000
        temps_debut = clock();
        R = reconstitueReseauHachage(chaines, 500000);
        temps_fin = clock();
        temps = ((double)(temps_fin - temps_debut)) / CLOCKS_PER_SEC;
        fprintf(f2, "%f ", temps);
        libereReseauListe(R);
        
        // temps de calcul pour l'arbre
        temps_debut = clock();
        R = reconstitueReseauArbre(chaines);
        temps_fin = clock();
        temps = ((double)(temps_fin - temps_debut)) / CLOCKS_PER_SEC;
        fprintf(f2, "%f\n", temps);
        libereReseauListe(R);
        
        libererChaines(chaines);
    }
    
    fclose(f1);
    fclose(f2);

    return 0;
}