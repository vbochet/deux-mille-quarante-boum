#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*pour la comparaison des chaînes de caractères*/
#include <time.h> /*pour l'aléatoire*/
#include <math.h>

#include "jeu_init.h"
#include "utils.h"
#include "jeu.h"
#include "jeu_fin.h"
#include "tableau.h"
#include "struct.h"


int main()
{
    int param_borne, param_hauteur, param_largeur; /* paramètres du jeu */
    int confirm; /* variable qui contient 0 en cas de confirmation d'une action, autre chose sinon */
    obj ** tableau; /* tableau à deux dimensions contenant les éléments du tableau */
    int h,l; /* variables de boucle for portant sur la hauteur et la largeur du tableau */
    int nb_cases_vides;
	int valeur_max; /* valeur maximale contenue dans le tableau, pour gérer la largeur des colonnes à l'affichage */
	int n_tour; /* variable contenant le nombre de tours joués, utile pour les stats de fin de partie */
	int horaire_debut, horaire_fin; /* stocke les temps de début et de fin de la partie pour calculer la durée totale */
	int partie_en_cours;  /* booléen valant 1 si la partie est toujours en cours, et 0 si elle est terminée */
	int resultat; /* vaut 1 si le joueur a gagné, 2 si le joueur a perdu, 0 par défaut (tant que la partie n'est pas finie */
	int quitter; /* variable valant 1 si le joueur décide de quitter la partie, 0 sinon */

    srand(time(NULL)); /*on initialise l'aléatoire*/

    /*on demande au joueur d'entrer les paramètres du jeu*/
    parametres(&param_borne, &param_hauteur, & param_largeur);

    /*on demande confirmation au joueur pour les paramètres*/
    confirm=confirmation();

    /* la boucle se termine lorsque le joueur a validé ses choix */
    while (confirm!=0) {
        parametres(&param_borne, &param_hauteur, &param_largeur);
        confirm=confirmation();
    }

    system("clear"); /* efface l'écran avant de commencer le jeu */

    /* on génère un tableau vide des dimensions choisies par le joueur */
    tableau=(obj **)calloc(param_hauteur,sizeof(obj*));
	
    for(h=0 ; h<param_hauteur ; h=h+1) {
        tableau[h]=(obj *)calloc(param_largeur,sizeof(obj));
		
        for(l=0; l<param_largeur; l=l+1) { /*on en profite pour affecter à 0 (<=> vide) toutes les cases du tableau*/
            tableau[h][l].valeur=0;
			/* pas besoin de s'occuper de la position et de la fusion) puisque l'on ne s'en servira pas (ces cases sont vides) */
        }
    }
	
    /* avant de lancer le premier tour, on assigne des valeurs de base aux variables */
    nb_cases_vides = param_hauteur * param_largeur;
    valeur_max = 1;
	n_tour = 0;
	partie_en_cours = 1;
	horaire_debut = time(NULL);
	quitter = 0;

	/* tours de jeu */
	while(partie_en_cours == 1) {
		/* à chaque tour, on effectue un tour de jeu */
		tour(tableau, param_hauteur, param_largeur, &valeur_max, &nb_cases_vides, &n_tour, &quitter);
		
		/* puis on vérifie si le joueur a quitté la partie */
		if(quitter == 1) {
			liberer_tableau(tableau, param_hauteur); /* on libère la mémoire allouée au tableau */
			return 0; /* et on termine le programme */
		}
		
		/* enfin, on vérifie si le joueur a gagné, ou perdu. Si c'est le cas, on met fin à la boucle (partie_en_cours = 0), 
		   et on affecte la variable resultat à 1 ou 2 selon le cas.*/
		if(valeur_max >= param_borne) { /* gagné */
			partie_en_cours = 0;
			resultat = 1;
		}
		else if(nb_cases_vides <= 0) { /* perdu */
			partie_en_cours = 0;
			resultat = 2;
		}
	}
	
	horaire_fin=time(NULL); /* on calcule l'horaire de fin de la partie */
	
	system("clear");
	print_tableau(tableau, param_hauteur, param_largeur, valeur_max);
	fin_partie(resultat, n_tour, nb_cases_vides, horaire_fin-horaire_debut); /* on affiche les statistiques de la partie */
	
    /* Pour finir, on libère la mémoire */
    liberer_tableau(tableau, param_hauteur);
    return 0;
}

