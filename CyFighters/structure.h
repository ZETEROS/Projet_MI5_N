#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nom[20];
    int type ; //1: Attaquant ; 2: Tank ; 3: Guerriseur
    float pv , pv_max , deg , def , esq , vit ;

    void (*special1)(Combatant *cible);  // Pointeurs vers une fonction
    void (*special2)(Combatant *cible);  
    void (*ultimate)(Combatant *cible);  

}Combatant;

#endif