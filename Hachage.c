#include <math.h>
#include <stdlib.h>
#include "Hachage.h"

double cle(double x, double y){
    return y + (x + y) * (x + y + 1) * 1.0 / 2;
}

int hachage(int m, double k){
    double A = (sqrt(5)-1)/2;
    return m*(k*A-(k*A));
}

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){
    //si reseau vide
	if(!R){return 0;}
    //On cree la cle et on calcul l'index dans H
    double c = cle(x,y);
    int index = hachage(c, H->tailleMax);
    //On se positionne a l'index
    CellNoeud *CNH = (H->T)[index];
    //On parcourt chaque noeud du reseau tant que les coordonnees correspondent pas
    while(CNH && CNH->nd->x != x && CNH->nd->y != y){
        CNH = CNH->suiv;
    }
	//Si rien n'est trouve on cree le noeud aux coordonnees x y
	if(!CNH){
		//maj du nombre de noeud
		R->nbNoeuds++;
        H->nbElement++;
		//creation nouveau noeud
		Noeud* n = (Noeud*)malloc(sizeof(Noeud));
		n->x = x;
		n->y = y;
		n->num = R->nbNoeuds+1;
		n->voisins = NULL;
		//creation nouvelle cellnoeud
		CellNoeud* cn = (CellNoeud*)malloc(sizeof(CellNoeud));
		cn->nd = n;
		cn->suiv = R->noeuds;
		R->noeuds = cn;
        //ajout dans H
        CellNoeud *nouvCellH = (CellNoeud*)malloc(sizeof(CellNoeud));
        nouvCellH->nd = n;
        nouvCellH->suiv = (H->T)[index];
		return n;
	}
	return CNH->nd;
}

Reseau* reconstitueReseauHachage(Chaines *C, int m){
	//si chaine vide
	if(!C){return NULL;}
	
	Reseau* R = malloc(sizeof(Reseau));
	R->nbNoeuds = m;
	R->gamma = C->gamma;
	R->noeuds = malloc(sizeof(CellNoeud));
	
	CellPoint* prec = malloc(sizeof(CellPoint));
	
	while(C->chaines){
	
		R->commodites->extrA = rechercheCreeNoeudListe(R, C->chaines->points->x, C->chaines->points->y);
		prec = C->chaines->points;
		C->chaines->points = C->chaines->points->suiv;
		
		while(C->chaines->points){
			if(C->chaines->points->suiv != NULL){
				R->noeuds->nd = rechercheCreeNoeudListe(R, C->chaines->points->x, C->chaines->points->y);
				R->noeuds->nd->voisins->nd = rechercheCreeNoeudListe(R, prec->x, prec->y);
				R->noeuds->nd->voisins->suiv->nd = rechercheCreeNoeudListe(R, C->chaines->points->suiv->x, C->chaines->points->suiv->y);
				prec = C->chaines->points;
				C->chaines->points = C->chaines->points->suiv;
			}
			else{
				break;
			}
		}
		
		C->chaines->points = C->chaines->points->suiv;
		R->commodites->extrB = rechercheCreeNoeudListe(R, C->chaines->points->x, C->chaines->points->y);
		R->commodites = R->commodites->suiv;
		C->chaines = C->chaines->suiv;
	}
	return R;
}
