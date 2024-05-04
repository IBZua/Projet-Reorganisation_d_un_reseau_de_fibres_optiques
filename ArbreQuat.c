#include <stdlib.h>
#include "ArbreQuat.h"
#include "Reseau.h"


//5.1
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax){
	if((!xmin)||(!ymin)||(!xmax)||(!ymax)){return;} 
	
	CellChaine * ch = C->chaines;
	
	*xmin = ch->points->x;
	*ymin = ch->points->y;
	*xmax = ch->points->x;
	*ymax = ch->points->y;
	
	while(ch){
		CellPoint *pcurr = ch->points;
		while(pcurr){
			if ((*xmin) > pcurr->x){
				*xmin = pcurr->x;
			}
			if ((*ymin) > pcurr->y){
				*ymin = pcurr->y;
			}
			if ((*xmax) < pcurr->x){
				*xmax = pcurr->x;
			}
			if ((*ymax) < pcurr->y){
				*ymax = pcurr->y;
			}
			pcurr = pcurr->suiv;
		}
		ch = ch->suiv;
	}
}

//5.2
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY){
	ArbreQuat* arbreQ = (ArbreQuat*)malloc(sizeof(ArbreQuat));
	if(!arbreQ){
		printf("Err malloc");
		return NULL;
	}
	arbreQ->xc = xc;
	arbreQ->yc = yc;
	arbreQ->coteX = coteX;
	arbreQ->coteY = coteY;
	arbreQ->noeud = NULL;
	arbreQ->so = NULL;
	arbreQ->se = NULL;
	arbreQ->no = NULL;
	arbreQ->ne = NULL;
	return arbreQ;
}



//5.3
//Je ne saispas si ca marche. je meme comprends pas totalement qu-est ce qu'il est demande.
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
	if(!a || !parent) return;
	//Cas 1
	//On choisent une des queartres cellules et on .
	if (*a == NULL){
	printf("cx:%f cy:%f cotex:%f cotey:%f\n",parent->xc, parent->yc, parent->coteX, parent->coteY);
	

		double centre_x, centre_y;
		if(n->x < parent->xc){
			if(n->y < parent->yc){
				//so
				centre_x = parent->xc - (parent->coteX/4);
				centre_y = parent->yc - (parent->coteY/4);
				
			}else{
				//no
				centre_x = parent->xc - (parent->coteX/4);
				centre_y = parent->yc + (parent->coteY/4);
			}
		}
		else{
			if(n->y < parent->yc){
				//se
				centre_x = parent->xc + (parent->coteX/4);
				centre_y = parent->yc - (parent->coteY/4);				
			}else{
				//ne
				centre_x = parent->xc + (parent->coteX/4);
				centre_y = parent->yc + (parent->coteY/4);
			}
		}
		*a = creerArbreQuat(centre_x,centre_y, (parent->coteX)*1.0/2, (parent->coteY)*1.0/2);
		
		(*a) -> noeud = n;
		return;
	}
	//Cas 2
	//On garde le noeud ancien de la cellule. On fait l'insertion maintenat de le noeud premier et le noeud ancien.
	if((*a)->noeud != NULL){
		
		Noeud *temp = (*a)->noeud;
		

		//insertion de l'originaire
		if(n->x < (*a)->xc){
				if(n->y < (*a)->yc){
				//so
				insererNoeudArbre(n, &((*a)->so), *a);
			}else{
				//no
			
				insererNoeudArbre(n, &((*a)->no), *a);
			}
		}
		else{
			if(n->y < (*a)->yc){
				//se
			
				insererNoeudArbre(n, &((*a)->se), *a);
			}else{
				//ne
				
				insererNoeudArbre(n, &((*a)->ne), *a);
			}
		}
		
		//insertion de l'ancien
		if(temp->x < (*a)->xc){
			if(temp->y < (*a)->yc){
				//so
				insererNoeudArbre(temp, &((*a)->so), *a);
			}else{
				//no
				insererNoeudArbre(temp, &((*a)->no), *a);
			}
		}
		else{
			if(temp->y < (*a)->yc){
				//se
				insererNoeudArbre(temp, &((*a)->se), *a);
			}else{
				//ne
				insererNoeudArbre(temp, &((*a)->ne), *a);
			}
		}
		(*a)->noeud = NULL;
		return;
	}
	//Cas 3. L'insertion est faite dans une des quatres cellules.
	if ((*a != NULL) && ((*a)->noeud == NULL)){

		if(n->x < parent->xc){
			if(n->y < parent->yc){
				//so
				insererNoeudArbre(n, &((*a)->so), *a);
			}else{
				//no
				insererNoeudArbre(n, &((*a)->no), *a);
			}
		}
		else{
			if(n->y < parent->yc){
				//se
				insererNoeudArbre(n, &((*a)->se), *a);
			}else{
				//ne
				insererNoeudArbre(n, &((*a)->ne), *a);
			}
		}
	}
}

