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
    int param_borne, param_hauteur, param_largeur; /*paramètres du jeu*/
    int confirm; /*variable qui contient 0 en cas de confirmation d'une action, autre chose sinon*/
    obj ** tableau; /*tableau à deux dimensions contenant les valeurs du tableau*/
    int h,l; /*variables de boucle for portant sur la hauteur et la largeur du tableau*/
    int nb_cases_vides, valeur_max;
	int n_tour; /*variable contenant le nombre de tours joués, utile pour les stats de fin de partie*/
	int horaire_debut, horaire_fin;
	int partie_en_cours; 
	int resultat;
	int quitter; /*variable valant 1 si le joueur décide de quitter la partie, 0 sinon*/

    srand(time(NULL)); /*on initialise l'aléatoire*/

    /*on demande au joueur d'entrer les paramètres du jeu*/
    parametres(&param_borne, &param_hauteur, & param_largeur);

    /*on demande confirmation au joueur pour les paramètres*/
    confirm=confirmation();

    /*la boucle se termine lorsque le joueur a validé ses choix*/
    while (confirm!=0)
    {
        parametres(&param_borne, &param_hauteur, &param_largeur);
        confirm=confirmation();
    }

    system("clear"); /*efface l'écran avant de commencer le jeu*/

    /*on génère un tableau vide des dimensions choisies par le joueur*/
    tableau=(obj **)calloc(param_hauteur,sizeof(obj*));
    for(h=0 ; h<param_hauteur ; h=h+1)
    {
        tableau[h]=(obj *)calloc(param_largeur,sizeof(obj));
        for(l=0; l<param_largeur; l=l+1) /*on en profite pour affecter à 0 (<=> vide) toutes les cases du tableau*/
        {
            tableau[h][l].valeur=0;
			/* pas besoin de s'occuper des autres valeurs (position et fusion) puisque l'on ne s'en servira pas (ces cases sont vides) */
        }
    }
	
    /*avant de lancer le premier tour, on assigne des valeurs de base aux variables*/
    nb_cases_vides=param_hauteur*param_largeur;
    valeur_max=1;
	n_tour=0;
	partie_en_cours=1;
	horaire_debut=time(NULL);
	quitter=0;

	/*tours de jeu*/
	while(partie_en_cours==1)
	{
		tour(tableau, param_hauteur, param_largeur, &valeur_max, &nb_cases_vides, &n_tour, &quitter);
		
		if(quitter==1){ /*si l'utilisateur a décidé de quitter la partie, */
			free(tableau); /* on libère la mémoire allouée au tableau */
			return 0; /* et on termine le programme */
		}
		if(valeur_max>=param_borne) {
			partie_en_cours=0;
			resultat = 1;
		}
		if(nb_cases_vides <= 0){
			partie_en_cours=0;
			resultat = 2;
		}
	}
	horaire_fin=time(NULL);
	
	system("clear");
	print_tableau(tableau, param_hauteur, param_largeur, valeur_max);
	fin_partie(resultat, n_tour, nb_cases_vides, horaire_fin-horaire_debut);
	
    /*à la fin du jeu, on libère la mémoire*/
    free(tableau);
    return 0;
}
