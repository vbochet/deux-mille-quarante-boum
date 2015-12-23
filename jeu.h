/* FONCTIONS POUR LES DIFFÉRENTES PARTIES DU JEU */

#ifndef __JEU_H
#define __JEU_H

#include "struct.h" /* on doit inclure la structure obj pour toutes les fonctions définies ici */

obj nouvel_objet(int cases_vides, int valeur_max);
char choix_action(obj** tab, int hauteur, int largeur, int val_max, int nb_chiffres, int* coordh, int* coordl);
void execute_action(obj** tab, int hauteur, int largeur, int* val_max, int* cases_vides, int nb_tour, char action, int coordh, int coordl);
void tour(obj** tab, int hauteur, int largeur, int* val_max, int* cases_vides, int* n_tour, int* quitter);

#endif