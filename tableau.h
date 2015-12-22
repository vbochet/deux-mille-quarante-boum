/* FONCTIONS DE GESTION DU TABLEAU */

#ifndef __TABLEAU_H
#define __TABLEAU_H

void remplir_tableau(obj** tableau, int hauteur, int largeur, int* cases_vides, obj nouv_objet);
void print_tableau(obj** tab, int hauteur, int largeur, int val_max);

#endif