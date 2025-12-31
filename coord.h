// TODO : écrire la spécification du module coord
// Note : ne pas oublier la garde pour le header

#ifndef COORD_H
#define COORD_H

#include <stdbool.h>

struct coord_t { int x; int y; };

typedef struct coord_t coord_t;

// creer_coord : crée une coordonnée avec les valeurs x et y données
coord_t creer_coord(int x, int y);


// get_x : récupère la coordonnée x
int get_x(coord_t position);


// get_y : récupère la coordonnée y 
int get_y(coord_t position);


// set_x : modifie la coordonnée x
void set_x(coord_t* position, int x);


void set_y(coord_t* position, int y);


// memes_coord : teste si deux points ont les mêmes coordonnées
bool memes_coord(coord_t c1, coord_t c2);


coord_t translation(coord_t position, int dx, int dy);


float distance_euclidienne(coord_t p1, coord_t p2);


#endif 
