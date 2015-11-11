#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*pour la comparaison des chaînes de caractères*/
#include <time.h> /*pour l'aléatoire*/
#include <math.h>

struct sobj{
    int position; /*position dans le tableau*/
    int type; /*1 pour nombre, 2 pour bombe*/
    int valeur; /*valeur normale si nombre, valeur négative si bombe +,x,*.*/
};
typedef struct sobj obj;

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
	
    /*si la valeur n'est pas correcte, on entre dans une boucle affichant un message d'erreur et redemandant la valeur*/
    while(*borne<=1) /*la boucle se termine lorsque le joueur rentre une valeur correcte*/
    {
        printf("La valeur doit être un nombre supérieur à 1 ! \nValeur à atteindre : ");
        scanf("%i", borne);
    }

    /*hauteur du tableau*/
    printf("Hauteur du tableau : "); /*on affiche une fois la demande*/
    scanf("%i", hauteur);
	
    /*si la valeur n'est pas correcte, on entre dans une boucle affichant un message d'erreur et redemandant la valeur*/
    while(*hauteur<=1) /*la boucle se termine lorsque le joueur rentre une valeur correcte*/
    {
        printf("La hauteur est forcément supérieure à 1 ! \nHauteur du tableau : ");
        scanf("%i", hauteur);
    }

    /*largeur du tableau*/
    printf("Largeur du tableau : "); /*on affiche une fois la demande*/
    scanf("%i", largeur);
	
    /*si la valeur n'est pas correcte, on entre dans une boucle affichant un message d'erreur et redemandant la valeur*/
    while(*largeur<=1) /*la boucle se termine lorsque le joueur rentre une valeur correcte*/
    {
        printf("La largeur est forcément supérieure à 1 ! \nLargeur du tableau : ");
        scanf("%i", largeur);
    }

    /*on affiche un récapitulatif des choix du joueur*/
    printf("Vous avez indiqué vouloir atteindre le nombre %i avec un tableau de %ix%i cases.\n", *borne, *hauteur, *largeur);
}


/* @requires a<b
   @assigns
   @ensures renvoie un entier aléatoire compris entre a inclus et b exclus
   @*/
int alea_bornes(int a, int b)
{
    return rand()%(b-a) +a;
}


/* @requires
   @assigns
   @ensures renvoie un objet à ajouter dans le tableau
   @*/
obj nouvel_objet(int cases_vides, int valeur_max)
{
    obj nouv_objet;
    int valeur;

    if(valeur_max<64) {valeur=1;}
    else if(valeur_max<256) {valeur=(alea_bornes(0,10)>6)+1;}
    else {valeur=(alea_bornes(0,10)>5)+1;}

    nouv_objet.position=alea_bornes(0,cases_vides); /*numéro de la case vide où placer ce nouvel objet*/
    nouv_objet.type=1;
    nouv_objet.valeur=valeur;

    return nouv_objet;
}


/* @requires
   @assigns
   @ensures renvoie la position de l'objet à ajouter dans le tableau
   @*/
