#include "Chaine.h"
#include "Reseau.h"
#include <math.h>
#include <stdlib.h>

typedef struct{
  int nbElement; //pas necessaire ici
  int tailleMax;
  CellNoeud** T;
} TableHachage ;

Reseau* reconstitueReseauHachage(Chaines *C, int m);
void libereTableHachage(TableHachage * TH);