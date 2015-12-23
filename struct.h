/* STRUCTURE DE DONNÉES */

#ifndef __STRUCT_H
#define __STRUCT_H

struct s_obj{ /* structure d'objet du tableau */
    int position; /* position dans le tableau, en terme de k_ième case vide (utile uniquement lors de la génération de cet élément dans le tableau pour le placer, mais plus utilisé ensuite) */
    int valeur; /* valeur de l'objet (-1 à -8 => +, -11 à -18 => x, -21 à -28 => *, et nombre positif sinon) */
    int fusion; /* si l'objet résulte d'une fusion au tour k, alors fusion = k. Cela évite de sommer des cases créées durant le tour. */
};
typedef struct s_obj obj;

#endif