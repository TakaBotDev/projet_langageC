#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

liste_noeud_t* creer_liste (void) {
    liste_noeud_t* liste = (liste_noeud_t*)malloc(sizeof(*liste));
    if (liste == NULL) {
        return NULL;
    };
    liste -> tete = NULL;
    return liste;
}


void detruire_liste (liste_noeud_t** liste_ptr) {
    if (*liste_ptr == NULL) {
        return;
    };
    _cellule* Courant = (*liste_ptr) -> tete;
    while (Courant != NULL) {
        _cellule* Suivant = Courant -> suivant;
        free (Courant);
        Courant = Suivant;
    }
    free (*liste_ptr);
    *liste_ptr = NULL;
}


bool est_vide_liste(const liste_noeud_t* liste) {
    return liste -> tete == NULL;
    
}


bool contient_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    const _cellule* Courant = liste -> tete;
    while (Courant != NULL) {
        if (memes_coord(Courant -> noeud, noeud)) {
            return true;
        }
        Courant = Courant -> suivant;
    }
    return false;
}


bool contient_arrete_liste(const liste_noeud_t* liste, coord_t source, coord_t destination) {
    const _cellule* Courant = liste -> tete;
    coord_t* prec_destination;
    while (Courant != NULL) {
        if (memes_coord(Courant -> noeud, destination)) {
            set_x (prec_destination, get_x (Courant -> precedent));
            set_y (prec_destination, get_y (Courant -> precedent));
        }
        Courant = Courant -> suivant;
    }
    return contient_noeud_liste (liste, source) && contient_noeud_liste (liste, destination) && memes_coord(*prec_destination, source);
}


float cout_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    const _cellule* Cellule = NULL;
    const _cellule* Courant = liste -> tete;
    while (Courant != NULL) {
        if (memes_coord(Courant -> noeud, noeud)) {  /* Je comprends pas le problème */
            Cellule = Courant;
        }
        Courant = Courant -> suivant;
    }
    if (Cellule == NULL) {
        return 99999999999999999999999;
    }
    else {
        return Cellule -> cout;
    }
}


coord_t precedent_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    const _cellule* Cellule = NULL;
    const _cellule* Courant = liste -> tete;
    while (Courant != NULL) {
        if (memes_coord(Courant -> noeud, noeud)) {
            Cellule = Courant;
        }
        Courant = Courant -> suivant;
    }
    if (Cellule != NULL) {
        return Cellule -> precedent;
    }
}


coord_t min_noeud_liste(const liste_noeud_t* liste) {
    const _cellule* minc = liste -> tete;
    for (const _cellule* Courant = liste -> tete -> suivant ; Courant != NULL ; Courant = Courant -> suivant) {
        if (Courant -> cout < minc -> cout) {
            minc = Courant;
        }
    }
    return minc -> noeud;
}


void inserer_noeud_liste(liste_noeud_t* liste, coord_t noeud, coord_t precedent, float cout) {
    _cellule* Cellule = NULL;
    _cellule* Courant = liste -> tete;
    while (Courant != NULL) {
        if (memes_coord(Courant -> noeud, noeud)) {
            Cellule = Courant;
        }
        Courant = Courant -> suivant;
    }

    if (Cellule != NULL) {
        Cellule -> cout = cout;
        Cellule -> precedent = precedent;
        return;
    }

    _cellule* Nouveau = (_cellule*)malloc(sizeof(*Nouveau));
    Nouveau -> noeud = noeud;
    Nouveau -> cout = cout;
    Nouveau -> precedent = precedent;
    Nouveau -> suivant = liste -> tete;
    liste -> tete = Nouveau;
}


void supprimer_noeud_liste(liste_noeud_t* liste, coord_t noeud){
    _cellule* Precedent = NULL;
    _cellule* Courant = liste -> tete;

    while (Courant != NULL) {
        if (memes_coord(Courant -> noeud, noeud)) {
            if (Precedent == NULL) {
                liste -> tete = Courant -> suivant;
            }
            else {
                Precedent -> suivant = Courant -> suivant;
            }
            free (Courant);
            return;
        }
    }
    Precedent = Courant;
    Courant = Courant -> suivant;
}