//5.4
Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y){
	ArbreQuat* arb = *a ;
	//Premier cas
	if (arb == NULL){
		Noeud* n = (Noeud*)malloc(sizeof(Noeud));
		
		R->nbNoeuds++;
		n->num = R->nbNoeuds;
		n->x = x;
		n->y = y;
		n->voisins = NULL;
		
		CellNoeud* cn = (CellNoeud*)malloc(sizeof(CellNoeud));
		
		cn->nd = n;
		cn->suiv = R->noeuds;
		R->noeuds = cn;
		
		insererNoeudArbre(n, &(*a), parent);
		return n;
	}
	//Deuxieme cas
	if (arb->noeud != NULL){
		if ((arb->noeud->x == x) && (arb->noeud->y == y)){
			return arb->noeud;
		}
		
		else{
			Noeud* n = (Noeud*)malloc(sizeof(Noeud));
			R->nbNoeuds++;
			n->num = R->nbNoeuds;
			n->x = x;
			n->y = y;
			n->voisins = NULL;
			
			CellNoeud* cn = (CellNoeud*)malloc(sizeof(CellNoeud));
			cn->nd = n;
			cn->suiv = R->noeuds;
			R->noeuds = cn;
			
			insererNoeudArbre(n, &(*a), parent);
			return n;
		}
	}

	if((*a != NULL) && ((*a)->noeud == NULL)){
		if(x < arb->xc){
			if(y < arb->yc){
				//so
				return rechercheCreeNoeudArbre(R, &(arb->so), arb, x, y);
			}else{
				//no
				return rechercheCreeNoeudArbre(R, &(arb->no), arb, x, y);
			}
		}
		else{
			if(y < arb->yc){
				//se
				return rechercheCreeNoeudArbre(R, &(arb->se), arb, x, y);
			}else{
				//ne
				return rechercheCreeNoeudArbre(R, &(arb->ne), arb, x, y);
			}
		}
	}
	else{return NULL;}
}

//5.5
Reseau* reconstitueReseauArbre(Chaines* C){

	if (!C) return NULL;

	Reseau *Res = (Reseau*)malloc(sizeof(Reseau));
	Res->nbNoeuds = 0;
	Res->gamma = C->gamma;
	Res->noeuds = NULL;
	Res->commodites = NULL;

	double Xmin, Ymin, Xmax, Ymax;
	chaineCoordMinMax(C, &Xmin, &Ymin, &Xmax, &Ymax);
	
	printf("%f %f %f %f", Xmin, Ymin, Xmax, Ymax);
	
	double coteX = Xmax - Xmin;
	double coteY = Ymax - Ymin;
	ArbreQuat *arb = creerArbreQuat(Xmin + coteX/2, Ymin + coteY/2, coteX, coteY);

	CellCommodite* com = NULL;
	CellChaine *chainecour = C->chaines;
	CellPoint * pointcour = NULL;
	while(chainecour){
		printf("-----------------\n");
		pointcour = chainecour->points;
		com = (CellCommodite*)malloc(sizeof(CellCommodite));
		Noeud* nd_pointcour = NULL;
		Noeud* nd_prec = NULL;
	
		while(pointcour){
			//aj 
			
			if(pointcour->x < arb->xc){
				if(pointcour->y < arb->yc){
					//so
					nd_pointcour = rechercheCreeNoeudArbre(Res, &(arb->so), arb, pointcour->x, pointcour->y);
				}else{
					//no
					nd_pointcour = rechercheCreeNoeudArbre(Res, &(arb->no), arb, pointcour->x, pointcour->y);
				}
			}
			else{
				if(pointcour->y < arb->yc){
					//se
					nd_pointcour = rechercheCreeNoeudArbre(Res, &(arb->se), arb, pointcour->x, pointcour->y);
				}else{
					//ne
					nd_pointcour = rechercheCreeNoeudArbre(Res, &(arb->ne), arb, pointcour->x, pointcour->y);
				}
			}
			
			printf("nb-noeud: %d -- x: %f  y: %f\n", Res->nbNoeuds, pointcour->x, pointcour->y);
			if(nd_prec){
			
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
		com->extrB = nd_prec;
		printf("extrB x:%f  y;%f \n", com->extrB->x, com->extrB->y);
		com->suiv = Res->commodites;
		Res->commodites = com;
		chainecour = chainecour->suiv;
	}
	libereArbreQuat(arb);
	return Res;
}

void libereArbreQuat(ArbreQuat * a){
	if(!a)return;
	if(!a->noeud) {
		libereArbreQuat(a->no);
		libereArbreQuat(a->so);
		libereArbreQuat(a->se);
		libereArbreQuat(a->ne);
		
	}
	free(a);
}

