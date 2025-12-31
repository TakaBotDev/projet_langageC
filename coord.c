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
