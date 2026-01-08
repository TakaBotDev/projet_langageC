#include "dijkstra.h"
#include "stdlib.h"
/*#include "animation.h"*/

/**
 * cout : calcule le coût pour rejoindre le noeud suivant depuis le noeud
 * courant. Ce coût est égal à la distance euclidienne entre les deux noeuds,
 * plus le dénivelé entre ces deux noeuds s'il est positif.
 * 
 * Pré-conditions :
 *  - dans_les_bornes(grille, courant)
 *  - dans_les_bornes(grille, suivant)
 * Post-conditions :
 *  - cout > 0, potentiellement infini (INFINITIY)
 *
 * @param grille heightmap contenant les hauteurs
 * @param courant noeud duquel on part pour calculer le coût
 * @param suivant noeud auquel on arrive pour calculer le coût
 * @return coût pour passer de courant à suivant
 */
static float cout(grille_t grille, coord_t courant, coord_t suivant) {
        float dist = distance_euclidienne(courant, suivant);
        float h_cour = get_hauteur(grille, courant);
        float h_suiv = get_hauteur(grille, suivant);
        float denivele = h_suiv - h_cour;
        
        if (denivele > 0.0f) {
                return dist + denivele;
        } else {
                return dist;
        }
}

/**
 * construire_chemin_vers - Construit le chemin depuis le noeud de départ donné vers le
 * noeud donné. On passe un chemin en entrée-sortie de la fonction, qui est mis à jour
 * par celle-ci.
 *
 * Ce sous-programme fonctionne récursivement :
 *  1. Si le noeud est égal au noeud de départ, on a fini
 *  2. Sinon, on construit le chemin du départ au noeud précédent (appel récursif)
 *  3. Dans tous les cas, on ajoute le noeud au chemin, avec les caractéristiques associées dans visites
 *
 * @param chemin [in/out] chemin dans lequel enregistrer les étapes depuis le départ vers noeud
 * @param visites [in] liste des noeuds visités créée par l'algorithme de Dijkstra
 * @param source noeud de départ du chemin
 * @param noeud noeud vers lequel on veut construire le chemin depuis le départ
 */
static void construire_chemin_vers(
                                liste_noeud_t* chemin,
                                liste_noeud_t* visites,
                                coord_t source,
                                coord_t noeud
                        ){
        if ( memes_coord(noeud, source) ) {
                return;
        } else {
                coord_t prec = precedent_noeud_liste(visites, noeud);
                
                construire_chemin_vers(chemin, visites, source, prec);

                float cout_prec = cout_noeud_liste(visites, prec);
                inserer_noeud_liste(chemin, prec, precedent_noeud_liste(visites, prec), cout_prec);
        }
}



float dijkstra(
        grille_t grille, 
        coord_t source, coord_t destination, 
        float seuil,
        liste_noeud_t** chemin
    ) {
        
        liste_noeud_t* a_visiter = creer_liste();
        liste_noeud_t* visites = creer_liste();

        inserer_noeud_liste(a_visiter, source, source, 0.0f);

        while (! est_vide_liste(a_visiter)) {
                coord_t noeud_courant = min_noeud_liste(a_visiter);
                float cout_courant = cout_noeud_liste(a_visiter, noeud_courant);
                coord_t prec_courant = precedent_noeud_liste(a_visiter, noeud_courant);

                inserer_noeud_liste(visites, noeud_courant, prec_courant, cout_courant);
                supprimer_noeud_liste(a_visiter, noeud_courant);

                coord_t* voisins = NULL;
                size_t nb_voisins = get_voisins(grille, noeud_courant, seuil, &voisins);

                for (size_t i = 0; i < nb_voisins; i++) {
                        coord_t nv = voisins[i];

                        if (contient_noeud_liste(visites, nv)) {
                                continue;
                        }

                        float cout_vers_voisin = cout(grille, noeud_courant, nv);
                        float nouveau_cout = cout_courant + cout_vers_voisin;

                        float cout_actuel = cout_noeud_liste(a_visiter, nv);

                        if (nouveau_cout < cout_actuel) {
                                inserer_noeud_liste(a_visiter, nv, noeud_courant, nouveau_cout);
                        }
                }

                free(voisins);
        }
        
        float cout_final = cout_noeud_liste(visites, destination);
        if (chemin != NULL) {
                *chemin = creer_liste();
                
                inserer_noeud_liste(*chemin, source, source, 0.0f);
                
                construire_chemin_vers(*chemin, visites, source, destination);
                
                float cout_dest = cout_noeud_liste(visites, destination);
                inserer_noeud_liste(*chemin, destination, precedent_noeud_liste(visites, destination), cout_dest);
        }
        
        detruire_liste(&a_visiter);
        detruire_liste(&visites);
        
        return cout_final;
        
}


