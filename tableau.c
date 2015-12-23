/* FONCTIONS DE GESTION DU TABLEAU */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "struct.h"
#include "utils.h"


/* @requires hauteur>1, largeur>1, cases_vides>0
   @assigns tab, cases_vides
   @ensures à la fin, le nouvel objet est placé au bon endroit dans le tableau
   @*/
void remplir_tableau(obj** tableau, int hauteur, int largeur, int* cases_vides, obj nouv_objet)
{
    int h, l; /* variables de boucles sur les lignes (hauteur) et les colonnes (largeur) */
	int cpt; /* compteur sur le nombre de cases vides rencontrées */
	
    h=0; 
	cpt=0;

    while(h < hauteur) { /* s'arrête car on incrémente de 1 le compteur à chaque fois */
	
        l = 0; /* on réinitialise le compteur des colonnes à chaque nouvelle ligne */
		
        while(l < largeur) { /* s'arrête pour les mêmes raisons que la boucle précédente */
		
            if((tableau[h][l]).valeur == 0) { /* si la case est vide */
			
                if(nouv_objet.position == cpt) { /* si c'est la position pour le nouvel objet, on l'y place et on termine la boucle */
                    tableau[h][l] = nouv_objet;
                    h = hauteur; /* on met fin à la boucle sur h */
                    l = largeur; /* on met fin à la boucle sur l */
					*cases_vides = *cases_vides - 1; 
                }
				
                else { /* ce n'est pas la bonne position, on va regarder à la position suivante */
                    l = l+1; /* on incrémente le compteur de boucle */
                    cpt = cpt+1; /* on incrémente le compteur de cases vides rencontrées */
                }
            }
            else { /* sinon, la case n'est pas vide, donc on incrémente le compteur pour traiter la case suivante */
                l = l+1;
            }
        }
        h = h+1;
    }
}


/* @requires hauteur>1, largeur>1
   @assigns
   @ensures affiche le tableau
   @*/
void print_tableau(obj** tab, int hauteur, int largeur, int val_max) /* fonction d'affichage du tableau de jeu */
{
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
			else if((tab[h][l]).valeur <= -21) { /* si la case contient un nombre <= -21, on affiche une bombe * */
				printf("|%*s", nb_chiffres, "*");
			}
			else if((tab[h][l]).valeur <= -11) { /* si la case contient un nombre <= -11, on affiche une bombe x (pas de souci avec les bombes * car le cas où la valeur de la case est <= -21 est déjà traité dans un else if) */
				printf("|%*s", nb_chiffres, "x");
			}
			else if((tab[h][l]).valeur <= -1) { /* si la case contient un nombre <= -1, on affiche une bombe + (pas de souci avec les bombes x et * car le cas où la valeur de la case est <= -11 ou -21 est déjà traité dans des else if) */
				printf("|%*s", nb_chiffres, "+");
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


/* @requires hauteur>1
   @assigns
   @ensures libère les lignes du tableau, puis le tableau
   @*/
void liberer_tableau(obj** tableau, int hauteur){ /* fonction libérant toute la mémoire allouée au tableau */
	int h; /* variable de boucle portant sur la hauteur du tableau */
	for(h = 0 ; h < hauteur ; h = h+1) { /* on libère d'abord toutes les lignes du tableau */
		free(tableau[h]);
	}
	free(tableau); /* puis on libère ce qui reste */
}