void remplir_tableau(int** tableau, int hauteur, int largeur, obj nouv_objet)
{
    int h, l, cpt;
    h=0; cpt=0;

    while(h<hauteur) /*s'arrête car on incrémente de 1 le compteur à chaque fois*/
    {
        l=0;
        while(l<largeur) /*s'arrête pour les mêmes raisons que la boucle précédente*/
        {
            if(tableau[h][l]==0) /*si la case vaut 0, alors c'est une case vide*/
            {
                if(nouv_objet.position==cpt)
                {
                    tableau[h][l]=nouv_objet.valeur;
                    h=hauteur; /*on met fin à la boucle sur h*/
                    l=largeur; /*on met fin à la boucle sur l*/
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


/* @requires hauteur>1, largeur>1
   @assigns
   @ensures
   @*/
void print_tableau(int** tab, int hauteur, int largeur, int val_max)
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
      if(tab[h][l]!=0)
      {
	printf("|%*i", nb_chiffres, tab[h][l]);
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
};


/* @requires hauteur>1, largeur>1, nb_chiffres>0
   @assigns 
   @ensures à la fin, le joueur a effectué un choix de mouvement valide
   @*/
   
char choix_action(int** tab, int hauteur, int largeur, int val_max, int nb_chiffres)
{
	int faire_boucle,n;
	char action;
	char buffer[2]; /* 2 car 1 caractère PLUS le \0 des chaînes */
	
	faire_boucle = 1;
	
	while(faire_boucle==1) /*se terminera lorsque le joueur aura effectué un choix correct et qu'il l'aura validé*/
	{
		system("clear");
		print_tableau(tab, hauteur, largeur, val_max); /*on affiche le tableau*/

		printf("Que faire ?");
	
		/*affichage d'espaces pour situer l'invite à droite du tableau*/
		printf(" ");
		for(n=1; n<=(largeur*(nb_chiffres+1))-12; n=n+1) /*12 pour nombre de caractères de la question + 1*/
		{
			printf(" ");
		}
		scanf("%1s", buffer);
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
			
			default:
				printf("erreur\n");
		}
	}
	
	return action;
}


/* @requires hauteur>1, largeur>1, action in {i,j,k,l}
   @assigns tab, val_max
   @ensures à la fin, on a effectué tous les déplacements du tour
   @*/
   
void execute_action(int** tab, int hauteur, int largeur, int* val_max, char action)
{
	int h,l; /*variables de boucles correspondant aux lignes et aux colonnes*/
	
	switch(action) {
		case 'i': /*déplacement vers le haut*/
			for(h=1; h<hauteur; h=h+1) /*on parcourt toutes les lignes sauf la première (sur laquelle on ne peut pas faire de déplacement*/
			{
				for(l=0; l<largeur; l=l+1) /*on parcourt toutes les cases de la ligne en cours*/
				{
					if(tab[h][l]!=0) /*si la case n'est pas vide, on agit*/
					{
						if(tab[h-1][l]==0) /*si la case située au dessus est vide, on peut y déplacer l'élément actuellement en cours de traitement*/
						{
							tab[h-1][l]=tab[h][l];
							tab[h][l]=0;
						}
						else if(tab[h-1][l]==tab[h][l]) /*si la case située au dessus a la même valeur que la case en cours de traitement, on les "fusionne"*/
						{
							tab[h-1][l]=tab[h-1][l]+tab[h][l];
							tab[h][l]=0;
							
							if(*val_max<tab[h-1][l]) /*si la valeur maximale du tableau est celle que l'on vient de créer, on met à jour la valeur de la variable correspondante*/
							{
								*val_max=tab[h-1][l];
							}
						}
					}
					
					system("clear");
					print_tableau(tab, hauteur, largeur, *val_max);
				}
			}
			
		break;
		
		case 'j': /*déplacement vers la gauche*/
			for(l=1; l<largeur; l=l+1)
			{
				for(h=0; h<hauteur; h=h+1)
				{
					if(tab[h][l]!=0) /*si la case n'est pas vide, on agit*/
					{
						if(tab[h][l-1]==0) /*si la case située à gauche est vide, on peut y déplacer l'élément actuellement en cours de traitement*/
						{
							tab[h][l-1]=tab[h][l];
							tab[h][l]=0;
						}
						else if(tab[h][l-1]==tab[h][l]) /*si la case située à gauche a la même valeur que la case en cours de traitement, on les "fusionne"*/
						{
							tab[h][l-1]=tab[h][l-1]+tab[h][l];
							tab[h][l]=0;
							
							if(*val_max<tab[h][l-1]) /*si la valeur maximale du tableau est celle que l'on vient de créer, on met à jour la valeur de la variable correspondante*/
							{
								*val_max=tab[h][l-1];
							}
						}
					}
					
					system("clear");
					print_tableau(tab, hauteur, largeur, *val_max);
				}
			}
			
		break;
		
		case 'k': /*déplacement vers le bas*/
			for(h=hauteur-2; h>=0; h=h-1)
			{
				for(l=0; l<largeur; l=l+1)
				{
					if(tab[h][l]!=0) /*si la case n'est pas vide, on agit*/
					{
						if(tab[h+1][l]==0) /*si la case située en dessous est vide, on peut y déplacer l'élément actuellement en cours de traitement*/
						{
							tab[h+1][l]=tab[h][l];
							tab[h][l]=0;
						}
						else if(tab[h+1][l]==tab[h][l]) /*si la case située en dessous a la même valeur que la case en cours de traitement, on les "fusionne"*/
						{
							tab[h+1][l]=tab[h+1][l]+tab[h][l];
							tab[h][l]=0;
							
							if(*val_max<tab[h+1][l]) /*si la valeur maximale du tableau est celle que l'on vient de créer, on met à jour la valeur de la variable correspondante*/
							{
								*val_max=tab[h+1][l];
							}
						}
					}
					
					system("clear");
					print_tableau(tab, hauteur, largeur, *val_max);
					
				}
			}
			
		break;
		
		case 'l': /*déplacement vers la droite*/
			for(l=largeur-2; l>=0; l=l-1)
			{
				for(h=0; h<hauteur; h=h+1)
				{
					if(tab[h][l]!=0) /*si la case n'est pas vide, on agit*/
					{
						if(tab[h][l+1]==0) /*si la case située à droite est vide, on peut y déplacer l'élément actuellement en cours de traitement*/
						{
							tab[h][l+1]=tab[h][l];
							tab[h][l]=0;
						}
						else if(tab[h][l+1]==tab[h][l]) /*si la case située à droite a la même valeur que la case en cours de traitement, on les "fusionne"*/
						{
							tab[h][l+1]=tab[h][l+1]+tab[h][l];
							tab[h][l]=0;
							
							if(*val_max<tab[h][l+1]) /*si la valeur maximale du tableau est celle que l'on vient de créer, on met à jour la valeur de la variable correspondante*/
							{
								*val_max=tab[h][l+1];
							}
						}
					}
					
					system("clear");
					print_tableau(tab, hauteur, largeur, *val_max);
				}
			}
			
		break;
	}
	
	return;
}


/* @requires hauteur>1, largeur>1, *val_max>0, *cases_vides>0
   @assigns cases du tableau tab, val_max, cases_vides, n_tour
   @ensures à la fin, le joueur a effectué un tour de jeu complet
   @*/
void tour(int** tab, int hauteur, int largeur, int* val_max, int* cases_vides, int* n_tour)
{
    obj nouvel_obj;
	int nb_chiffres;
	char action;
	
	nb_chiffres=max(3, log10(*val_max)+1);
	
    nouvel_obj=nouvel_objet(*cases_vides, *val_max); /*on génère le nouvel objet à ajouter à notre tableau de jeu*/
	
    remplir_tableau(tab, hauteur, largeur, nouvel_obj); /*on place le nouvel objet dans le tableau à la place indiquée*/
	*cases_vides = *cases_vides-1;
	
	action=choix_action(tab, hauteur, largeur, *val_max, nb_chiffres);
	
	execute_action(tab, hauteur, largeur, val_max, action);
	
	
	*n_tour = *n_tour+1;
}


int main()
{
    int param_borne, param_hauteur, param_largeur; /*paramètres du jeu*/
    int confirm; /*variable qui contient 0 en cas de confirmation d'une action, autre chose sinon*/
    int ** tableau; /*tableau à deux dimensions contenant les valeurs du tableau*/
    int h,l; /*variables de boucle for portant sur la hauteur et la largeur du tableau*/
    int nb_cases_vides, valeur_max;
	int n_tour; /*variable contenant le nombre de tours joués, utile pour les stats de fin de partie*/

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
    tableau=(int **)calloc(param_hauteur,sizeof(int*));
    for(h=0 ; h<param_hauteur ; h=h+1)
    {
        tableau[h]=(int *)calloc(param_largeur,sizeof(int));
        for(l=0; l<param_largeur; l=l+1) /*on en profite pour affecter à 0 (<=> vide) toutes les cases du tableau*/
        {
            tableau[h][l]=0;
        }
    }
	
    /*avant de lancer le premier tour, on assigne des valeurs de base aux variables*/
    nb_cases_vides=param_hauteur*param_largeur;
    valeur_max=1;
	n_tour=1;

	/*tour de jeu*/
	tour(tableau, param_hauteur, param_largeur, &valeur_max, &nb_cases_vides, &n_tour);
	if(valeur_max>param_borne) {
		printf("Vous avez gagné !");
	}
	if(nb_cases_vides <= 0){
		printf("il n'y a plus de cases vides, vous avez perdu. :(");
	}
	
    /*à la fin du jeu, on libère la mémoire*/
    free(tableau);
	
    printf("Hello world!\n");
    return 0;
}
