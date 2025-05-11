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

// Normal attack function for each character
void normal_attack(Fighter* Attacker, Fighter* Target) { //to use when the character didn't dodge
    float dmg = (Attacker->dmg * (100 - Target->def))/100;
    Target->hp -= dmg;
    if (Target->hp < 0) Target->hp = 0;  // Prevent negative HP
}

void special_attack(Fighter* Attacker, Fighter* Target) {
    if(Target != NULL){
        if (strcmp(Attacker->name, "John_Wick") == 0) {
            int dmg = (int)(Attacker->dmg * 0.75);  // 75% damage per shot
            Target->hp -= 2 * dmg;

        } else if (strcmp(Attacker->name, "Hulk") == 0) {
            Target->dmg = (int)(Target->dmg * 0.8);  // Reduces dmg by 20%

        } else if (strcmp(Attacker->name, "Lifeline") == 0) {
            Attacker->hp = (Attacker->hp + 25 > 100) ? 100 : Attacker->hp + 25;
            
        } else if (strcmp(Attacker->name, "Sans") == 0) {
            Target->dodge /= 2;  // Reduces dodge by half

        } else if (strcmp(Attacker->name, "Ronflex") == 0) {
            Target->def = (int)(Target->def * 0.7);  // Reduces def by 30%

        } else if (strcmp(Attacker->name, "Dracula") == 0) {
            int heal = (int)(Attacker->dmg * 0.4);  // Heal 40% of dmg dealt
            Target->hp -= heal;
            Attacker->hp = (Attacker->hp + heal > 100) ? 100 : Attacker->hp + heal;

        } else if (strcmp(Attacker->name, "Batman") == 0) {
            // Batman becomes invisible for 1 turn

        } else if (strcmp(Attacker->name, "Demolisher") == 0) {
            int dmg = Attacker->dmg;
            Target->hp -= dmg;
            
        } else if (strcmp(Attacker->name, "Medic") == 0) {
            Attacker->hp = (Attacker->hp + 30 > 100) ? 100 : Attacker->hp + 30;
        }
    }
    else{
        printf("Couldnt attack because Target is NULL\n");
    }
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
    printf("Name = %s\nHP: %.2f\nHP_MAX:%.2f\nDMG:%.2f\nDEF:%.2f\nDODGE:%.2f\nSPEED:%.2f\n\n",a.name,a.hp,a.hp_max,a.dmg,a.dmg,a.def,a.dodge,a.speed);
}

#endif
