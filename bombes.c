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
				explosion(tab, hauteur, largeur, h-1, l-1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				tab[h-1][l+1].valeur = 0;
			}
		}
		
		if((h+1 < hauteur) && (l-1 > 0)) { /* la case en diagonale bas-gauche existe-t-elle ? */
			if(tab[h+1][l-1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, h-1, l-1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				tab[h+1][l-1].valeur = 0;
			}
		}
		
		if((h+1 < hauteur) && (l+1 < largeur)) { /* la case en diagonale bas-gauche existe-t-elle ? */
			if(tab[h+1][l+1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, h-1, l-1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				tab[h+1][l+1].valeur = 0;
			}
		}
	}
}


/* @requires
   @assigns
   @ensures
   @*/
void check_bombes(obj** tab, int hauteur, int largeur)
{
	
}

