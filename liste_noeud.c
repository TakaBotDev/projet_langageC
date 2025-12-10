#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

LCA creer_liste () {
    return Null; /* A revoir car ça ne respecte pas les post-condtions. */
}


void detruire_liste (LCA liste_ptr) {
    LCA Courant = liste_ptr;
    while (Courant != Null) {
        Free(Courant);
        Courant := Courant.Suivant;
    }
}


bool est_vide_liste () {
    LCA Courant = liste_ptr;
    
}


bool contient_noeud_liste () {

}


bool contient_arrete_liste () {

}


int cout_noeud_liste () {

}


LCA precedent_noeud_liste () {

}


LCA min_noeud_liste () {

}


void inserer_noeud_liste () {

}


void supprimer_noeud_liste () {

}


