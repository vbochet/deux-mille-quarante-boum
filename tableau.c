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
    int h, l, cpt;
    h=0; cpt=0;

    while(h<hauteur) /*s'arrête car on incrémente de 1 le compteur à chaque fois*/
    {
        l=0;
        while(l<largeur) /*s'arrête pour les mêmes raisons que la boucle précédente*/
        {
            if((tableau[h][l]).valeur==0) /*si la case vaut 0, alors c'est une case vide*/
            {
                if(nouv_objet.position==cpt) /*si c'est la position pour le nouvel objet, on l'y place et on termine la boucle*/
                {
                    tableau[h][l]=nouv_objet;
                    h=hauteur; /*on met fin à la boucle sur h*/
                    l=largeur; /*on met fin à la boucle sur l*/
					*cases_vides = *cases_vides - 1; 
                }
                else
                {
                    l=l+1; /*on incrémente le compteur de boucle*/
                    cpt=cpt+1; /*on incrémente le compteur de cases vides*/
                }
            }
            else
            {
                l=l+1;
            }
        }
        h=h+1;
    }
}


/* @requires hauteur>1, largeur>1
   @assigns
   @ensures affiche le tableau
   @*/
void print_tableau(obj** tab, int hauteur, int largeur, int val_max)
{
  int h, l;
  int n;
  int nb_chiffres; /*nombre de chiffres de la valeur maximale du tableau, pour gérer un affichage correct*/
  
  nb_chiffres=max(3, log10(val_max)+1);
  
  for(h=0; h<hauteur; h=h+1) /*boucle sur les lignes*/
  {
    /*affichage de la barre horizontale en haut de la ligne en cours*/
    printf("-");
	for(n=1; n<=largeur*(nb_chiffres+1); n=n+1)
	{
		printf("-");
    }
    printf("\n");
    
    /*affichage d'une première ligne "vide" car chaque ligne est affichée sur 3 lignes de texte*/
    for(l=0; l<largeur; l=l+1)
    {
      printf("|%*s", nb_chiffres, "");
    }
    printf("|\n");
    
    /*affichage des lignes comportant du contenu*/
    for(l=0; l<largeur; l=l+1)
    {
      if((tab[h][l]).valeur!=0)
      {
		printf("|%*i", nb_chiffres, (tab[h][l]).valeur);
      }
      else
      {
		printf("|%*s", nb_chiffres, "");
      }
    }
    printf("|\n");
    
    /*affichage de la troisième ligne "vide"*/
    for(l=0; l<largeur; l=l+1)
    {
      printf("|%*s", nb_chiffres, "");
    }
    printf("|\n");
  }
  
  /*affichage de la barre horizontale fermant le tableau*/
    printf("-");
	for(n=1; n<=largeur*(nb_chiffres+1); n=n+1)
	{
		printf("-");
    }
    printf("\n");
	printf("\n");
}