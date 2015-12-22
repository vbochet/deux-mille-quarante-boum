# Makefile pour le projet d'IPI 2015-2016
# Vincent BOCHET, décembre 2015

#le nom de l'exécutable généré. Peut être modifié.
APPLI=deuxmillequaranteboum
#liste des fichiers à compiler.
CSRC= main.c jeu.c jeu_fin.c jeu_init.c tableau.c utils.c
#compilateur à utiliser
CC = gcc

#flags à utiliser lors des compilations
CFLAGS = -Wall -Wextra -ansi -lm 

#liste des fichiers .o générés
COBJ=$(CSRC:.c=.o)

#création des fichiers .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

#création de l'exécutable
$(APPLI):	$(COBJ)
	$(CC) -o $(APPLI) $(COBJ) -lm

#pour supprimer les fichiers inutiles
clean:
	-rm *.o *[~%] core *.bak

