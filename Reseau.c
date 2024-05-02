#include "Reseau.h"
#include <stdlib.h>

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
	//si reseau vide
	if(!R){return 0;}
	
	CellNoeud *ncour = R->noeuds;
	//On parcourt chaque noeud du reseau tant que les coordonnees correspondent pas
	while((ncour) && ((ncour->nd->x != x) || (ncour->nd->y != y))){
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
	R->nbNoeuds = 0 ; 
	R->gamma = C->gamma;
	R->noeuds = NULL;
	R->commodites = NULL;
	
	CellCommodite* com = NULL;
	
	CellChaine *chainecour = C->chaines;
	CellPoint * pointcour = NULL;
	//On parcourt les chaines
	while(chainecour){
		printf("------------\n");
		pointcour = chainecour->points;
		
		com = (CellCommodite*)malloc(sizeof(CellCommodite));
		
		Noeud* nd_pointcour = NULL;
		Noeud* nd_prec = NULL;
		//On parcourt les points de la chaine
		while(pointcour){
			//Ajout de noeud
			nd_pointcour = rechercheCreeNoeudListe(R, pointcour->x, pointcour->y);
			printf("nb-noeud: %d -- x: %f  y: %f\n", R->nbNoeuds, pointcour->x, pointcour->y);
			
			if(nd_prec){
				// verifier si nd_prec est voisins de nd_pointcour et si nd_pointcour est voisin de nd prec
				//Ajout de precedent dans voisins
				insererVoisin(nd_pointcour, nd_prec);
				insererVoisin(nd_prec, nd_pointcour);
			}else{
				com->extrA = nd_pointcour;
				printf("extrA x:%f  y;%f \n", com->extrA->x, com->extrA->y);
			}
			nd_prec = nd_pointcour;
			pointcour = pointcour->suiv;
		}
		// dans nd_pred on aura le deuxieme noeud de la commadite (extraB)
		//On maj commodite B
		com->extrB = nd_prec;
		printf("extrB x:%f  y;%f \n", com->extrB->x, com->extrB->y);
		com->suiv = R->commodites;
		R->commodites = com;
		
		chainecour = chainecour->suiv;
	}
	return R;
}

int nbCommodites(Reseau *R){
	//si reseau vide
	if(!R){return 0;}
	CellCommodite* comd = R->commodites;
	//on traite le premier manualement
	int cpt = 0;
	while(comd){
		cpt++;
		comd = comd->suiv;
	}
	return cpt;
}

int nbLiaisons(Reseau* R){
	//si reseau vide
	if(!R){return 0;}
	CellNoeud* cn = R->noeuds;
	int cpt = 0;
	//on check chaque noeud
	while(cn){
		//on check chaque liaison du noeud
		while(cn->nd->voisins){
			
			//on filtre les liaisons pour eviter les doublons
			if(cn->nd->voisins->nd->num < cn->nd->num){
			
				cpt++;
			}
			cn->nd->voisins = cn->nd->voisins->suiv;
		}
		cn = cn->suiv;
	}
	return cpt;
}

void ecrireReseau(Reseau* R, FILE* f){
		
	fprintf(f,"NbNoeuds: %d\n",R->nbNoeuds);
	
	int nbLiaison = nbLiaisons(R);
	printf("nbL: %d\n", nbLiaison);
	int nbCommodite = nbCommodites(R);
	printf("nbC: %d\n", nbCommodite);
	
	
	fprintf(f,"NbLiaisons: %d\n",nbLiaison);
	fprintf(f,"NbCommodites: %d\n",nbCommodite);
	fprintf(f,"Gamma: %d\n",R->gamma);
	fprintf(f,"\n");
	

	//la liste des noeuds
	CellNoeud* cll_nd_v = R->noeuds;
	while(cll_nd_v){
		fprintf(f,"v %d %f %f\n", cll_nd_v->nd->num, cll_nd_v->nd->x, cll_nd_v->nd->y);
		cll_nd_v = cll_nd_v->suiv;
	}
	fprintf(f,"\n");

	
	
	CellNoeud * voisins = NULL;
	//la liste des voisins de chaque noeud
	CellNoeud* cll_nd_l = R->noeuds;
	//On parcourt la liste des noeuds du reseau
	while(cll_nd_l){
		//on parcourt la liste des voisins de chaque noeud
		if (!cll_nd_l->nd->voisins)printf("cll_nd_l->nd->voisins existent pas\n");
		voisins = cll_nd_l->nd->voisins;
		
		while(voisins){
			printf("i'm in\n");
			//si le num du voisin est inf au num du noeud on ecrit
			if(cll_nd_l->nd->voisins->nd->num < cll_nd_l->nd->num){
				fprintf(f,"l %d %d\n", cll_nd_l->nd->voisins->nd->num, cll_nd_l->nd->num);
			}
			cll_nd_l->nd->voisins = cll_nd_l->nd->voisins->suiv;
		}
		cll_nd_l = cll_nd_l->suiv;
	}
	fprintf(f,"\n");
	
	//la liste des commodites
	CellCommodite* cll_com = R->commodites;
	while(cll_com){
		fprintf(f,"k %d %d\n", cll_com->extrA->num, cll_com->extrB->num);
		cll_com = cll_com->suiv;
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
