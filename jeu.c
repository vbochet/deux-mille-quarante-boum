/* FONCTIONS POUR LES DIFFÉRENTES PARTIES DU JEU */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "struct.h"
#include "utils.h"
#include "tableau.h"


/* @requires cases_vides>0
   @assigns
   @ensures renvoie un objet à ajouter dans le tableau
   @*/
obj nouvel_objet(int cases_vides, int valeur_max) /* génère un nouvel objet aléatoirement */
{
    obj nouv_objet;
    int valeur; /* la valeur du nouvel objet */

    if(valeur_max < 64) {
		valeur = 1;
	}
    else if(valeur_max < 256) { /* 80% de chances d'avoir un 1, 20% d'avoir un 2 */
		valeur = (alea_bornes(0,100) > 80) + 1;
	}
    else { /* 65% de chances d'avoir un 1, 35% d'avoir un 2 */
		valeur = (alea_bornes(0,100) > 65) + 1;
	}

    nouv_objet.position = alea_bornes(0,cases_vides); /* numéro de la case vide où placer ce nouvel objet */
    nouv_objet.fusion = 0; /* l'objet ne résulte pas d'une fusion, donc fusion=0 qui est inférieur au n° du tour */
    nouv_objet.valeur = valeur;

    return nouv_objet;
}


/* @requires hauteur>1, largeur>1, nb_chiffres>0
   @assigns 
   @ensures à la fin, le joueur a effectué un choix de mouvement valide
   @*/
char choix_action(obj** tab, int hauteur, int largeur, int val_max, int nb_chiffres) /* fonction de demande de choix au joueur */
{
	int faire_boucle, n; /* variables de boucle */
	char action; /* choix d'action du joueur (i, j, k, l, q, h) */
	char buffer[2]; /* 2 car 1 caractère PLUS le \0 des chaînes */
	
	faire_boucle = 1;
	
	while(faire_boucle==1) /* se terminera lorsque le joueur aura effectué un choix correct et qu'il l'aura validé */
	{
		system("clear");
		print_tableau(tab, hauteur, largeur, val_max); /* on affiche le tableau */

		printf("Que faire ? ");
	
		/*affichage d'espaces pour situer l'invite à droite du tableau*/
		for(n = 1; n <= (largeur*(nb_chiffres+1)) - 12; n=n+1) { /* 12 = nombre de caractères de la question */
			printf(" ");
		}
		
		scanf("%1s", buffer); /* récupération du choix de l'utilisateur */
		action=buffer[0];
		
		switch(action) {
			case 'i':
				printf("Vous avez choisi de vous déplacer vers le haut. \n");
				faire_boucle=confirmation();
			break;
			
			case 'j':
				printf("Vous avez choisi de vous déplacer vers la gauche. \n");
				faire_boucle=confirmation();
			break;
			
			case 'k':
				printf("Vous avez choisi de vous déplacer vers le bas. \n");
				faire_boucle=confirmation();
			break;
			
			case 'l':
				printf("Vous avez choisi de vous déplacer vers la droite. \n");
				faire_boucle=confirmation();
			break;
			
			case 'q':
				printf("Vous avez choisi de quitter la partie. \n");
				faire_boucle=confirmation();
			break;
			
			case 'h':
				system("clear");
				printf("AIDE \n\n");
				printf("- i => déplacement vers le haut\n");
				printf("- j => déplacement vers la gauche\n");
				printf("- k => déplacement vers le bas\n");
				printf("- l => déplacement vers la droite\n");
				printf("- q => quitter la partie\n");
				printf("- h => revenir ici (à l'aide)\n");
				printf("\nPour revenir au jeu, entrez un caractère : ");
				scanf("%1s", buffer); /* on demande juste un caractère pour que l'utilisateur puisse prendre le temps de lire l'aide, puis revenir au choix, mais on n'a pas besoin de conserver sa valeur, donc on utilise void */
			break;
			
			default:
				printf("erreur\n"); /* ne se produit pas */
		}
	}
	
	return action;
}


/* @requires hauteur>1, largeur>1, action in {i,j,k,l}
   @assigns tab, val_max, cases_vides
   @ensures à la fin, on a effectué tous les déplacements du tour
   @*/
