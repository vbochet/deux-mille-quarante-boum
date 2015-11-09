#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*pour la comparaison des chaînes de caractères*/
#include <time.h> /*pour l'aléatoire*/
#include <math.h>

/* @requires
   @assigns
   @ensures renvoie 0 si l'utilisateur a validé (en entrant 'y' ou 'Y'), et renvoie 1 sinon
   @*/
int confirmation()/*fonction de demande de confirmation*/
{
    char c;
    char buffer[2]; /* 2 car 1 caractère PLUS le \0 des chaînes */
    int comp1, comp2; /*contiendront le résultat de la comparaison avec "y" et "Y"*/
    int retour; /*valeur de retour de la fonction*/

    printf("Valider ? (y/n)"); /*on affiche un message pour demander validation*/
    scanf("%1s", buffer);
    c=buffer[0];

    comp1=strcmp(c+"", 'y'+""); /*on ajoute la chaine vide à chaque caractère pour caster en string pour la fonction strcmp et pour garder l'égalité des deux*/
    comp2=strcmp(c+"", 'Y'+""); /*idem*/

    if (comp1==0 || comp2==0) retour = 0;
    else retour = 1;

    return retour;
};


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
    int confirm; /*variable qui contient 0 en cas de confirmation d'une action, autre chose sinon*/

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

    printf("Hello world!\n");
    return 0;
}
