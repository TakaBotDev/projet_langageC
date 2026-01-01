#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

liste_noeud_t* creer_liste (void) {
    return Null; /* A revoir car ça ne respecte pas les post-condtions. */
}


void detruire_liste (liste_noeud_t** liste_ptr) {
    LCA Courant = liste_ptr;
    while (Courant != Null) {
        Free(Courant);
        Courant := Courant.Suivant;
    }
}


bool est_vide_liste(const liste_noeud_t* liste) {
    LCA Courant = liste_ptr;
    
}


bool contient_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {

}


bool contient_noeud_liste(const liste_noeud_t* liste, coord_t source, coord_t destination) {

}


float cout_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {

}


coord_t precedent_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {

}


coord_t min_noeud_liste(const liste_noeud_t* liste) {

}


void inserer_noeud_liste(liste_noeud_t* liste, coord_t noeud, float cout, coord_t precedent) {

}


void supprimer_noeud_liste(liste_noeud_t* liste, coord_t noeud){

}


