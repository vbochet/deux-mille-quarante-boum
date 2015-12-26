/* FONCTIONS POUR LES BOMBES */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "struct.h"
#include "utils.h"

/* @requires 0<=h<hauteur, 0<=l<largeur
   @assigns tab
   @ensures à la fin, on a fait disparaitre les cases touchées par l'explosion de la bombe sélectionnée
   @*/
void explosion(obj** tab, int hauteur, int largeur, int* cases_vides, int h, int l)
{
	obj bombe;
	int m,n; /* variables de boucle */
	
	bombe = tab[h][l];
	
	tab[h][l].valeur = 0; /* on fait "exploser" la bombe : la case sur laquelle elle était devient vide */
	*cases_vides = *cases_vides + 1; /* on rajoute une case vide au compteur */
	
	/* on traite ensuite les cases alentour, selon le type de bombe */
	if(bombe.valeur <= -21) { /* si c'est un *, on regarde toutes les cases dans un rayon de 1 case autour de la position de la bombe */
		for(m = h-1; m <= h+1; m=m+1) {
			if((m >= 0) && (m < hauteur)) { /* si la case qu'on veut traiter existe bien (càd qu'elle est dans le tableau, donc m compris entre 0 et hauteur-1) */
				for(n = l-1; n <= n+1; n = n+1) {
					if((n >= 0) && (n < largeur)) {/* si la case qu'on veut traiter existe bien (càd qu'elle est dans le tableau, donc n compris entre 0 et largeur-1) */
						if(tab[m][n].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
							explosion(tab, hauteur, largeur, cases_vides, m, n);
						}
						else { /* sinon, on fait simplement disparaitre l'élément du tableau */
							if(tab[m][n].valeur != 0) { /* si la case contient un nombre positif */
								tab[m][n].valeur = 0; /* on vide la case */
								*cases_vides = *cases_vides + 1; /* on rajoute une case vide au compteur */
							}
							/* sinon, c'est que la case est déjà vide, donc rien à faire */
						}
					}
				}
			}
		}
	}
	else if(bombe.valeur <= -11) { /* si c'est un x, on regarde les cases en diagonale autour de la position de la bombe */
		if((h-1 >= 0) && (l-1 >= 0)) { /* la case en diagonale haut-gauche existe-t-elle ? */
			if(tab[h-1][l-1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, cases_vides, h-1, l-1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				if(tab[h-1][l-1].valeur != 0) { /* si la case contient un nombre positif */
					tab[h-1][l-1].valeur = 0; /* on vide la case */
					*cases_vides = *cases_vides + 1; /* on rajoute une case vide au compteur */
				}
				/* sinon, c'est que la case est déjà vide, donc rien à faire */
			}
		}
		
		if((h-1 >= 0) && (l+1 < largeur)) { /* la case en diagonale haut-droite existe-t-elle ? */
			if(tab[h-1][l+1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, cases_vides, h-1, l+1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				if(tab[h-1][l+1].valeur != 0) { /* si la case contient un nombre positif */
					tab[h-1][l+1].valeur = 0; /* on vide la case */
					*cases_vides = *cases_vides + 1; /* on rajoute une case vide au compteur */
				}
				/* sinon, c'est que la case est déjà vide, donc rien à faire */
			}
		}
		
		if((h+1 < hauteur) && (l-1 >= 0)) { /* la case en diagonale bas-gauche existe-t-elle ? */
			if(tab[h+1][l-1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, cases_vides, h+1, l-1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				if(tab[h+1][l-1].valeur != 0) { /* si la case contient un nombre positif */
					tab[h+1][l-1].valeur = 0; /* on vide la case */
					*cases_vides = *cases_vides + 1; /* on rajoute une case vide au compteur */
				}
				/* sinon, c'est que la case est déjà vide, donc rien à faire */
			}
		}
		
		if((h+1 < hauteur) && (l+1 < largeur)) { /* la case en diagonale bas-gauche existe-t-elle ? */
			if(tab[h+1][l+1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, cases_vides, h+1, l+1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				if(tab[h+1][l+1].valeur != 0) { /* si la case contient un nombre positif */
					tab[h+1][l+1].valeur = 0; /* on vide la case */
					*cases_vides = *cases_vides + 1; /* on rajoute une case vide au compteur */
				}
				/* sinon, c'est que la case est déjà vide, donc rien à faire */
			}
		}
	}
	else if(bombe.valeur <= -1) { /* si c'est un +, on regarde les cases latérales autour de la position de la bombe */
		if(l-1 >= 0) { /* la case à gauche existe-t-elle ? */
			if(tab[h][l-1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, cases_vides, h, l-1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				if(tab[h][l-1].valeur != 0) { /* si la case contient un nombre positif */
					tab[h][l-1].valeur = 0; /* on vide la case */
					*cases_vides = *cases_vides + 1; /* on rajoute une case vide au compteur */
				}
				/* sinon, c'est que la case est déjà vide, donc rien à faire */
			}
		}
		
		if(l+1 < largeur) { /* la case à droite existe-t-elle ? */
			if(tab[h][l+1].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, cases_vides, h, l+1);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				if(tab[h][l+1].valeur != 0) { /* si la case contient un nombre positif */
					tab[h][l+1].valeur = 0; /* on vide la case */
					*cases_vides = *cases_vides + 1; /* on rajoute une case vide au compteur */
				}
				/* sinon, c'est que la case est déjà vide, donc rien à faire */
			}
		}
		
		if(h+1 < hauteur) { /* la case en dessous existe-t-elle ? */
			if(tab[h+1][l].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, cases_vides, h+1, l);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				if(tab[h+1][l].valeur != 0) { /* si la case contient un nombre positif */
					tab[h+1][l].valeur = 0; /* on vide la case */
					*cases_vides = *cases_vides + 1; /* on rajoute une case vide au compteur */
				}
				/* sinon, c'est que la case est déjà vide, donc rien à faire */
			}
		}
		
		if(h-1 >= 0) { /* la case au dessus existe-t-elle ? */
			if(tab[h-1][l].valeur < 0) { /* si la case voisine est une bombe, on la fait exploser aussi */
				explosion(tab, hauteur, largeur, cases_vides, h-1, l);
			}
			else { /* sinon, on fait simplement disparaitre l'élément du tableau */
				if(tab[h-1][l].valeur != 0) { /* si la case contient un nombre positif */
					tab[h-1][l].valeur = 0; /* on vide la case */
					*cases_vides = *cases_vides + 1; /* on rajoute une case vide au compteur */
				}
				/* sinon, c'est que la case est déjà vide, donc rien à faire */
			}
		}
	}
}


/* @requires hauteur > 0, largeur > 0
   @assigns tab
   @ensures à la fin, les bombes ont toutes été vérifiées, leur compteur a été incrémenté, les bombes vieilles de 8 tours ont explosé
   @*/
void check_bombes(obj** tab, int hauteur, int largeur, int* cases_vides)
{
	int h, l; /* variables de boucle sur la hauteur et la largeur du tableau */
	
	for(h = 0; h < hauteur; h = h+1) {
		for(l = 0; l < largeur; l = l+1) {
			if(tab[h][l].valeur < 0) { /* si c'est une bombe, on effectue un traitement spécifique, sinon on passe à la case suivante */
			
				tab[h][l].valeur = tab[h][l].valeur - 1; /* la bombe a "vécu" un tour supplémentaire, symbolisé par sa valeur qui perd une unité */
				
				if((tab[h][l].valeur == -8) || (tab[h][l].valeur == -18) || (tab[h][l].valeur == -28)) { /* pour ces valeurs, la bombe a été sur le tableau pendant 7 tours et entame son 8e tour, il faut donc la faire exploser */
					explosion(tab, hauteur, largeur, cases_vides, h, l);
				}
			}
		}
	}
}


/* @requires hauteur>1, largeur>1
   @assigns
   @ensures affiche le tableau en mettant en évidence la bombe sélectionnée à l'aide d'accolades {}
   @*/
void affich_choix_bombe(obj** tab, int hauteur, int largeur, int val_max, int coordh, int coordl) {
	
  int h, l; /* variables de boucle sur la hauteur et la largeur du tableau */
  int n; /* variable de boucle for */
  int nb_chiffres; /* nombre de chiffres de la valeur maximale du tableau, pour gérer un affichage correct */
  
  /* on veut un affichage avec des colonnes de largeur minimale 3, et plus si la valeur maximale du tableau est supérieure à 999 */
  nb_chiffres = max(3, log10(val_max)+1); 
  
	for(h = 0; h < hauteur; h = h+1) { /* boucle sur les lignes */
		/* affichage de la barre horizontale en haut de la ligne en cours */
		printf("-");
		for(n = 1; n <= largeur * (nb_chiffres+1); n = n+1) {
			printf("-");
		}
		printf("\n");

		/* affichage d'une première ligne "vide" car chaque ligne est affichée sur 3 lignes de texte */
		for(l=0; l<largeur; l=l+1) {
			printf("|%*s", nb_chiffres, ""); /* on utilise %*s pour pouvoir adapter la taille de l'affichage*/
		}
		printf("|\n");

		/* affichage des lignes comportant du contenu */
		for(l = 0; l < largeur; l = l+1) {
			if((tab[h][l]).valeur > 0) { /* si la case contient un nombre positif, on affiche son contenu */
				printf("|%*d", nb_chiffres, (tab[h][l]).valeur); /* idem ici pour %*d, on peut adapter la taille de l'affichage de l'int */
			}
			else if((tab[h][l]).valeur < -21) { /* si la case contient un nombre < -21, on affiche une bombe * */
				if((h == coordh) && (l == coordl)) {
					printf("|%*s", nb_chiffres, "{*}");
				}
				else {
					printf("|%*s", nb_chiffres, "*");
				}					
			}
			else if((tab[h][l]).valeur < -11) { /* si la case contient un nombre < -11, on affiche une bombe x (pas de souci avec les bombes * car le cas où la valeur de la case est < -21 est déjà traité dans un else if) */
				if((h == coordh) && (l == coordl)) {
					printf("|%*s", nb_chiffres, "{x}");
				}
				else {
					printf("|%*s", nb_chiffres, "x");
				}	 
			}
			else if((tab[h][l]).valeur < -1) { /* si la case contient un nombre < -1, on affiche une bombe + (pas de souci avec les bombes x et * car le cas où la valeur de la case est < -11 ou -21 est déjà traité dans des else if) */
				if((h == coordh) && (l == coordl)) {
					printf("|%*s", nb_chiffres, "{+}");
				}
				else {
					printf("|%*s", nb_chiffres, "+");
				}	
			}
			else {
				printf("|%*s", nb_chiffres, ""); /* si la case est vide, on n'affiche pas de contenu */
			}
		}
		printf("|\n");

		/* affichage de la troisième ligne "vide" */
		for(l = 0; l < largeur; l = l+1) {
			printf("|%*s", nb_chiffres, "");
		}
		printf("|\n");
	}
  
  /* affichage de la barre horizontale fermant le tableau */
    printf("-");
	for(n=1; n<=largeur*(nb_chiffres+1); n=n+1) {
		printf("-");
    }
    printf("\n");
	printf("\n");
}

