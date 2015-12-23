/* FONCTIONS POUR LES BOMBES */


#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

/* @requires 0<=h<hauteur, 0<=l<largeur
   @assigns tab
   @ensures à la fin, on a fait disparaitre les cases touchées par l'explosion de la bombe sélectionnée
   @*/
void explosion(obj** tab, int hauteur, int largeur, int h, int l)
{
	obj bombe;
	int type; /* type de bombe : 1 -> +, 2 -> x, 3 -> * */
	int m,n; /* variables de boucle */
	
	bombe = tab[h][l];
	type = (bombe.valeur <= -1) + (bombe.valeur <= -11) + (bombe.valeur <= -21);
	
	tab[h][l].valeur = 0; /* on fait "exploser" la bombe : la case sur laquelle elle était devient vide */
	
	/* on traite ensuite les cases alentour, selon le type de bombe */
	if(type == 3) { /* si c'est un *, on regarde toutes les cases dans un rayon de 1 case autour de la position de la bombe */
		for(m = h-1; m <= h+1; m=m+1) {
			if((m >= 0) && (m < hauteur)) { /* si la case qu'on veut traiter existe bien (càd qu'elle est dans le tableau, donc m compris entre 0 et hauteur-1) */
				for(n = l-1; n <= n+1; n = n+1) {
					if((n >= 0) && (n < largeur)) {/* si la case qu'on veut traiter existe bien (càd qu'elle est dans le tableau, donc n compris entre 0 et largeur-1) */
						if(tab[m][n].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
							explosion(tab, hauteur, largeur, m, n);
						}
						else { /* sinon, on fait simplement disparaitre l'élément du tableau */
							tab[m][n].valeur = 0;
						}
					}
				}
			}
		}
	}
	else if(type == 2) { /* si c'est un x, on regarde les cases en diagonale autour de la position de la bombe */
		if((h-1 > 0) && (l-1 > 0)) { /* la case en diagonale haut-gauche existe-t-elle ? */
			if(tab[h-1][l-1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, h-1, l-1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				tab[h-1][l-1].valeur = 0;
			}
		}
		
		if((h-1 > 0) && (l+1 < largeur)) { /* la case en diagonale haut-droite existe-t-elle ? */
			if(tab[h-1][l+1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, h-1, l+1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				tab[h-1][l+1].valeur = 0;
			}
		}
		
		if((h+1 < hauteur) && (l-1 > 0)) { /* la case en diagonale bas-gauche existe-t-elle ? */
			if(tab[h+1][l-1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, h+1, l-1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				tab[h+1][l-1].valeur = 0;
			}
		}
		
		if((h+1 < hauteur) && (l+1 < largeur)) { /* la case en diagonale bas-gauche existe-t-elle ? */
			if(tab[h+1][l+1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, h+1, l+1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				tab[h+1][l+1].valeur = 0;
			}
		}
	}
	else if(type == 1) { /* si c'est un +, on regarde les cases latérales autour de la position de la bombe */
		if(l-1 > 0) { /* la case à gauche existe-t-elle ? */
			if(tab[h][l-1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, h, l-1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				tab[h][l-1].valeur = 0;
			}
		}
		
		if(l+1 < largeur) { /* la case à droite existe-t-elle ? */
			if(tab[h][l+1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, h, l-1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				tab[h][l+1].valeur = 0;
			}
		}
		
		if(h+1 < hauteur) { /* la case en dessous existe-t-elle ? */
			if(tab[h+1][l].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, h-1, l);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				tab[h+1][l].valeur = 0;
			}
		}
		
		if(h-1 > 0) { /* la case au dessus existe-t-elle ? */
			if(tab[h-1][l].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, h-1, l);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				tab[h-1][l].valeur = 0;
			}
		}
	}
}


/* @requires hauteur > 0, largeur > 0
   @assigns tab
   @ensures à la fin, les bombes ont toutes été vérifiées, leur compteur a été incrémenté, les bombes vieilles de 8 tours ont explosé
   @*/
void check_bombes(obj** tab, int hauteur, int largeur)
{
	int h, l; /* variables de boucle sur la hauteur et la largeur du tableau */
	
	for(h = 0; h < hauteur; h = h+1) {
		for(l = 0; l < largeur; l = l+1) {
			if(tab[h][l].valeur < 0) { /* si c'est une bombe, on effectue un traitement spécifique, sinon on passe à la case suivante */
				tab[h][l].valeur = tab[h][l].valeur - 1; /* la bombe a "vécu" un tour supplémentaire, symbolisé par sa valeur qui perd une unité */
				if((tab[h][l].valeur == -8) || (tab[h][l].valeur == -18) || (tab[h][l].valeur == -28)) { /* pour ces valeurs, la bombe a été sur le tableau pendant 7 tours et entame son 8e tour, il faut donc la faire exploser */
					explosion(tab, hauteur, largeur, h, l);
				}
			}
		}
	}
}

