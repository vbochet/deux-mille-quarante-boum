/* FONCTIONS POUR L'INITIALISATION DU JEU */


#include <stdio.h>
#include <stdlib.h>


/* @requires
   @assigns borne, hauteur, largeur
   @ensures à la fin, les variables contiennent des valeurs valides pour le jeu (borne supérieure à 1, tableau de dimensions minimales 2x2)
   @*/
void parametres(int *borne, int *hauteur, int *largeur) /*fonction de demande des paramètres à l'utilisateur*/
{
    system("clear"); /* on efface l'écran avant de commencer */
    printf("Avant de commencer à jouer, veuillez renseigner quelques paramètres.\n");

    /* borne max à dépasser dans le jeu */
    printf("Valeur à atteindre : "); /* on affiche une fois la demande */
    scanf("%i", borne);
	
    /* si la valeur n'est pas correcte, on entre dans une boucle affichant un message d'erreur et redemandant la valeur */
    while(*borne <= 1) { /* la boucle se termine lorsque le joueur rentre une valeur correcte */
        printf("La valeur doit être un nombre supérieur à 1 ! \nValeur à atteindre : ");
        scanf("%i", borne);
    }

    /* hauteur du tableau */
    printf("Hauteur du tableau : "); /* on affiche une fois la demande */
    scanf("%i", hauteur);
	
    /* si la valeur n'est pas correcte, on entre dans une boucle affichant un message d'erreur et redemandant la valeur */
    while(*hauteur <= 1) { /* la boucle se termine lorsque le joueur rentre une valeur correcte */
        printf("La hauteur est forcément supérieure à 1 ! \nHauteur du tableau : ");
        scanf("%i", hauteur);
    }

    /* largeur du tableau */
    printf("Largeur du tableau : "); /* on affiche une fois la demande */
    scanf("%i", largeur);
	
    /* si la valeur n'est pas correcte, on entre dans une boucle affichant un message d'erreur et redemandant la valeur */
    while(*largeur <= 1) { /* la boucle se termine lorsque le joueur rentre une valeur correcte */
        printf("La largeur est forcément supérieure à 1 ! \nLargeur du tableau : ");
        scanf("%i", largeur);
    }

    /* on affiche un récapitulatif des choix du joueur */
    printf("Vous avez indiqué vouloir atteindre le nombre %i avec un tableau de %ix%i cases.\n", *borne, *hauteur, *largeur);
}

