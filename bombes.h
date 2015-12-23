/* FONCTIONS POUR LES BOMBES */

#ifndef __BOMBES_H
#define __BOMBES_H

void explosion(obj** tab, int hauteur, int largeur, int h, int l);
void check_bombes(obj** tab, int hauteur, int largeur);
void affich_choix_bombe(obj** tab, int hauteur, int largeur, int val_max, int coordh, int coordl);

#endif