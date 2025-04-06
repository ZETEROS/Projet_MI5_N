#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char name[20];
    int class ; //1: Attacker ; 2: Tank ; 3: Healer
    float hp , hp_max , dmg , def , dodge , speed ;

    //void (*special1)(Fighter *cible);  // Pointeurs vers une fonction
    //void (*special2)(Fighter *cible);  
    //void (*ultimate)(Fighter *cible);  

}Fighter;

void show_stats(Fighter a){
    printf("Name = %s\nHP: %.2f\nHP_MAX:%.2f\nDMG:%.2f\nDEF:%.2f\nDODGE:%.2f\nSPEED:%.2f\n",a.name,a.hp,a.hp_max,a.dmg,a.dmg,a.def,a.dodge,a.speed);
}