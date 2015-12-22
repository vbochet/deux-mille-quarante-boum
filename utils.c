/* FONCTIONS ANNEXES, SERVANT POUR LES FONCTIONS PRINCIPALES... */


#include <stdio.h>
#include <stdlib.h> /*pour l'aléatoire*/
#include <time.h> /*pour l'aléatoire*/
#include <string.h> /*pour la comparaison des chaînes de caractères*/


/* @requires
   @assigns
   @ensures renvoie 0 si l'utilisateur a validé (en entrant 'y' ou 'Y'), et renvoie 1 sinon
   @*/
int confirmation() /*fonction de demande de confirmation*/
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


/* @requires a<b
   @assigns
   @ensures renvoie un entier aléatoire compris entre a inclus et b exclus
   @*/
int alea_bornes(int a, int b) /* ATTENTION : IL N'Y A PAS PROBABILITÉ UNIFORME. POUR CORRIGER CELA, CF. LES NOTES PRISES EN TP D'IPI ! */
{
    return rand()%(b-a) +a;
}


/* @requires 
   @assigns
   @ensures renvoie le maximum de a et b
   @*/
int max(int a, int b)
{
  if(a>b){
    return a;
  }
  return b;
}

