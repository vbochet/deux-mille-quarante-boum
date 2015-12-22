/* STRUCTURE DE DONNÉES */

#ifndef __STRUCT_H
#define __STRUCT_H

struct s_obj{ /* structure d'objet du tableau */
    int position; /* position dans le tableau, en terme de k_ième case vide */
    int valeur; /* valeur de l'objet (1, 2, 4, 8, ...) */
    int fusion; /* si l'objet résulte d'une fusion au tour k, alors fusion = k. Cela évite de sommer des cases créées durant le tour. */
};
typedef struct s_obj obj;

#endif