// TODO : écrire la spécification du module coord
// Note : ne pas oublier la garde pour le header

#ifndef COORD_H
#define COORD_H

struct coord_t { int x; int y; };

typedef struct coord_t coord_t;

// creer_coord : crée une coordonnée avec les valeurs x et y données
coord_t creer_coord(int x, int y);


// get_x : récupère la coordonnée x
int get_x(coord_t c);


// get_y : récupère la coordonnée y 
int get_y(coord_t c);
