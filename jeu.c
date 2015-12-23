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
	int alea; /* nombre aléatoire généré */

    if(valeur_max < 64) {
		valeur = 1;
	}
    else if(valeur_max < 256) { /* 70% de chances d'avoir un 1, 20% d'avoir un 2, 10% d'avoir un + */
		alea = alea_bornes(0,100);
		
		if(alea < 70) { /* 70% de chances d'avoir un 1 */
			valeur = 1;
		}
		else if(alea < 90) { /* 90-70=20% de chances d'avoir un 2 */
			valeur = 2;
		}
		else { /* 100-90=10% de chances d'avoir un + */
			valeur = -1;
		}
	}
    else { /* 60% de chances d'avoir un 1, 25% d'avoir un 2, 10% d'avoir un + et 5% d'avoir un x */
		alea = alea_bornes(0,100);
		
		if(alea < 60) { /* 60% de chances d'avoir un 1 */
			valeur = 1;
		}
		else if(alea < 85) { /* 85-60=25% de chances d'avoir un 2 */
			valeur = 2;
		}
		else if(alea < 95) { /* 95-85=10% de chances d'avoir un + */
			valeur = -1;
		}
		else { /* 100-95=5% de chances d'avoir un x */
			valeur = -11;
		}
	}

    nouv_objet.position = alea_bornes(0,cases_vides); /* numéro de la case vide où placer ce nouvel objet */
    nouv_objet.fusion = 0; /* l'objet ne résulte pas d'une fusion, donc fusion=0 qui est inférieur au n° du tour */
    nouv_objet.valeur = valeur;

    return nouv_objet;
}


/* @requires hauteur>1, largeur>1, nb_chiffres>0
   @assigns coordonnees
   @ensures à la fin, le joueur a effectué un choix de mouvement valide
   @*/
