# Makefile pour le projet d'IPI 2015-2016
# Vincent BOCHET, décembre 2015

APPLI=deuxmillequaranteboum
CSRC= main.c jeu.c jeu_fin.c jeu_init.c tableau.c utils.c
CC = gcc

CFLAGS = -Wall -Wextra -ansi -lm 

COBJ=$(CSRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

$(APPLI):	$(COBJ)
	$(CC) -o $(APPLI) $(COBJ) -lm

clean:
	-rm *.o *[~%] core *.bak

