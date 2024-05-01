#include "Reseau.h"

#include <stdlib.h>

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
	//si reseau vide
	if(!R){return 0;}
	
	CellNoeud *ncour = R->noeuds;
	//On parcourt chaque noeud du reseau tant que les coordonnees correspondent pas
	while((ncour) && (ncour->nd->x != x) && (ncour->nd->y != y)){
		ncour = ncour->suiv;
	}
	
	//Si rien n'est trouve on cree le noeud aux coordonnees x y
	if(!ncour){
		
		//creation nouveau noeud
		Noeud* n = (Noeud*)malloc(sizeof(Noeud));
		n->num = R->nbNoeuds + 1;
		n->x = x;
		n->y = y;
		n->voisins = NULL;
		//creation nouvelle cellnoeud
		CellNoeud* cn = (CellNoeud*)malloc(sizeof(CellNoeud));
		cn->nd = n;
		cn->suiv = R->noeuds;
		R->noeuds = cn;
		//maj du nombre de noeud
		R->nbNoeuds++;
		
		return n;
		
	}
	
	return ncour->nd;
}

void insererVoisin(Noeud *N, Noeud *V){
	CellNoeud* listev = N->voisins;
	while((listev)&&(listev->nd != V)){
		listev = listev->suiv;
	}
	if(!listev){
		listev = (CellNoeud*)malloc(sizeof(CellNoeud));
		listev->nd = V;
		listev->suiv = N->voisins;
		N->voisins = listev;
	}
	
	
}

Reseau* reconstitueReseauListe(Chaines *C){
	
	//si chaine vide
	if(!C){return NULL;}
	//INITIALISATION RESEAU
	Reseau *R = (Reseau*)malloc(sizeof(Reseau));
	R->nbNoeuds = 0; //comptePointsTotal(C); //m
	R->gamma = C->gamma;
	R->noeuds = NULL;
	R->commodites = NULL;
	//Initialisation prec pour parcourir voisins
	//CellPoint* prec = NULL;//(CellPoint*)malloc(sizeof(CellPoint));
	
	CellCommodite* com = NULL;
	
	
	
	CellChaine *chainecour = C->chaines;
	CellPoint * pointcour = NULL;
	//On parcourt les chaines
	while(chainecour){
		pointcour = chainecour->points;
		
		com = (CellCommodite*)malloc(sizeof(CellCommodite));
		
		Noeud* nd_pointcour = NULL;
		Noeud* nd_prec = NULL;

		//On parcourt les points de la chaine
		while(pointcour){
			//Ajout de noeud
			nd_pointcour = rechercheCreeNoeudListe(R, pointcour->x, pointcour->y);
			//R->noeuds->nd 
			//printf("aj point x et y de: %f %f\n", pointcour->x, pointcour->y);
			
			if(nd_prec){
				// verifier si nd_prec est voisins de nd_pointcour et si nd_pointcour est voisin de nd prec
				//Ajout de precedent dans voisins
				
				insererVoisin(nd_pointcour, nd_prec);
				insererVoisin(nd_prec, nd_pointcour);

				//printf("%f %f \n",R->noeuds->nd->voisins->nd->x, R->noeuds->nd->voisins->nd->y);
				printf("aj prec\n");
			}else{
				//On est dans le premier point 
				com->extrA = nd_pointcour;
			}
			
			nd_prec = nd_pointcour;
			pointcour = pointcour->suiv;
		}
		// dans nd_pred on aura le deuxieme noeud de la commadite (extraB)
		//On maj commodite B
		com->extrB = nd_pointcour;
		//printf("%f,%f\n", R->commodites->extrA->x, R->commodites->extrB->x);
		com->suiv = R->commodites;
		R->commodites = com;
		
		chainecour = chainecour->suiv;
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

void ecrireReseau(Reseau*R, FILE*f){
	fprintf(f,"NbNoeuds: %d\n",R->nbNoeuds);
	int nbLiaison = nbLiaisons(R);
	int nbCommodite = nbCommodites(R);
	fprintf(f,"NbLiaisons: %d\n",nbLiaison);
	fprintf(f,"NbCommodites: %d\n",nbCommodite);
	fprintf(f,"Gamma: %d\n",R->gamma);
	fprintf(f,"\n");
	//la liste des noeuds
	while(R->noeuds){
		fprintf(f,"v %d %f %f\n", R->noeuds->nd->num, R->noeuds->nd->x, R->noeuds->nd->y);
		R->noeuds = R->noeuds->suiv;
	}
	fprintf(f,"\n");

	CellNoeud * voisins = NULL;
	//la liste des voisins de chaque noeud
	//On parcourt la liste des noeuds du reseau
	while(R->noeuds){
		//on parcourt la liste des voisins de chaque noeud
		voisins = R->noeuds->nd->voisins;
		while(voisins){
			//si le num du voisin est inf au num du noeud on ecrit
			if(R->noeuds->nd->voisins->nd->num < R->noeuds->nd->num){
				fprintf(f,"l %d %d\n", R->noeuds->nd->voisins->nd->num, R->noeuds->nd->num);
			}
			R->noeuds->nd->voisins = R->noeuds->nd->voisins->suiv;
		}
		R->noeuds = R->noeuds->suiv;
	}
	fprintf(f,"\n");
	//la liste des commodites
	
	while(R->commodites){
		fprintf(f,"k %d %d\n", R->commodites->extrA->num, R->commodites->extrB->num);
		R->commodites = R->commodites->suiv;
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