char choix_action(obj** tab, int hauteur, int largeur, int val_max, int nb_chiffres, int* coordh, int* coordl) /* fonction de demande de choix au joueur */
{
	int faire_boucle, n; /* variables de boucle */
	char action; /* choix d'action du joueur (i, j, k, l, b, q, h) */
	char buffer[2]; /* 2 car 1 caractère PLUS le \0 des chaînes */
	
	faire_boucle = 1;
	
	while(faire_boucle > 0) /* se terminera lorsque le joueur aura effectué un choix correct et qu'il l'aura validé */
	{
		system("clear");
		
		if(faire_boucle == 2) { /* on affiche un message d'avertissement car le joueur s'est trompé en indiquant les coordonnées de la bombe lors de son choix*/
			printf("Vous n'avez pas choisi une bombe ! Veuillez recommencer.\n\n");
		}
		
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
			
			case 'b':
				printf("Vous avez choisi de faire exploser une bombe. Quelles sont ses coordonnées ? \n");
				printf("Hauteur : ");
				scanf("%d", coordh); /* on récupère la hauteur de la bombe */
				*coordh = hauteur - (*coordh); /* pour le joueur, l'origine du tableau est en bas à gauche. Pour le code, l'origine est en haut à gauche. On doit donc "renverser" la valeur de la hauteur pour que cela corresponde. */
				printf("Largeur : ");
				scanf("%d", coordl); /* on récupère la largeur de la bombe */
				
				/* on vérifie que c'est une bombe */
				if(tab[*coordh][*coordl]).valeur < 0) { /* si oui, on peut demander confirmation au joueur */
					system("clear");
					affich_choix_bombe(tab, hauteur, largeur, val_max, *coordh, *coordl);
					printf("Voici la bombe à faire exploser. \n");
					faire_boucle=confirmation();
				}
				else { /* sinon, on lui repose la question de ce qu'il veut faire */
					faire_boucle = 2;
				}
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
				printf("- b => faire exploser une bombe\n       rappel : coordonnées de la case en bas à gauche = (0,0)\n");
				printf("       bombe + => supprime les valeurs latérales\n       bombe x => supprime les valeurs diagonales\n");
				printf("       bombe * => supprime toutes les valeurs attenantes\n");
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
void execute_action(obj** tab, int hauteur, int largeur, int* val_max, int* cases_vides, int nb_tour, char action, coord coordonnees) /* effectue l'action choisie */
{
	int h,l; /*variables de boucles correspondant aux lignes et aux colonnes*/
	int m,n; /*idem*/
	
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
							}
							else if((tab[m-1][l].valeur == tab[m][l].valeur) && (tab[m-1][l].fusion < nb_tour)) { /* si la case située au dessus a la même valeur que la case en cours de traitement, et que la case au dessus ne résulte pas d'une fusion à ce tour, on les "fusionne" */
								tab[m-1][l].valeur = tab[m-1][l].valeur + tab[m][l].valeur;
								tab[m-1][l].fusion = nb_tour;
								tab[m][l].valeur = 0;
								*cases_vides = *cases_vides + 1; /* on a vidé une case du tableau */
								
								if(*val_max < tab[m-1][l].valeur) { /* si la valeur maximale du tableau est celle que l'on vient de créer, on met à jour la valeur de la variable correspondante */
									*val_max = tab[m-1][l].valeur;
								}
								m = 0; /* on sort de la boucle dès lors qu'on a fait une somme avec une autre case. en effet, si on ne s'arrête pas, on risque de sommer des cases qui viennent d'être crées pendant le tour */
							}
							else if((tab[m-1][l].valeur < 0) && (tab[m][l].valeur < 0) && (tab[m-1][l].fusion < nb_tour)) { /* si la case située au dessus et la case en cours de traitement sont des bombes, et que la case au dessus ne résulte pas d'une fusion à ce tour, on procède à des tests spécifiques */
								if((tab[m-1][l].valeur <= -21) && (tab[m][l].valeur <= -21)) { /* on a deux bombes *, on les fusionne => explosion de celle sur la case d'arrivée */
									tab[m][l].valeur = 0; /* on vide la case en cours de traitement */
									explosion(tab, hauteur, largeur, m-1, l); /* on fait exploser la bombe de la case d'arrivée */
								}
								else if((tab[m-1][l].valeur <= -11) && (tab[m][l].valeur <= -11)) { /* on a deux bombes x, on les fusionne => on a une bombe * sur la case d'arrivée */
									tab[m][l].valeur = 0; /* on vide la case en cours de traitement */
									tab[m-1][l].valeur = -21; /* on obtient une bombe * sur la case d'arrivée */
								}
								else if((tab[m-1][l].valeur <= -1) && (tab[m][l].valeur <= -1)) { /* on a deux bombes +, on les fusionne => on a une bombe x sur la case d'arrivée */
									tab[m][l].valeur = 0; /* on vide la case en cours de traitement */
									tab[m-1][l].valeur = -11; /* on obtient une bombe x sur la case d'arrivée */
								}
								
								*cases_vides = *cases_vides + 1; /* on a vidé une case du tableau */
								
								m = 0; /* on sort de la boucle dès lors qu'on a fait une somme avec une autre case. en effet, si on ne s'arrête pas, on risque de sommer des cases qui viennent d'être crées pendant le tour */
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
							}
							else if((tab[h][n-1].valeur < 0) && (tab[h][n].valeur < 0) && (tab[h][n-1].fusion < nb_tour)) { /* si la case située à gauche et la case en cours de traitement sont des bombes, et que la case à gauche ne résulte pas d'une fusion à ce tour, on procède à des tests spécifiques */
								if((tab[h][n-1].valeur <= -21) && (tab[h][n].valeur <= -21)) { /* on a deux bombes *, on les fusionne => explosion de celle sur la case d'arrivée */
									tab[h][n].valeur = 0; /* on vide la case en cours de traitement */
									explosion(tab, hauteur, largeur, h, n-1); /* on fait exploser la bombe de la case d'arrivée */
								}
								else if((tab[h][n-1].valeur <= -11) && (tab[h][n].valeur <= -11)) { /* on a deux bombes x, on les fusionne => on a une bombe * sur la case d'arrivée */
									tab[h][n].valeur = 0; /* on vide la case en cours de traitement */
									tab[h][n-1].valeur = -21; /* on obtient une bombe * sur la case d'arrivée */
								}
								else if((tab[h][n-1].valeur <= -1) && (tab[h][n].valeur <= -1)) { /* on a deux bombes +, on les fusionne => on a une bombe x sur la case d'arrivée */
									tab[h][n].valeur = 0; /* on vide la case en cours de traitement */
									tab[h][n-1].valeur = -11; /* on obtient une bombe x sur la case d'arrivée */
								}
								
								*cases_vides = *cases_vides + 1; /* on a vidé une case du tableau */
								
								n = 0; /* on sort de la boucle dès lors qu'on a fait une somme avec une autre case. en effet, si on ne s'arrête pas, on risque de sommer des cases qui viennent d'être crées pendant le tour */
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
							}
							else if((tab[m+1][l].valeur < 0) && (tab[m][l].valeur < 0) && (tab[m+1][l].fusion < nb_tour)) { /* si la case située en dessous et la case en cours de traitement sont des bombes, et que la case en dessous ne résulte pas d'une fusion à ce tour, on procède à des tests spécifiques */
								if((tab[m+1][l].valeur <= -21) && (tab[m][l].valeur <= -21)) { /* on a deux bombes *, on les fusionne => explosion de celle sur la case d'arrivée */
									tab[m][l].valeur = 0; /* on vide la case en cours de traitement */
									explosion(tab, hauteur, largeur, m+1, l); /* on fait exploser la bombe de la case d'arrivée */
								}
								else if((tab[m+1][l].valeur <= -11) && (tab[m][l].valeur <= -11)) { /* on a deux bombes x, on les fusionne => on a une bombe * sur la case d'arrivée */
									tab[m][l].valeur = 0; /* on vide la case en cours de traitement */
									tab[m+1][l].valeur = -21; /* on obtient une bombe * sur la case d'arrivée */
								}
								else if((tab[m+1][l].valeur <= -1) && (tab[m][l].valeur <= -1)) { /* on a deux bombes +, on les fusionne => on a une bombe x sur la case d'arrivée */
									tab[m][l].valeur = 0; /* on vide la case en cours de traitement */
									tab[m+1][l].valeur = -11; /* on obtient une bombe x sur la case d'arrivée */
								}
								
								*cases_vides = *cases_vides + 1; /* on a vidé une case du tableau */
								
								m = hauteur; /* on sort de la boucle dès lors qu'on a fait une somme avec une autre case. en effet, si on ne s'arrête pas, on risque de sommer des cases qui viennent d'être crées pendant le tour */
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
							}
							else if((tab[h][n+1].valeur < 0) && (tab[h][n].valeur < 0) && (tab[h][n+1].fusion < nb_tour)) { /* si la case située à gauche et la case en cours de traitement sont des bombes, et que la case à gauche ne résulte pas d'une fusion à ce tour, on procède à des tests spécifiques */
								if((tab[h][n+1].valeur <= -21) && (tab[h][n].valeur <= -21)) { /* on a deux bombes *, on les fusionne => explosion de celle sur la case d'arrivée */
									tab[h][n].valeur = 0; /* on vide la case en cours de traitement */
									explosion(tab, hauteur, largeur, h, n+1); /* on fait exploser la bombe de la case d'arrivée */
								}
								else if((tab[h][n+1].valeur <= -11) && (tab[h][n].valeur <= -11)) { /* on a deux bombes x, on les fusionne => on a une bombe * sur la case d'arrivée */
									tab[h][n].valeur = 0; /* on vide la case en cours de traitement */
									tab[h][n+1].valeur = -21; /* on obtient une bombe * sur la case d'arrivée */
								}
								else if((tab[h][n+1].valeur <= -1) && (tab[h][n].valeur <= -1)) { /* on a deux bombes +, on les fusionne => on a une bombe x sur la case d'arrivée */
									tab[h][n].valeur = 0; /* on vide la case en cours de traitement */
									tab[h][n+1].valeur = -11; /* on obtient une bombe x sur la case d'arrivée */
								}
								
								*cases_vides = *cases_vides + 1; /* on a vidé une case du tableau */
								
								n = largeur; /* on sort de la boucle dès lors qu'on a fait une somme avec une autre case. en effet, si on ne s'arrête pas, on risque de sommer des cases qui viennent d'être crées pendant le tour */
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
		
		case 'b': /* explosion d'une bombe (vérifiée auparavant dans la fonction choix_action */
			explosion(tab, hauteur, largeur, coordonnees.h, coordonnees.l);
		break;
	}
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
	int coordh, coordl; /* les coordonnées lorsqu'on voudra faire exploser une bombe */
	
	nb_chiffres = max(3, log10(*val_max)+1);
	*n_tour = *n_tour+1;
	
	/* avant de commencer le tour en ajoutant un nouvel objet, on incrémente le nombre de tours de chaque bombe, on vérifie si des bombes doivent exploser spontanément, et on réalise les explosions le cas échéant */
	check_bombes(tab, hauteur, largeur);
	
	/* on peut ensuite reprendre le déroulement classique d'un tour de jeu */
    nouvel_obj = nouvel_objet(*cases_vides, *val_max); /*on génère le nouvel objet à ajouter à notre tableau de jeu*/
	
    remplir_tableau(tab, hauteur, largeur, cases_vides, nouvel_obj); /*on place le nouvel objet dans le tableau à la place indiquée*/
	
	action = choix_action(tab, hauteur, largeur, *val_max, nb_chiffres, &coordh, &coordl);
	if('q' == action) {
		*quitter = 1;
		return;
	}
	execute_action(tab, hauteur, largeur, val_max, cases_vides, *n_tour, action, coordh, coordl);
}

