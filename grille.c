#define _GNU_SOURCE
#include "grille.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/**
 * coord_lin : fonction statique (de module) qui transforme des coordonnées
 * cartésiennes dans la grille en coordonnées "linéaires" permettant d'adresser
 * le tableau contenu dans la grille.
 *
 * @param grille grille avec le bon système de coordonnées
 * @param position position dans la grille en coordonnées cartésiennes entières
 * @return position dans le tableau en coordonnée linéaire
 */
static size_t coord_lin(grille_t grille, coord_t position) {
    return (size_t)get_y(position) * (size_t)grille.largeur + (size_t)get_x(position);
}


grille_t creer_grille(int largeur, int profondeur) {
    assert(largeur > 0);
    assert(profondeur > 0);

    grille_t grille;
    grille.largeur = largeur;
    grille.profondeur = profondeur;
    
    grille.hauteurs = (float*)calloc( (size_t) (largeur * profondeur), sizeof(float) );
    assert(grille.hauteurs != NULL);
    
    return grille;
}


