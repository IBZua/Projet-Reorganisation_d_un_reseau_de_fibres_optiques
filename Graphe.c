#include <stdio.h>
#include "Graphe.h"
#include "Struct_File.h"
#include "Reseau.h"
// 7.1
Graphe* creerGraphe(Reseau* r){
    Graphe *g = (Graphe*)malloc(sizeof(Graphe));

    g->nbsom = r->nbNoeuds;
    g->gamma = r->gamma;
    g->nbcommod = nbCommodites(r);

    Sommet ** tab_s = (Sommet**)malloc((g->nbcommod + 1)*sizeof(Sommet*));

    for(int i=0; i<g->nbsom +1; i++){
        tab_s[i] = NULL;
    }

    CellNoeud * cn = r -> noeuds;
    Noeud * nd = NULL;
    CellNoeud * voisin = NULL;
    int num_voisin;
    
    while(cn){
        nd = cn -> nd;
        Sommet * s = (Sommet *)malloc(sizeof(Sommet));
        
        s -> num = nd -> num;
        s -> x = nd -> x;
        s -> y = nd -> y;
        s -> L_voisin = NULL;
       
        while (voisin) {
            num_voisin = voisin -> nd -> num;
            Arete * arr = NULL;

            //on comparons les num des sommets pour voir si on a deja vu le voisin
            //Si c'est le 1er rencontre
            if(num_voisin <= nd -> num){ 
                arr = (Arete *)malloc(sizeof(Arete));
                arr -> u = nd -> num;
                arr -> v = num_voisin;
            
            //si on a deja vu
            } else {    // nous le trouvons dans la liste des voisins du sommet u
                Cellule_arete * cll_arr_djv = tab_s[num_voisin] -> L_voisin;
                Arete * arr_djv = NULL;

                while(cll_arr_djv != NULL){
                    arr_djv = cll_arr_djv -> a;
                    //On cherche l'arete qui a pour numero = le numero du sommet v
                    if(arr_djv -> v == nd -> num){
                        arr = arr_djv;
                        break;
                    }
                    cll_arr_djv = cll_arr_djv -> suiv;
                }
            }

            //Creer la cellule arete et ajouter l'arete dans cette cellule
            Cellule_arete * cll_arr = (Cellule_arete *)malloc(sizeof(Cellule_arete));
            cll_arr -> a = arr;
            cll_arr -> suiv = s -> L_voisin;
            s -> L_voisin = cll_arr;

            voisin = voisin -> suiv;
        }

        tab_s[s -> num] = s;
        cn = cn -> suiv;
    }
    g->T_som = tab_s;

    Commod * liste_com  = (Commod *)malloc((g -> nbcommod) * sizeof(Commod));
    CellCommodite * com_cour = r->commodites;
    int j = 0;
    while(com_cour){
        Commod c;
        c.e1 = com_cour->extrA->num;
        c.e2 = com_cour->extrB->num;
        liste_com[j] = c;
        j++;

        com_cour = com_cour->suiv;
    }
    g->T_commod = liste_com;
    return g;
}

//7.2
int plusPetitNbArretes(Graphe* g, int a, int b){
    //Nous initialisons un tableau visit qui nous donne la longueur de la chaîne de a à visit[i]
    int visit[(g -> nbsom) + 1];
    int i;
    for (i = 0; i < g -> nbsom + 1; i++){
        visit[i] = 0;
    }

    //initialisons bordure avec une file
    S_file * F = (S_file *)malloc(sizeof(S_file));
    Init_file(F);
    enfile(F,a);

    while(!estFileVide(F)){
        //A chaque fois on prend un sommet u et on regarde ses sommets adjacents
        int u = defile(F);

        //Nous regardons les aretes du sommet u
        Cellule_arete * voisins_u = g -> T_som[u] -> L_voisin;

        while(voisins_u){
            //Nous choisissont le bon sommet v de l'arete, exemple arete 1-4, si u = 4, nous retournons 1 et sinon , nous retournons 4.
            int v = 0;
            if(voisins_u -> a -> v == u){
                v = voisins_u -> a -> u;
            } else {
                v = voisins_u -> a -> v;
            }

            //Si nous n'avons jamais parcouru le sommet (visit[v] == 0) ou s'il est different du sommet de depart (racine)
            if(visit[v] == 0 && v != a){
                //Nous incrementons de 1 par rapport a son element precedent dans le tableau visit
                visit[v] = visit[u] + 1;
                enfile(F,v);

                //Si on est arrivée au sommet target, nous retournons la distance entre a et b, en prenant le plus cours chemin entre les deux sommets.
                if(v == b){
                    while(!estFileVide(F)){
                        defile(F);
                    }
                    free(F);
                    return visit[b];
                }
            }
            voisins_u = voisins_u -> suiv;
        }

    }
    free(F);
    return visit[b];

}

