#ifndef FIGHTER_LOADER_H
#define FIGHTER_LOADER_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "structure.h"
#endif

#include "renderingfonctions.h"



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
Fighter importandassign(char* file , SDL_Texture** visuals , SDL_Texture** visuals_selected){
    Fighter a;
    FILE* doc = fopen(file , "rb");
    if(doc == NULL){
        printf("File not found");
        exit(1);

    }
    fread(&a , sizeof(Fighter), 1 , doc);
    fclose(doc);
    a.selected = 0;

    char* names[9] = {"John_Wick" , "Sans", "Batman" , "Hulk" , "Snorlax" , "Demolisher" , "Lifeline", "Dracula" , "The_Medic"};


    for (int i= 0 ; i<9 ; i++){
        if(strcmp(names[i] , a.name) == 0){
            a.sprite = visuals[i];
            a.sprite_selected = visuals_selected[i];
        }
    }
    if(!a.sprite || !a.sprite_selected){
        printf("Couldn't assign the visual model to , at least , a fighter. Maybe the binary file has the wrong name for the fighter or the .png is missing.");
        exit(10);
    }

    return a;

}
void show_stats(Fighter a){
    printf("Name = %s\nHP: %.2f\nHP_MAX:%.2f\nDMG:%.2f\nDEF:%.2f\nDODGE:%.2f\nSPEED:%.2f\n",a.name,a.hp,a.hp_max,a.dmg,a.dmg,a.def,a.dodge,a.speed);
}

#endif