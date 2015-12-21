/* STRUCTURE DE DONNÉES */

#ifndef __STRUCT_H
#define __STRUCT_H

struct s_obj{
    int position; /*position dans le tableau, en terme de k_ième case vide*/
    int type; /*1 pour nombre*/
    int valeur; 
};
typedef struct s_obj obj;

#endif