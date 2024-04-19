#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "SVGwriter.h"

CellPoint *creer_point(double x,double y){
	CellPoint *p=(CellPoint*)malloc(sizeof(CellPoint));
	p->x=x;
	p->y=y;
	p->suiv=NULL;
	return p;}
	
CellChaine *creer_liste_chaine(int numero){
	CellChaine *lc=(CellChaine*)malloc(sizeof(CellChaine));
	lc->numero = numero;
	lc->points=NULL;
	lc->suiv=NULL;
	return lc;}
	
Chaines *creer_chaine(int gamma){
	Chaines *c=(Chaines*)malloc(sizeof(Chaines));
	c->gamma = gamma;
	c->nbChaines=0;
	c->chaines=NULL;
	return c;}
	
void ajout_point_chaine(CellChaine *lc, double x,double y){
	CellPoint *new=creer_point( x, y);
	
	if(lc->points==NULL){
		lc->points=new;
		}else{
		
	CellPoint *temp=lc->points;
	
	while(temp->suiv){
		temp=temp->suiv;
		}
	temp->suiv=new;}
	}

//Ajouter un element d'une liste de chaines à Chaine
void ajout_Chaines(Chaines *c, CellChaine *lc){
	if(c->nbChaines==0){
	c->nbChaines++;
	c->chaines=lc;
	}else{
	
		CellChaine *temp=c->chaines;
		while(temp->suiv){
		temp=temp->suiv;}
		c->nbChaines++;
		temp->suiv=lc;}
	}
	

Chaines* lectureChaines(FILE *f){
	int nbChaines;
	int gamma;
	char buffer[256];
	
	fgets(buffer,256,f);
	sscanf(buffer,"NbChain: %d\n",&nbChaines);
	fgets(buffer,256,f);
	sscanf(buffer,"Gamma: %d\n",&gamma);
	
	 Chaines * chaines = creer_chaine(gamma);

    // Lecture des chaînes
    for (int i = 0; i < nbChaines; i++) {
        int numero, nbPoints;
        double x, y;

        fgets(buffer, sizeof(buffer), f);
        sscanf(buffer, "%d %d %[^\n]\n", &numero, &nbPoints,buffer);

        // Création de la liste de points
        CellChaine *chaine = creer_liste_chaine(i);

        for (int j = 0; j < nbPoints; j++) {
            sscanf(buffer, "%lf %lf %[^\n]\n", &x, &y,buffer);
            ajout_point_chaine(chaine, x, y);
        }

        ajout_Chaines(chaines, chaine);
    }

    return chaines;
}
	
int comptePoints(CellChaine *chaine) {
    int res = 0;
    CellPoint *p = chaine->points;
    while (p != NULL) {
        res++;
        p = p->suiv;
    }
    return res;
}

void ecrireChaines(Chaines *C, FILE *f) {
    fprintf(f, "NbChain: %d\n", C->nbChaines);
    fprintf(f, "Gamma: %d\n", C->gamma);
    
    CellChaine *lc = C->chaines;
    while (lc != NULL) {
        fprintf(f, "%d %d ", lc->numero, comptePoints(lc));
        
        CellPoint *p = lc->points;
        while (p != NULL) {
            fprintf(f, "%.2f %.2f ", p->x, p->y);
            p = p->suiv;
        }
        fprintf(f, "\n");
        lc = lc->suiv;
    }
}


void afficheChainesSVG(Chaines *C, char* nomInstance){
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}


double longueurChaine(CellChaine *c){
	int l=0;
	CellPoint *tmp=c->suiv->points;
	CellPoint *prec=c->points;
	while(tmp){
        l += sqrt(pow((tmp->x - prec->x),2) + pow((tmp->y - prec->y),2));
        tmp = tmp->suiv;
    }
    return l;
}
	
double longueurTotale(Chaines *C){
    int l = 0;
    CellChaine *c = C->chaines;
    for(int i = 0; i < C->nbChaines; i++){
        l += longueurChaine(c);
        c = c->suiv;
    }
    return l;
}

int comptePointsTotal(Chaines *C){
    int nbPoint = 0;
    CellChaine *c = C->chaines;
    CellPoint *tmp = c->points;
    //parcourt de la liste de chaine
    for(int i = 0; i < C->nbChaines; i++){
        //parcourt de la liste de points
        while(tmp){
            nbPoint++;
            tmp = tmp->suiv;
        }
        tmp = c->points;
    }
    return nbPoint;
}