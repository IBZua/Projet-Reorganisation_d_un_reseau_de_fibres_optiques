#ifndef __CHAINE_H__
#define __CHAINE_H__	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SVGwriter.h"

/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;

Chaines* lectureChaines(FILE *f);
void ecrireChaines(Chaines *C, FILE *f);
double longueurChaine(CellChaine *c);
double longueurTotale(Chaines *C);
int comptePointsTotal(Chaines *C);

int comptePoints(CellChaine *C);
CellPoint *creer_point(double x,double y);
CellChaine *creer_liste_chaine(int numero);
Chaines *creer_chaine(int gamma);
void ajout_point_chaine(CellChaine *lc, double x,double y);
void ajout_Chaines(Chaines *c, CellChaine *lc);

void afficheChainesSVG(Chaines *C, char* nomInstance);
double longueurChaine(CellChaine *c);
double longueurTotale(Chaines *C);
int comptePointsTotal(Chaines *C);
Chaines *generationAleatoire(int nbChaines,int nbPointsChaine,int xmax,int ymax);
void libererChaines(Chaines* C);
#endif	
