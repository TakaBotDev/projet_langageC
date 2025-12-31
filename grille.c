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


void detruire_grille(grille_t grille) {
    free(grille.hauteurs);
}


bool dans_les_bornes(grille_t grille, coord_t position) {
    int x = get_x(position);
    int y = get_y(position);
    return (x >= 0 && x < grille.largeur && y >= 0 && y < grille.profondeur);
}    


int get_largeur(grille_t grille) {
    return grille.largeur;
}


int get_profondeur(grille_t grille) {
    return grille.profondeur;
}


coord_t inferieur_gauche(grille_t grille) {
    return creer_coord(0, 0);
}


coord_t superieur_droit(grille_t grille) {
    return creer_coord(grille.largeur - 1, grille.profondeur - 1);
}



void set_hauteur(grille_t grille, coord_t position, float hauteur) {
    assert(dans_les_bornes(grille, position));
    grille.hauteurs[coord_lin(grille, position)] = hauteur;
}


float get_hauteur(grille_t grille, coord_t position) {
    assert(dans_les_bornes(grille, position));
    return grille.hauteurs[coord_lin(grille, position)];
}


size_t get_voisins(grille_t grille, coord_t position, float seuil, coord_t** voisins) {
    assert(voisins != NULL);
    assert(seuil >= 0.0f);

    float hauteur_initiale = get_hauteur(grille, position);

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    coord_t* voisins_temp = (coord_t*)malloc(4 * sizeof(coord_t));
    assert(voisins_temp != NULL);

    size_t ind_voisin_valide = 0; 

    for (int i = 0; i < 4; i++) {
        coord_t voisin = translation(position, dx[i], dy[i]);

        if (dans_les_bornes(grille, voisin)) {
            float hauteur_voisin = get_hauteur(grille, voisin);
            float denivele = fabsf(hauteur_voisin - hauteur_initiale);

            if (denivele <= seuil) {
                voisins_temp[ind_voisin_valide] = voisin;
                ind_voisin_valide++;
            }
        }
    }


    if (ind_voisin_valide > 0) {
        *voisins = (coord_t*)realloc(voisins_temp, ind_voisin_valide * sizeof(coord_t));
        assert(*voisins != NULL);
    } else {
        free(voisins_temp);
        *voisins = NULL;
    }
    
    return ind_voisin_valide;
}   