int execute_action(obj** tab, int hauteur, int largeur, int* val_max, int* cases_vides, int nb_tour, char action) /* effectue l'action choisie */
{
	int h,l; /*variables de boucles correspondant aux lignes et aux colonnes*/
	int m,n; /*idem*/
	
	int actions_exec; /* vaut 0 si aucune action n'a pu être effectuée, 1 sinon */
	
	actions_exec = 0; 
	
	switch(action) {
		case 'i': /*déplacement vers le haut*/
			for (h = 1; h < hauteur; h = h+1) {
				for (l = 0; l < largeur; l = l+1) {
					m = h; /* seconde variable sur la hauteur */
					while(m > 0) { /* se termine car on décrémente m à chaque tour. Pas une boucle for car on souhaite pouvoir terminer la boucle plus vite en affectant 0 à m directement */
						if(tab[m][l].valeur != 0) { /* si la case n'est pas vide, on agit */
							if(tab[m-1][l].valeur == 0) { /* si la case située au dessus est vide, on peut y déplacer l'élément actuellement en cours de traitement */
								tab[m-1][l].valeur = tab[m][l].valeur; /* on swap les cases */
								tab[m][l].valeur = 0;
								m = m-1; /* on travaille sur la case du dessus pour poursuivre le déplacement */
									
								actions_exec = 1; /* on a fait une action, le choix du joueur était donc autorisé */
							}
							else if((tab[m-1][l].valeur==tab[m][l].valeur) && (tab[m-1][l].fusion<nb_tour)) { /* si la case située au dessus a la même valeur que la case en cours de traitement, et que la case au dessus ne résulte pas d'une fusion à ce tour, on les "fusionne" */
								tab[m-1][l].valeur = tab[m-1][l].valeur + tab[m][l].valeur;
								tab[m-1][l].fusion = nb_tour;
								tab[m][l].valeur = 0;
								*cases_vides = *cases_vides + 1; /* on a vidé une case du tableau */
								
								if(*val_max < tab[m-1][l].valeur) { /* si la valeur maximale du tableau est celle que l'on vient de créer, on met à jour la valeur de la variable correspondante */
									*val_max = tab[m-1][l].valeur;
								}
								m = 0; /* on sort de la boucle dès lors qu'on a fait une somme avec une autre case. en effet, si on ne s'arrête pas, on risque de sommer des cases qui viennent d'être crées pendant le tour */
									
								actions_exec = 1; /* on a fait une action, le choix du joueur était donc autorisé */
							}
							else { /* si on ne peut pas faire de mouvement, on arrête la boucle */
								m = 0;
							}
						}
						else { /* si on n'avait pas une case vide, on met fin à la boucle */
							m = 0;
						}
					}
				}
			}
		break;
		
		/* Les autres déplacements sont sur le même principe et seront par conséquent moins commentés */
		case 'j': /* déplacement vers la gauche */
			for(l = 1; l < largeur; l = l+1) {
				for(h = 0; h < hauteur; h = h+1) {
					n = l;
					while(n > 0) { /* se termine car n est décrémenté. Pas de boucle for car on veut pouvoir interrompre la boucle à tout moment */
						if(tab[h][n].valeur != 0) { /* si la case n'est pas vide, on agit */
							if(tab[h][n-1].valeur == 0) { /* si la case située à gauche est vide, on peut y déplacer l'élément actuellement en cours de traitement */
								tab[h][n-1].valeur = tab[h][n].valeur;
								tab[h][n].valeur = 0;
								n = n-1;
									
								actions_exec = 1; /* on a fait une action, le choix du joueur était donc autorisé */
							}
							else if((tab[h][n-1].valeur == tab[h][n].valeur) && (tab[h][n-1].fusion < nb_tour)) { /* si la case située à gauche a la même valeur que la case en cours de traitement, et que la case à gauche ne résulte pas d'une fusion à ce tour, on les "fusionne" */
								tab[h][n-1].valeur = tab[h][n-1].valeur + tab[h][n].valeur;
								tab[h][n-1].fusion = nb_tour;
								tab[h][n].valeur = 0;
								*cases_vides = *cases_vides + 1; /* on a libéré une case du tableau */
								
								if(*val_max < tab[h][n-1].valeur) { /* si la valeur maximale du tableau est celle que l'on vient de créer, on met à jour la valeur de la variable correspondante */
									*val_max = tab[h][n-1].valeur;
								}
								n = 0;
									
								actions_exec = 1; /* on a fait une action, le choix du joueur était donc autorisé */
							}
							else { /*si on ne peut pas faire de mouvement, on arrête la boucle*/
								n = 0;
							}
						}
						else { /*si on n'avait pas une case vide, on met fin à la boucle*/
							n = 0;
						}
					}
				}
			}
		break;
		
		case 'k': /* déplacement vers le bas */
			for(h = hauteur-2; h >= 0; h = h-1) {
				for(l = 0; l < largeur; l = l+1) {
					m = h;
					while(m < hauteur-1) { /* se termine car on incrémente m */
						if(tab[m][l].valeur != 0) { /* si la case n'est pas vide, on agit */
							if(tab[m+1][l].valeur == 0) { /* si la case située en dessous est vide, on peut y déplacer l'élément actuellement en cours de traitement */
								tab[m+1][l].valeur = tab[m][l].valeur;
								tab[m][l].valeur = 0;
								m = m+1;
									
								actions_exec = 1; /* on a fait une action, le choix du joueur était donc autorisé */
							}
							else if((tab[m+1][l].valeur == tab[m][l].valeur) && (tab[m+1][l].fusion < nb_tour)) { /* si la case située en dessous a la même valeur que la case en cours de traitement, et que la case en dessous ne résulte pas d'une fusion à ce tour, on les "fusionne" */
								tab[m+1][l].valeur = tab[m+1][l].valeur + tab[m][l].valeur;
								tab[m+1][l].fusion = nb_tour;
								tab[m][l].valeur = 0;
								*cases_vides = *cases_vides + 1; /* on a libéré une case du tableau */
								
								if(*val_max < tab[m+1][l].valeur) { /* si la valeur maximale du tableau est celle que l'on vient de créer, on met à jour la valeur de la variable correspondante */
									*val_max = tab[m+1][l].valeur;
								}
								m = hauteur;
									
								actions_exec = 1; /* on a fait une action, le choix du joueur était donc autorisé */
							}
							else { /* si on ne peut pas faire de mouvement, on arrête la boucle */
								m = hauteur;
							}
						}
						else { /* si on n'avait pas une case vide, on met fin à la boucle */
							m = hauteur;
						}
					}	
				}
			}
		break;
		
		case 'l': /* déplacement vers la droite */
			for(l = largeur-2; l >= 0; l = l-1) {
				for(h = 0; h < hauteur; h = h+1) {
					n = l;
					while(n < largeur-1) { /* se termine car on incrémente n */
						if(tab[h][n].valeur != 0) { /* si la case n'est pas vide, on agit */
							if(tab[h][n+1].valeur == 0) { /* si la case située à droite est vide, on peut y déplacer l'élément actuellement en cours de traitement */
								tab[h][n+1].valeur = tab[h][n].valeur;
								tab[h][n].valeur = 0;
								n = n+1;
									
								actions_exec = 1; /* on a fait une action, le choix du joueur était donc autorisé */
							}
							else if((tab[h][n+1].valeur == tab[h][n].valeur) && (tab[h][n+1].fusion < nb_tour)) { /* si la case située à droite a la même valeur que la case en cours de traitement, et que la case à droite ne résulte pas d'une fusion à ce tour, on les "fusionne" */
								tab[h][n+1].valeur = tab[h][n+1].valeur + tab[h][n].valeur;
								tab[h][n+1].fusion = nb_tour;
								tab[h][n].valeur = 0;
								*cases_vides = *cases_vides + 1; /*on a libéré une case du tableau*/
								
								if(*val_max < tab[h][n+1].valeur) { /*si la valeur maximale du tableau est celle que l'on vient de créer, on met à jour la valeur de la variable correspondante*/
									*val_max = tab[h][n+1].valeur;
								}
								n = largeur;
									
								actions_exec = 1; /* on a fait une action, le choix du joueur était donc autorisé */
							}
							else {
								n = largeur;
							}
						}
						else {
							n = largeur;
						}
					}
				}
			}
		break;
	}
	
	return actions_exec;
}


