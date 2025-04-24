#ifndef FIGHTER_LOADER_H
#define FIGHTER_LOADER_H
#include <stdio.h>
#include <stdlib.h>
#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "structure.h"
#endif


//List of special attacks
void test(Fighter* a){
    printf("It works!");
}

//Fonction to assign the special attack by looking at the name of the attack in the struct of the fighter.
void assign_special(Fighter* a){
    //if(strcmp(a->special_attack_name , "test")){
       // a->AttackFunction = test ;
    //}
}

//Fonction to import the fighter and to use the assign fonction saw before.
Fighter importandassign(char* file){
    Fighter a;
    FILE* doc = fopen(file , "rb");
    if(doc == NULL){
        printf("File not found");
        exit(1);

    }
    fread(&a , sizeof(Fighter), 1 , doc);
    fclose(doc);
    assign_special(&a);

    return a;

}
void show_stats(Fighter a){
    printf("Name = %s\nHP: %.2f\nHP_MAX:%.2f\nDMG:%.2f\nDEF:%.2f\nDODGE:%.2f\nSPEED:%.2f\n",a.name,a.hp,a.hp_max,a.dmg,a.dmg,a.def,a.dodge,a.speed);
}

#endif