//7.3
ListeEntier * plusCourteChaineUV(Graphe * G, int a, int b){
    //Nous reprennons la fonction plusPetitNbAretes et nous la modifions pour qu'il retourne la chaîne entre a et b
    //Pour cela, nous utiliserons une liste d'entiers, nous la declarons et initialisons
    ListeEntier * le = (ListeEntier *)malloc(sizeof(ListeEntier));
    Init_Liste(le);

    int visit[(G -> nbsom) + 1];
    //Nous creons un tableau prec pour pouvoir retourner du sommet v au sommet u et remplir notre liste d'entiers
    int prec[(G -> nbsom) + 1];
    int i;
    for (i = 0; i < (G -> nbsom) + 1; i++){
        visit[i] = 0;
        //Nous initialisons prec
        prec[i] = -1;
    }
    S_file * F = (S_file *)malloc(sizeof(S_file));
    Init_file(F);
    enfile(F,a);

    while(!estFileVide(F)){
        int u = defile(F);
        Cellule_arete * voisins_u = G -> T_som[u] -> L_voisin;

        while(voisins_u != NULL){
            int v = 0;
            if(voisins_u -> a -> v == u){
                v = voisins_u -> a -> u;
            } else {
                v = voisins_u -> a -> v;
            }
            if(visit[v] == 0 && v != a){
                visit[v] = visit[u] + 1;
                enfile(F,v);

                //Nous mettons le sommet antecedent de v dans la case v dans prec
                if(prec[v] == -1){
                    prec[v] = u;
                }
                //Si on a atteint le sommet target, nous n'avons plus besoin du reste.
                if(v == b){
                    int temp = b;
                    //A chaque tour, nous revennons "a l'arriere" grace au tableau prec et on obtiendra la liste d'entiers de la plus courte chaine de u a v.
                    while(prec[temp] != -1){
                        
                         ajoute_en_tete(le, temp);

                        temp = prec[temp];
                    }
                         ajoute_en_tete(le, temp);

                    // Liberer la file 
                    while (!estFileVide(F)) {
                        defile(F);
                    }
                    free(F);

                    return le;
                }
            }
            voisins_u = voisins_u -> suiv;
        }

    }

    free(F);
    return le;
}
//7.4
int reorganiseReseau(Reseau * r){
    Graphe * g = creerGraphe(r);

    // On initialise la matrice
    int ** matrice = (int **)malloc(((g -> nbsom) + 1) * sizeof(int*));
    if(!matrice){    
        printf("Probleme allocation");
        return -1;
    }
    for (int i = 0; i < (g -> nbsom) + 1; i++){
        matrice[i] = (int *)malloc(((g -> nbsom) + 1) * sizeof(int));
    }
    for(int i = 0; i < (g -> nbsom) + 1; i++){
        for(int j = 0; j < (g -> nbsom) + 1; j++){
            matrice[i][j] = 0;
        }
    }


    //On parcours la table de commodites
    Commod * tab_c = g -> T_commod;
    Commod com;
    for(int l = 0; l < g -> nbcommod; l++){
        com = tab_c[l];
        //On regarde la plus courte chaine qui relie les deux extremites de la commodite
        ListeEntier * LE_temp = plusCourteChaineUV(g, com.e1, com.e2);
        ListeEntier parcours = *LE_temp;
        //Nous ajoutons les aretes dans la matrice
        while(parcours -> suiv){
            matrice[parcours -> u][parcours -> suiv -> u]++;
            parcours = parcours -> suiv;
        }
        //Liberent LE_temp
        desalloue(LE_temp);
        free(LE_temp);
    }

    //Nous comptons pour chaque couple de sommets, le nombre de chaines qui passent par l'arrete
    int arretes = 0;
    for (int m = 0; m < (g -> nbsom) + 1; m++){
        for(int n = m; n < (g -> nbsom) + 1; n++){
            arretes = matrice[m][n] + matrice[n][m];
            //Si le nombre est superieur a gamma, on retoune Faux
            if(arretes > g -> gamma){
                libererMatrice(matrice, (g -> nbsom) + 1);
                libererGraphe(g);
                return 0;
            }
        }
    }

    libererMatrice(matrice, (g -> nbsom) + 1);

    libererGraphe(g);
    return 1;
}

void libererMatrice(int ** matrice, int taille){
    for(int i = 0; i < taille; i++){
        free(matrice[i]);
    }
    free(matrice);
}

void afficherGraphe(Graphe * G) {
    printf("Nombre de sommets : %d\n", G -> nbsom);
    printf("Gamma : %d\n", G -> gamma);
    printf("Nb commodites : %d\n", G -> nbcommod);

    Sommet * s = NULL;
    Cellule_arete * ca = NULL;

    for (int i = 1 ; i < G -> nbsom + 1 ; i++) {
        s = G -> T_som[i];
        printf("sommet : [num : %d] [x : %f] [y : %f] \n", s -> num, s -> x, s -> y);

        ca = s -> L_voisin;
        while (ca) {
            printf("arete : %d, %d\n", ca -> a -> u, ca -> a -> v);
            ca = ca -> suiv;
        }
    }

    printf("\n");

    for (int j = 0 ; j < G -> nbcommod ; j++) {
        printf("Commod : %d, %d\n", (G -> T_commod)[j].e1, (G -> T_commod)[j].e2);
    }
}

void libererGraphe(Graphe * g) {
    if(!g)return;

    Sommet * s = NULL;
    Cellule_arete * cll_cour = NULL;
    Cellule_arete * cll_prec = NULL;

    // On libere les sommets et les aretes 
    for (int i = 1 ; i < g -> nbsom + 1 ; i++) {
        s = g -> T_som[i];
        cll_cour = s -> L_voisin;

        while (cll_cour) {
            // Si on rencontre la premiere fois cette arete, on la libere 
            if (s -> num == (cll_cour -> a -> u)) {
                free(cll_cour -> a);
            }
            cll_prec = cll_cour;
            cll_cour = cll_cour -> suiv;
            free(cll_prec);
        }
        free(s);
    }
    free(g -> T_som);
    free(g -> T_commod);
    free(g);
}