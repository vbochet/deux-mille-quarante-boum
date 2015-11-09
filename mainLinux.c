#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*pour la comparaison des chaînes de caractères*/
#include <time.h> /*pour l'aléatoire*/
#include <math.h>

/* @requires
   @assigns les variables borne, hauteur et largeur pointées par les arguments
   @ensures les variables pointées contiennent des valeurs valides pour le jeu (borne supérieure à 1, tableau de dimensions minimales 2x2)
   @*/
void parametres(int *borne, int *hauteur, int *largeur) /*fonction de demande des paramètres à l'utilisateur*/
{
    system("clear"); /*on efface l'écran avant de commencer*/
    printf("Avant de commencer à jouer, veuillez renseigner quelques paramètres.\n");

    /*borne max à dépasser dans le jeu*/
    printf("Valeur à atteindre : "); /*on affiche une fois la demande*/
    scanf("%i", borne);
    printf("\n");
    /*si la valeur n'est pas correcte, on entre dans une boucle affichant un message d'erreur et redemandant la valeur*/
    while(*borne<=1) /*la boucle se termine lorsque le joueur rentre une valeur correcte*/
    {
        printf("La valeur doit être un nombre supérieur à 1 ! \nValeur à atteindre : ");
        scanf("%i", borne);
        printf("\n");
    }

    /*hauteur du tableau*/
    printf("Hauteur du tableau : "); /*on affiche une fois la demande*/
    scanf("%i", hauteur);
    printf("\n");
    /*si la valeur n'est pas correcte, on entre dans une boucle affichant un message d'erreur et redemandant la valeur*/
    while(*hauteur<=1) /*la boucle se termine lorsque le joueur rentre une valeur correcte*/
    {
        printf("La hauteur est forcément supérieure à 1 ! \nHauteur du tableau : ");
        scanf("%i", hauteur);
        printf("\n");
    }

    /*largeur du tableau*/
    printf("Largeur du tableau : "); /*on affiche une fois la demande*/
    scanf("%i", largeur);
    printf("\n");
    /*si la valeur n'est pas correcte, on entre dans une boucle affichant un message d'erreur et redemandant la valeur*/
    while(*largeur<=1) /*la boucle se termine lorsque le joueur rentre une valeur correcte*/
    {
        printf("La largeur est forcément supérieure à 1 ! \nLargeur du tableau : ");
        scanf("%i", largeur);
        printf("\n");
    }

    /*on affiche un récapitulatif des choix du joueur*/
    printf("Vous avez indiqué vouloir atteindre le nombre %i avec un tableau de %ix%i cases.\n", *borne, *hauteur, *largeur);
}



int main()
{
    int param_borne, param_hauteur, param_largeur; /*paramètres du jeu*/
	
    /*on demande au joueur d'entrer les paramètres du jeu*/
    parametres(&param_borne, &param_hauteur, & param_largeur);
	
    return 0;
}