/* @requires hauteur>1, largeur>1, *val_max>0, *cases_vides>0
   @assigns tab, val_max, cases_vides, n_tour
   @ensures à la fin, le joueur a effectué un tour de jeu complet
   @*/
void tour(obj** tab, int hauteur, int largeur, int* val_max, int* cases_vides, int* n_tour, int* quitter)
{
    obj nouvel_obj;
	int nb_chiffres;
	char action;
	int succes;
	
	nb_chiffres = max(3, log10(*val_max)+1);
	*n_tour = *n_tour+1;
	
    nouvel_obj = nouvel_objet(*cases_vides, *val_max); /*on génère le nouvel objet à ajouter à notre tableau de jeu*/
	
    remplir_tableau(tab, hauteur, largeur, cases_vides, nouvel_obj); /*on place le nouvel objet dans le tableau à la place indiquée*/
	
	do { /* structure do while car on veut faire les instructions au moins une fois */
		action = choix_action(tab, hauteur, largeur, *val_max, nb_chiffres); /* on demande au joueur ce qu'il veut faire */
		if('q' == action) { /* s'il veut quitter, on quitte le jeu */
			*quitter = 1;
			return;
		}
		/* sinon, on effectue l'action qu'il a demandée et on récupère la valeur renvoyée */
		succes = execute_action(tab, hauteur, largeur, val_max, cases_vides, *n_tour, action);
		
	}
	while ((succes == 0) && (*cases_vides > 0)); /* et on recommence tant que les actions n'étaient pas possibles et qu'il reste des actions possibles */
	
}

