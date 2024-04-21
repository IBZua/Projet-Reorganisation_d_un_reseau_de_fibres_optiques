#include <stdlib.h>
#include "ArbreQuat.h"


//5.1
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax){
    while(C->chaines){
        CellPoint *pcurr = C->chaines->points;
        while(pcurr){
            if ((*xmin > pcurr->x)  ){
                xmin = &pcurr->x;
            }
            if (*ymin > pcurr->y){
                ymin = &pcurr->y;
            }
            if ((*xmax < pcurr->x)  ){
                xmax = &pcurr->x;
            }
            if (*ymax < pcurr->y){
                ymax = &pcurr->y;
            }
            pcurr = pcurr->suiv;
        }     
        C->chaines = C->chaines->suiv;
    }    
}
//5.2
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY){
    ArbreQuat* arbreQ = (ArbreQuat*)malloc(sizeof(ArbreQuat));
    arbreQ->xc = xc;
    arbreQ->yc = yc;
    arbreQ->coteX = coteX;
    arbreQ->coteY = coteY;
    arbreQ->noeud = NULL;
    arbreQ->so = NULL;
    arbreQ->se = NULL;
    arbreQ->no = NULL;
    arbreQ->ne = NULL;
}

//5.3
//Je ne saispas si ca marche. je meme comprends pas totalement qu-est ce qu'il est demande.
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
    //Cas 1
    //On choisent une des queartres cellules et on . 
    if (*a == NULL){
        if(n->x < parent->xc){
            if(n->y < parent->yc){
                //so
                *a = creerArbreQuat(parent->xc - (parent->coteX/4),parent->yc - (parent->coteY/4), parent->coteX/2, parent->coteY/2);
                (*a)->noeud = n;
            }else{
                //no
                *a = creerArbreQuat(parent->xc - (parent->coteX/4),parent->yc + (parent->coteY/4), parent->coteX/2, parent->coteY/2);
                (*a)->noeud = n;
            }
            
        }
        else{
            if(n->y < parent->yc){
                //se
                *a = creerArbreQuat(parent->xc + (parent->coteX/4),parent->yc - (parent->coteY/4), parent->coteX/2, parent->coteY/2);
                (*a)->noeud = n;
            }else{
                //ne
                *a = creerArbreQuat(parent->xc + (parent->coteX/4),parent->yc + (parent->coteY/4), parent->coteX/2, parent->coteY/2);
                (*a)->noeud = n;
            }
        }
    }
    //Cas 2
    //On garde le noeud ancien de la cellule. On fait l'insertion maintenat de le noeud premier et le noeud ancien. 
    if((*a)->noeud != NULL){ 
        Noeud *temp = (*a)->noeud;
        (*a)->noeud = NULL;
        
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
        if(n->x < (*a)->xc){
            if(n->y < (*a)->yc){
                //so
                insererNoeudArbre(temp, &((*a)->so), *a);
            }else{
                //no
                insererNoeudArbre(temp, &((*a)->no), *a);
            }
        }
        else{
            if(n->y < (*a)->yc){
                //se
                insererNoeudArbre(temp, &((*a)->se), *a);
            }else{
                //ne
                insererNoeudArbre(temp, &((*a)->ne), *a);
            }
        }
        
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
    
    if (*a == NULL){
        Noeud* n = rechercheCreeNoeudListe(R, x, y);
        insererNoeudArbre(n, &(*a), parent);
        return n;
    }

    if ((*a)->noeud != NULL){
        if (((*a)->noeud->x == x)&&((*a)->noeud->y == y)){
            return (*a)->noeud;
        }
        else{
            Noeud* n = rechercheCreeNoeudListe(R, x, y);
            insererNoeudArbre(n, &(*a), parent);
        }
    }

    if((*a != NULL) && ((*a)->noeud == NULL)){
        Noeud* n = rechercheCreeNoeudListe(R, x, y);
        if(x < parent->xc){
            if(y < parent->yc){
                //so
                rechercheCreeNoeudArbre(R, (*a)->so, *a, x, y);
            }else{
                //no
                rechercheCreeNoeudArbre(R, (*a)->no, *a, x, y);
            }
        }
        else{
            if(y < parent->yc){
                //se
                rechercheCreeNoeudArbre(R, (*a)->se, *a, x, y);
            }else{
                //ne
                rechercheCreeNoeudArbre(R, (*a)->ne, *a, x, y);
            }
        }
    }
} 

//5.5
Reseau* reconstitueReseauArbre(Chaines* C){
    Reseau *Res = (Reseau*)malloc(sizeof(Reseau));
    Res->nbNoeuds = comptePointsTotal(C);
	Res->gamma = C->gamma;
	Res->noeuds = malloc(sizeof(CellNoeud));

    double *Xmin, *Ymin, *Xmax, *Ymax; 
    chaineCoordMinMax(C, Xmin, Ymin, Xmax, Ymax);
    double coteX = *Xmax - *Xmin;
    double coteY = *Ymax - *Ymin;
    ArbreQuat *Arb = creerArbreQuat(*Xmin + coteX/2, *Ymin + coteY/2, coteX, coteY);

    CellPoint* pprec = malloc(sizeof(CellPoint));

    while(C->chaines){
        CellPoint *pcurr = C->chaines->points;
        Res->commodites->extrA = rechercheCreeNoeudArbre(Res, &Arb, NULL, pcurr->x, pcurr->y);
        //premier point de la chaine peut etre pas dans le reseau?
        while(pcurr){
            Res->noeuds->nd = rechercheCreeNoeudArbre(Res, &Arb, NULL, pcurr->x, pcurr->y);
            //voisins?
            pprec = pcurr;
            pcurr = pcurr->suiv;
        }
        Res->commodites->extrB = pprec;
        Res->commodites = Res->commodites->suiv;
        C->chaines = C->chaines->suiv;
    }
    //liberer arbre?
}