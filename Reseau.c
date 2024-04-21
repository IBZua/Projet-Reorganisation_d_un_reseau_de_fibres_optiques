#include "Reseau.h"
#include <stdlib.h>

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
	//si reseau vide
	if(!R){return 0;}
	//On parcourt chaque noeud du reseau tant que les coordonnees correspondent pas
	while(R->noeuds->nd && R->noeuds->nd->x != x && R->noeuds->nd->y != y){
		R->noeuds = R->noeuds->suiv;
	}
	//Si rien n'est trouve on cree le noeud aux coordonnees x y
	if(!R->noeuds->nd){
		//maj du nombre de noeud
		R->nbNoeuds++;
		//creation nouveau noeud
		Noeud* n = (Noeud*)malloc(sizeof(Noeud));
		n->x = x;
		n->y = y;
		n->num = R->nbNoeuds;
		n->voisins = NULL;
		R->noeuds->suiv->nd = n;
		//creation nouvelle cellnoeud
		CellNoeud* cn = (CellNoeud*)malloc(sizeof(CellNoeud));
		cn->nd = n;
		cn->suiv = R->noeuds;
		R->noeuds = cn;
		return n;
	}
	return R->noeuds->nd;
}

Reseau* reconstitueReseauListe(Chaines *C){
	//si chaine vide
	if(!C){return NULL;}
	
	Reseau* R = malloc(sizeof(Reseau));
	R->nbNoeuds = comptePointsTotal(C);
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

int nbCommodites(Reseau *R){
	//si reseau vide
	if(!R){return 0;}
	int cpt = 0;
	while(R->commodites){
		cpt++;
		R->commodites = R->commodites->suiv;
	}
	return cpt;
}

int nbLiaisons(Reseau*R){
	//si reseau vide
	if(!R){return 0;}
	int cpt = 0;
	//on check chaque noeud
	while(R->noeuds){
		//on check chaque liaison du noeud
		while(R->noeuds->nd->voisins){
			//on filtre les liaisons pour eviter les doublons
			if(R->noeuds->nd->voisins->nd->num < R->noeuds->nd->num){
				cpt++;
			}
			R->noeuds->nd->voisins = R->noeuds->nd->voisins->suiv;
		}
		R->noeuds = R->noeuds->suiv;
	}
	return cpt;
}

void ecrireReseau(Reseau*R,FILE*f){
	fprintf(f,"NbNoeuds: %d\n",R->nbNoeuds);
	int nbLiaison = nbLiaisons(R);
	int nbCommodite = nbCommodites(R);
	fprintf(f,"NbLiaisons: %d\n",nbLiaison);
	fprintf(f,"NbCommodites: %d\n",nbCommodite);
	fprintf(f,"Gamma: %d\n",R->gamma);
	fprintf(f,"\n");
	//la liste des noeuds
	for(int i = 0; i < R->nbNoeuds; i++){
		fprintf(f,"v %d %f %f\n", R->noeuds->nd->num, R->noeuds->nd->x, R->noeuds->nd->y);
	}
	fprintf(f,"\n");
	//la liste des voisins de chaque noeud
	//On parcourt la liste des noeuds du reseau
	for(int i = 0; i < R->nbNoeuds; i++){
		//on parcourt la liste des voisins de chaque noeud
		while(R->noeuds->nd->voisins){
			//si le num du voisin est inf au num du noeud on ecrit
			if(R->noeuds->nd->voisins->nd->num < R->noeuds->nd->num){
				fprintf(f,"l %d %d\n", R->noeuds->nd->voisins->nd->num, R->noeuds->nd->num);
			}
			R->noeuds->nd->voisins = R->noeuds->nd->voisins->suiv;
		}
	}
	fprintf(f,"\n");
	//la liste des commodites
	for(int i = 0; i < nbCommodite; i++){
		fprintf(f,"k %d %d\n", R->commodites->extrA->num, R->commodites->extrB->num);
	}
}
void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}
