#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

struct _cellule {
    coord_t noeud;
    float cout;
    coord_t precedent;
    struct _cellule* suivant;
};

struct liste_noeud_t {
    struct _cellule* tete;
};

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
    bool trouve = false;
    
    while (Courant != NULL && !trouve) {
        if (memes_coord(Courant -> noeud, noeud)) {
            trouve = true;
        } else {
            NULL;
        }
        Courant = Courant -> suivant;
    }
    
    return trouve;
}


bool contient_arrete_liste(const liste_noeud_t* liste, coord_t source, coord_t destination) {
    return contient_noeud_liste (liste, source) && contient_noeud_liste (liste, destination) && memes_coord(precedent_noeud_liste(liste, destination), source);
}


float cout_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    const _cellule* Courant = liste -> tete;
    float cout_trouve = INFINITY;
    bool trouve = false;
    
    while (Courant != NULL && !trouve) {
        if (memes_coord(Courant -> noeud, noeud)) { 
            cout_trouve = Courant->cout;
            trouve = true;
        }
        Courant = Courant -> suivant;
    }
    return cout_trouve;
}


coord_t precedent_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    const _cellule* Courant = liste -> tete;
    bool trouve = false;
    coord_t precedent_trouve = creer_coord(-1, -1);
    
    while (Courant != NULL && !trouve) {
        if (memes_coord(Courant -> noeud, noeud)) {
            precedent_trouve = Courant -> precedent;
            trouve = true;
        }
        Courant = Courant -> suivant;
    }
    return precedent_trouve;
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
    while (Courant != NULL && Cellule == NULL) {
        if (memes_coord(Courant -> noeud, noeud)) {
            Cellule = Courant;
        } else {
            NULL;
        }
        Courant = Courant -> suivant;
    }

    if (Cellule != NULL) {
        Cellule -> cout = cout;
        Cellule -> precedent = precedent;
    } else {
        _cellule* Nouveau = (_cellule*)malloc(sizeof(*Nouveau));
        if (Nouveau != NULL) {
        Nouveau -> noeud = noeud;
        Nouveau -> cout = cout;
        Nouveau -> precedent = precedent;
        Nouveau -> suivant = liste -> tete;
        liste -> tete = Nouveau;
        } else {
            NULL;
        }
    }
}


void supprimer_noeud_liste(liste_noeud_t* liste, coord_t noeud){
    _cellule* Precedent = NULL;
    _cellule* Courant = liste -> tete;
    bool trouve = false;

    while (Courant != NULL && !trouve) {
        if (memes_coord(Courant -> noeud, noeud)) {
            trouve = true;
        } else {
            Precedent = Courant;
            Courant = Courant ->suivant;
        }
    }

    
    if (trouve) {     
        if (Precedent == NULL) {
            liste -> tete = Courant -> suivant;
        } else {
            Precedent -> suivant = Courant -> suivant;
        }
        free (Courant);
    } else {
        NULL;
    }
}


