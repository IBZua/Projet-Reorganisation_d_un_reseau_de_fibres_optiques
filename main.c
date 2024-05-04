#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "ArbreQuat.h"
int main(int argc, char* argv[]){
    /*INITIALISATION VARIABLES*/
    Reseau *r = NULL;
    printf("Input 1\n");
    FILE *fInput1 = fopen("00014_burma.cha", "r");
    printf("Input 2\n");
    FILE *fInput2 = fopen("07397_pla.cha", "r");
    printf("Input 3\n");
    FILE *fInput3 = fopen("05000_USA-road-d-NY.cha", "r");
    FILE *fOutput = fopen("mesures.txt", "w");
    printf("c1\n");
    Chaines *c1 = lectureChaines(fInput1);
    printf("c2\n");
    Chaines *c2 = lectureChaines(fInput2);
    printf("c3\n");
    Chaines *c3 = lectureChaines(fInput3);
    clock_t temps_debut;
    clock_t temps_fin;
    double temps;

    fprintf(fOutput, "type     instance_1      type                         instance_2    type                   instance_3\n");
    
    //Liste
    printf("Test Liste\n");
    fprintf(fOutput, "liste    ");
    //Instance 1: 00014_burma.cha
    temps_debut = clock();
    r = reconstitueReseauListe(c1); 
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    //Instance 2: 07397_pla.cha 
    temps_debut = clock();
    r = reconstitueReseauListe(c2); 
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    //Instance 3: 05000_USA-road-d-NY.cha
    temps_debut = clock();
    r = reconstitueReseauListe(c3); 
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    //Table Hachage
    printf("Test Hachage\n");
    //tailleMax = 10
    fprintf(fOutput, "  table hachage (taille 10)    ");
    // Instance 1: 00014_burma.cha
    temps_debut = clock();
    r = reconstitueReseauHachage(c1, 10);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    // Instance 2: 07397_pla.cha
    temps_debut = clock();
    r = reconstitueReseauHachage(c2, 10);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    // Instance 3: 05000_USA-road-d-NY.cha
    temps_debut = clock();
    r = reconstitueReseauHachage(c3, 10);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    //tailleMax = 1000
    fprintf(fOutput, "  table hachage (taille 1000)    ");
    // Instance 1: 00014_burma.cha
    temps_debut = clock();
    r = reconstitueReseauHachage(c1, 1000);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    // Instance 2: 07397_pla.cha
    temps_debut = clock();
    r = reconstitueReseauHachage(c2, 1000);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    // Instance 3: 05000_USA-road-d-NY.cha
    temps_debut = clock();
    r = reconstitueReseauHachage(c3, 1000);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    //tailleMax = 100000
    fprintf(fOutput, "  table hachage (taille 100000)    ");
    // Instance 1: 00014_burma.cha
    temps_debut = clock();
    r = reconstitueReseauHachage(c1, 100000);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    // Instance 2: 07397_pla.cha
    temps_debut = clock();
    r = reconstitueReseauHachage(c2, 100000);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    // Instance 3: 05000_USA-road-d-NY.cha
    temps_debut = clock();
    r = reconstitueReseauHachage(c3, 100000);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    //Arbre Quadratiques
    fprintf(fOutput, "Arbre Quadratiques     ");
    // Instance 1: 00014_burma.cha
    temps_debut = clock();
    r = reconstitueReseauArbre(c1);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    //Instance 2: 07397_pla.cha 
    temps_debut = clock();
    r = reconstitueReseauArbre(c2);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    //Instance 3: 05000_USA-road-d-NY.cha 
    temps_debut = clock();
    r = reconstitueReseauArbre(c3);
    temps_fin = clock();
    temps = ((double)(temps_fin - temps_debut))/CLOCKS_PER_SEC;
    fprintf(fOutput, "%f      ", temps);
    libereReseauListe(r);

    //Fermture et liberation ram
    libererChaines(c1);
    libererChaines(c2);
    libererChaines(c3);
    fclose(fInput1);
    fclose(fInput2);
    fclose(fInput3);
    return 0;
}