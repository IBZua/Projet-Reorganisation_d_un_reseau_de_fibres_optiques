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



/*
void insereVoisin(CellNoeud ** L, Noeud * n) {
    CellNoeud * voisin = (*L);
    
    //Parcourt la liste des voisins 
    while ((voisin != NULL) && (voisin -> nd != n)) voisin = voisin -> suiv;
    
    // Si ce noeud n'est pas dans la liste, on l'ajoute 
    if (!voisin) {
        voisin = (CellNoeud *)malloc(sizeof(CellNoeud));
        voisin -> nd = n;
        voisin -> suiv = (*L);
        (*L) = voisin;
    }
}


// Q 2.2 
Reseau* reconstitueReseauListe(Chaines *C) {
  if (!C) return NULL;

  // Creer le reseau 
  Reseau * r = (Reseau *)malloc(sizeof(Reseau));

  r -> nbNoeuds = 0;
  r -> gamma = C -> gamma;
  r -> commodites = NULL;
  r -> noeuds = NULL;

  CellCommodite * ccommo = NULL;
  Noeud * n  = NULL;
  Noeud * nPrec = NULL;
	
  CellChaine * cc = C -> chaines;
  CellPoint * cp = NULL;

  while (cc) {
    cp = cc -> points;
    nPrec = NULL;
    n = NULL;

    //On cree une commodite chaque fois au debut d'un parcourt d'une chaine 
    ccommo = (CellCommodite *)malloc(sizeof(CellCommodite));

    while (cp) {
      //On conserve le noeud precedent 
      nPrec = n;
      // On cree un noeud et l'ajoute dans le reseau 
      n = rechercheCreeNoeudListe(r, cp -> x, cp -> y);
      // On ajoute les voisins si ce noeud n'est pas le premier dans une chaine 
      if (nPrec) {
        insereVoisin(&(nPrec -> voisins), n);
        insereVoisin(&(n -> voisins), nPrec);
      } else {
        //Si ce noeud est le premier dans une chaine, alors il est l'extrA *
        ccommo -> extrA = n;
      }

      cp = cp -> suiv;
    }
    // On ajoute le commodite dans la liste 
    ccommo -> extrB = n;
    ccommo -> suiv = r -> commodites;
    r -> commodites = ccommo;
    
    cc = cc -> suiv;
  }
  
  return r;
}*/

Reseau* reconstitueReseauListe(Chaines *C){
printf("wtf");
	//si chaine vide
	if(!C){return NULL;}
	//INITIALISATION RESEAU
	Reseau *R = (Reseau*)malloc(sizeof(Reseau));
	R->nbNoeuds = comptePointsTotal(C);
	R->gamma = C->gamma;
	R->noeuds = NULL;
	R->commodites = NULL;
	//Initialisation prec pour parcourir voisins
	CellPoint* prec = (CellPoint*)malloc(sizeof(CellPoint));
	CellCommodite* com;
	
	printf("test creation");
	CellChaine *chainecour = C->chaines;
	CellPoint * pointcour = NULL;
	//On parcourt les chaines
	while(chainecour){
		pointcour = chainecour->points;
		
		com = (CellCommodite*)malloc(sizeof(CellCommodite));
		//On initialise/ajoute commodite A au reseau
		R->commodites = com;
		R->commodites->extrA = rechercheCreeNoeudListe(R, pointcour->x, pointcour->y);
		
		R->noeuds->nd->voisins = (CellNoeud*)malloc(sizeof(CellNoeud));
		
		printf("commodite");
		//On ajoute le premier point
		R->noeuds->nd = rechercheCreeNoeudListe(R, pointcour->x, pointcour->y);
		printf("1 x et y de: %f %f", pointcour->x, pointcour->y);
		R->noeuds->nd->voisins->nd = rechercheCreeNoeudListe(R, pointcour->suiv->x, pointcour->suiv->y);
		printf("1 x et y de: %f %f", pointcour->x, pointcour->y);
		prec = pointcour;
		pointcour = pointcour->suiv;
		
		//On parcourt les points de la chaine
		while(pointcour->suiv){
			R->noeuds->nd = rechercheCreeNoeudListe(R, pointcour->x, pointcour->y);
			printf("2 x et y de: %f %f", pointcour->x, pointcour->y);
			R->noeuds->nd->voisins = (CellNoeud*)malloc(sizeof(CellNoeud));
			R->noeuds->nd->voisins->nd = rechercheCreeNoeudListe(R, prec->x, prec->y);
			printf("x et y de prec: %f %f", prec->x, prec->y);
			R->noeuds->nd->voisins->suiv = (CellNoeud*)malloc(sizeof(CellNoeud));
			R->noeuds->nd->voisins->suiv->nd = rechercheCreeNoeudListe(R, pointcour->suiv->x, pointcour->suiv->y);
			
			prec = pointcour;
			pointcour = pointcour->suiv;
		}
		R->noeuds->nd = rechercheCreeNoeudListe(R, pointcour->x, pointcour->y);
		R->noeuds->nd->voisins = (CellNoeud*)malloc(sizeof(CellNoeud));
		R->noeuds->nd->voisins->nd = rechercheCreeNoeudListe(R, prec->x, prec->y);
		
		//On maj commodite B
		R->commodites->extrB = rechercheCreeNoeudListe(R, pointcour->x, pointcour->y);
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
