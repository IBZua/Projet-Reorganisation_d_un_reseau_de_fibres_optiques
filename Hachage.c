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
	if(!R){return NULL;}
    //On cree la cle et on calcul l'index dans H
    double c = cle(x,y);
    int index = hachage(H->tailleMax, c);
    //On se positionne a l'index
    CellNoeud *CNH = (H->T)[index];
	Noeud *NH = NULL;
    //On parcourt chaque noeud du reseau tant que les coordonnees correspondent pas
    while(CNH){
         NH = CNH -> nd;

        if((NH -> x) == x && (NH -> y) == y) return NH;
        CNH = CNH -> suiv;
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
		H->T[index] = nouvCellH;
		return n;
	}
}

Reseau* reconstitueReseauHachage(Chaines *C, int m){
	//si chaine vide
	if(!C){return NULL;}
	TableHachage *TH = (TableHachage*)malloc(sizeof(TableHachage));
	TH->nbElement = 0;
    TH->tailleMax = m;
    TH->T = (CellNoeud**)malloc(m * sizeof(CellNoeud*));

	for (int i = 0 ; i < m ; i++) (TH -> T[i]) = NULL;

	Reseau *R = (Reseau*)malloc(sizeof(Reseau));
	R->nbNoeuds = 0;
	R->gamma = C->gamma;
	R->noeuds = NULL;
	R->commodites = NULL;

	CellCommodite* com = NULL;

	CellChaine *chainecour = C->chaines;
	CellPoint *pointcour = NULL;
	//On parcourt les chaines
	while(chainecour){
		pointcour = chainecour->points;

		com = (CellCommodite*)malloc(sizeof(CellCommodite));

		Noeud* nd_pointcour = NULL;
		Noeud* nd_prec = NULL;

		
		//On parcourt les points de la chaine
		while(pointcour){
			//Ajout de noeud
			nd_pointcour =  rechercheCreeNoeudHachage(R, TH,pointcour->x, pointcour->y);
			
			if(nd_prec){
			// verifier si nd_prec est voisins de nd_pointcour et si nd_pointcour est voisin de nd prec
			//Ajout de precedent dans voisins
			insererVoisin(nd_prec, nd_pointcour);
			insererVoisin(nd_pointcour, nd_prec);

			}else{
			com->extrA = nd_pointcour;
			}
			nd_prec = nd_pointcour;
			pointcour = pointcour->suiv;
		}
		
		com->extrB = nd_prec;
		com->suiv = R->commodites;
		R->commodites = com;

		chainecour = chainecour->suiv;
	}
	libereTableHachage(TH);
	return R;
}
void libereTableHachage(TableHachage * TH) {
    if (!TH) return ;
    
    CellNoeud * cnCour = NULL;
    CellNoeud * cnPrec = NULL;
    for (int i = 0 ; i < TH -> tailleMax ; i++) {
        cnPrec = NULL;
        cnCour = (TH -> T)[i];
        while (cnCour) {
            cnPrec = cnCour;
            cnCour = cnCour -> suiv;
            free(cnPrec);
        }
    }
    free(TH -> T);
    free(TH);
}