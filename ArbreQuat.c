#include <stdlib.h>
#include "ArbreQuat.h"
#include "Reseau.h"


//5.1
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax){
	if((!xmin)||(!ymin)||(!xmax)||(!ymax)){return;} 
	
	CellChaine * ch = C->chaines;
	//initialisation des coordonnes
	*xmin = ch->points->x;
	*ymin = ch->points->y;
	*xmax = ch->points->x;
	*ymax = ch->points->y;
	//parcours des chaines
	while(ch){
		CellPoint *pcurr = ch->points;
		//parcours des points
		while(pcurr){
			// on remplace une coordone min ou max si il on trouve une valeur plus petit ou grand
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
	//initialisation d'un arbre
	ArbreQuat* arbreQ = (ArbreQuat*)malloc(sizeof(ArbreQuat));
	//test alloc
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
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
	if(!a || !parent) return;
	//Cas 1
	//Si arbre est vide. On cree une arbre calculant le centre et les dimentions
	if (*a == NULL){
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
		//creation du l'arbre
		*a = creerArbreQuat(centre_x,centre_y, (parent->coteX)*1.0/2, (parent->coteY)*1.0/2);
		//ajoute la noeud 
		(*a) -> noeud = n;
		return;
	}
	//Cas 2
	//On insere dans une feuille deja avec une noeud. 
	//On fait l'insertion maintenat de le noeud premier et le noeud ancien.
	if((*a)->noeud != NULL){
		Noeud *temp = (*a)->noeud;
		//insertion de la noeud originaire
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
		//insertion de la noeud ancien
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
		//ancient noued dans la feuille est donc annule
		(*a)->noeud = NULL;
		return;
	}
	//Cas 3. 
	//il y a pas de la noued dans cet arbre/feuille.
	//L'insertion est faite dans une des quatres cellules.
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
	//on cree la noeud et on l'insere
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
	//Si on est sur un feuille d'un arbre avec un noeud
	//On verifie si le noeud est pas le meme de notre et sinon on cree et l'ajoute
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
	//Trosieme cas
	//Si on est dans un feuille et le noeud est vide
	//On insere le noeud 
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
	//initialisation
	Reseau *Res = (Reseau*)malloc(sizeof(Reseau));
	Res->nbNoeuds = 0;
	Res->gamma = C->gamma;
	Res->noeuds = NULL;
	Res->commodites = NULL;
	//initialisation, calculs des dimentions et creeation d'un arbre 
	double Xmin, Ymin, Xmax, Ymax;
	chaineCoordMinMax(C, &Xmin, &Ymin, &Xmax, &Ymax);
	double coteX = Xmax - Xmin;
	double coteY = Ymax - Ymin;
	ArbreQuat *arb = creerArbreQuat(Xmin + coteX/2, Ymin + coteY/2, coteX, coteY);

	CellCommodite* com = NULL;
	CellChaine *chainecour = C->chaines;
	CellPoint * pointcour = NULL;
	//parcour chaine
	while(chainecour){
		pointcour = chainecour->points;
		com = (CellCommodite*)malloc(sizeof(CellCommodite));
		Noeud* nd_pointcour = NULL;
		Noeud* nd_prec = NULL;
		//parcour points
		while(pointcour){
			//ajout de point avec rechercheCreeNoeudArbre
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
			//si c'est pas le premier point 
			//on ajout des voisins
			if(nd_prec){
				insererVoisin(nd_pointcour, nd_prec);
				insererVoisin(nd_prec, nd_pointcour);
			}else{
				//on est sur le premier point de chaine
				com->extrA = nd_pointcour;
			}
			nd_prec = nd_pointcour;
			pointcour = pointcour->suiv;
		}
		//finalisation de la commodites
		com->extrB = nd_prec;
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

