#include "coord.h"

coord_t creer_coord(int x, int y) {
    coord_t resultat;
    resultat.x = x;
    resultat.y = y;
    return resultat;
}


int get_x(coord_t position) {
    return position.x;
}


int get_y(coord_t position) {
    return position.y;
}


void set_x(coord_t* position, int x) {
    (*position).x = x;
}


void set_y(coord_t* position, int y) {
    (*position).y = y;
}


bool memes_coord(coord_t c1, coord_t c2) {
    return (c1.x == c2.x) && (c1.y == c2.y);
}


coord_t translation(coord_t position, int dx, int dy) {
    return creer_coord(position.x + dx, position.y + dy);
}


float distance_euclidienne(coord_t p1, coord_t p2) {
    int diffx = p2.x - p1.x;
    int diffy = p2.y - p1.y;
    return (float)((diffx * diffx + diffy * diffy)^(1/2));
}
