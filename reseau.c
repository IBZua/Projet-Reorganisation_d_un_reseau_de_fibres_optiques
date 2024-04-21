#include "Reseau.h"
#include "Chaine.h"
#include <stdlib.h>
#include <stdio.h>

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
	while(R->noeuds->nd && R->noeuds->nd->x != x && R->noeuds->nd->y != y){
		R->noeuds = R->noeuds->suiv;
	}
	if(!R->noeuds->nd){
		R->nbNoeuds++;
		Noeud* n = malloc(sizeof(Noeud));
		n->x = x;
		n->y = y;
		n->num = R->nbNoeuds;
		R->noeuds->suiv->nd = n;
		return n;
	}
	return R->noeuds->nd;
}

Reseau* reconstitueReseauListe(Chaines *C){
	Reseau* R = malloc(sizeof(Reseau));
	R->nbNoeuds = comptePointsTotal(C);
	R->gamma = C->gamma;
	R->noeuds = malloc(sizeof(CellNoeud));
	
	CellPoint* prec = malloc(sizeof(CellPoint));
	
	while(C->chaines){
	
		R->commodites->extrA = rechercheCreeNoeudListe(R, C->chaines->points->x, C->chaines->points->y);
		prec = C->chaines->points;
		//peut etre oublie de mettre le premier noeud dans le liste  //|
		C->chaines->points = C->chaines->points->suiv;               //|
																	 //|
		while(C->chaines->points->suiv != NULL){				     //V ici
				R->noeuds->nd = rechercheCreeNoeudListe(R, C->chaines->points->x, C->chaines->points->y);
				R->noeuds->nd->voisins->nd = rechercheCreeNoeudListe(R, prec->x, prec->y);
				R->noeuds->nd->voisins->suiv->nd = rechercheCreeNoeudListe(R, C->chaines->points->suiv->x, C->chaines->points->suiv->y);
				prec = C->chaines->points;
				C->chaines->points = C->chaines->points->suiv;
		
		}
		
		//C->chaines->points = C->chaines->points->suiv;
		R->commodites->extrB = rechercheCreeNoeudListe(R, C->chaines->points->x, C->chaines->points->y);
		R->commodites = R->commodites->suiv;
		C->chaines = C->chaines->suiv;
	}
	return R;
}
