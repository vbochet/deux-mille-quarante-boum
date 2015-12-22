/* FONCTIONS POUR LA CONCLUSION DU JEU*/


#include <stdio.h>


/* @requires
   @assigns
   @ensures affiche les résultats de la partie
   @*/
void fin_partie(int resultat, int n_tours, int cases_vides, int duree) /* affiche le résultat et des statistiques pour la partie achevée */
{
	if(resultat == 1) { /* le joueur a gagné la partie */
		printf("Vous avez gagné la partie !!!\n");
	}
	else if(resultat == 2) { /* le joueur a perdu la partie */
		printf("Il ne reste plus de case vide.\n");
		printf("Vous avez perdu la partie. :(\n");
	}

	/* statistiques diverses */
	printf("_____________________________\n\n");
	printf("Statistiques de la partie :\n");
	printf("Nombre de tours = %i\n", n_tours);
	printf("Nombre de cases vides restantes = %i\n", cases_vides);
	printf("La partie a duré %i secondes\n\n\n", duree);
}

