Deux-Mille-Quarante-Boum
========================

Jeu de type 2048 codé en langage C dans le cadre d'un projet de programmation impérative.

Comment compiler le programme ?
-------------------------------

Le programme est prévu pour être compilé et utilisé sous Linux. Pour cela :
- Ouvrez un terminal ;
- Placez-vous dans le répertoire du programme ;
- Exécutez la commande `make` qui génèrera un programme nommé par défaut `deuxmillequaranteboum` (le nom de l'exécutable généré peut être modifié dans le fichier `Makefile`) ;
- Pour jouer, exécutez le fichier `deuxmillequaranteboum`.

Utilisation du jeu
------------------

Ce programme a été réalisé en mode texte.  
Au lancement, vous devez indiquer la valeur que vous souhaitez atteindre, ainsi que la hauteur et la largeur du tableau sur lequel vous jouerez.  
Lorsque vous aurez validé votre choix, vous pourrez jouer et déplacer les éléments du tableau comme suit :
- `i` pour déplacer vers le haut ;
- `j` pour déplacer vers la gauche ;
- `k` pour déplacer vers le bas ;
- `l` pour déplacer vers la droite ;
- `b` pour faire exploser une bombe. Vous devrez alors indiquer sa hauteur et sa largeur dans le tableau (en considérant l'origine du tableau en bas à gauche).

Informations complémentaires
----------------------------

Les éléments de même valeur s'additionnent, les autres s'ignorent.  
Les bombes sont de trois types : +, x et *. Une bombe + qui explose détruit les cases situées à sa droite, sa gauche, au dessus et en dessous. Une bombe x qui explose détruit les quatre cases situées directement à ses diagonales. Une bombe * qui explose détruit les huit cases qui l'entourent.  
Deux bombes + qui se rencontrent forment une bombe x. Deux bombes x qui se rencontrent forment une bombe *. Deux bombes * qui se rencontrent explosent. Toute bombe posée depuis 7 tours explosera sponatément au début du huitième.  
Le jeu prend fin lorsque l'une des cases du tableau au moins contient une valeur supérieure ou égale à celle fixée à l'initialisation du jeu.  
Vous pouvez néanmoins à tout moment interrompre votre partie en indiquant lors d'un tour le choix `q` et en validant votre choix.  
L'utilisation de `h` lors de la demande de choix vous affichera l'aide (rappel des options possibles).  

Licence
-------

Ce programme est distribué sous licence Creative-Commons BY-NC-SA.