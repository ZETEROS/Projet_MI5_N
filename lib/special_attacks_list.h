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
#include "price_special_attack.h"
#include "renderingfonctions.h"
#include "enum.h"

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



void special_attack(Fighter* Attacker, Fighter* Target , int* team_coins , Fight_State* fight , SDL_Renderer* render , TTF_Font* font , Fighter* team1 , Fighter* team2 , int team1_count , int team2_count , int* attack_now , int* hit , int* heal , int* did_dodge , Mix_Chunk* hit_fx , Mix_Chunk* dodge_fx) {
    int prices[9] = {price_double_tap , price_immobilization , price_in_the_shadows , price_thunder_clap , price_tackle , price_rock_throw , price_drone_heal , price_drainage , price_crusaders_crossbow};
    if(Target != NULL){
        if (strcmp(Attacker->name, "John_Wick") == 0 && *team_coins >= prices[0])  {

            if(Dodged(Target)){
                *team_coins -= prices[0];
                *did_dodge = 1;
                Mix_PlayChannel(-1 , dodge_fx , 0);
            }
            else{
                float normal_dmg = Attacker->dmg *(100-Target->def)/100;
                float special_dmg = (normal_dmg * 0.75) ;  // 75% damage per shot
                Target->hp -= 2 * special_dmg;
                *team_coins -= prices[0];
                Mix_PlayChannel(-1 , hit_fx , 0);
            }

        } 
        else if (strcmp(Attacker->name, "Hulk" ) == 0 && *team_coins >= prices[3])  {
            if(Dodged(Target)){
                *team_coins -= prices[3];
                *did_dodge = 1;
                Mix_PlayChannel(-1 , dodge_fx , 0);
            }
            else{
                Target->dmg = (Target->dmg * 0.8);  // Reduces dmg by 20%
                *team_coins -= prices[3];
                Mix_PlayChannel(-1 , hit_fx , 0);
            }

        } 
        else if (strcmp(Attacker->name, "Lifeline") == 0 && *team_coins >= prices[6])  {
            if(Dodged(Target)){
               *team_coins -= prices[6];
               *did_dodge = 1;
               Mix_PlayChannel(-1 , dodge_fx , 0);
            }
            else{
                 if(Target->hp + 25 > 100){
                    Target -> hp = 100;
                }
                else{
                    Target->hp += 25;
                }
                *team_coins -= prices[6];
                Mix_PlayChannel(-1 , hit_fx , 0);
            }
        } 
        else if (strcmp(Attacker->name, "Sans") == 0 && *team_coins >= prices[1])  {
            if(Dodged(Target)){
                *team_coins -= prices[1];
                *did_dodge = 1;
                Mix_PlayChannel(-1 , dodge_fx , 0);
            }
            else{
                Target->dodge /= 2;  // Reduces dodge by half
                *team_coins -= prices[1];
                Mix_PlayChannel(-1 , hit_fx , 0);
            }

        } 
        else if (strcmp(Attacker->name, "Snorlax") == 0 && *team_coins >= prices[4])  {
            if(Dodged(Target)){
                *team_coins -= prices[4];
                *did_dodge = 1;
                Mix_PlayChannel(-1 , dodge_fx , 0);
            }
            else{
                Target->def = (Target->def * 0.7);  // Reduces def by 30%
                *team_coins -= prices[4];
                Mix_PlayChannel(-1 , hit_fx , 0);
            }

        } 
        else if (strcmp(Attacker->name, "Dracula") == 0 && *team_coins >= prices[7])  {
            if(Dodged(Target)){
                *team_coins -= prices[7];
                *did_dodge = 1;
                Mix_PlayChannel(-1 , dodge_fx , 0);
            }
            else{
                float heal = (Attacker->dmg * 0.4);  // Heal 40% of dmg dealt
                Target->hp -= heal;
                if(Attacker->hp + 25 > 100){
                    Attacker -> hp = 100;
                }
                else{
                    Attacker->hp += heal;
                }
                *team_coins -= prices[7];
                Mix_PlayChannel(-1 , hit_fx , 0);
            }

        } 
        else if (strcmp(Attacker->name, "Batman") == 0 && *team_coins >= prices[2])  {
            if(Dodged(Target)){
                *team_coins -= prices[2];
                *did_dodge = 1;
                Mix_PlayChannel(-1 , dodge_fx , 0);
            }
            else{
                Attacker->dodge = Attacker->dodge * 1.2 ;
                *team_coins -= prices[2];
                Mix_PlayChannel(-1 , hit_fx , 0);
            }

        } 
        else if (strcmp(Attacker->name, "Demolisher") == 0 & *team_coins >= prices[5])  {
            if(Dodged(Target)){
                *team_coins -= prices[5];
                *did_dodge = 1;
                Mix_PlayChannel(-1 , dodge_fx , 0);
            }
            else{
                float dmg = Attacker->dmg;    //Attacks without considering the target's def
                Target->hp -= dmg;
                *team_coins -= prices[5];
                Mix_PlayChannel(-1 , hit_fx , 0);
            }
            
        } 
        else if (strcmp(Attacker->name, "The_Medic") == 0 && *team_coins >= prices[8])  {
            if(Dodged(Target)){
                *team_coins -= prices[8];
                *did_dodge = 1;
                Mix_PlayChannel(-1 , dodge_fx , 0);
            }
            else{ 
                if(Target->hp + 30 > 100){
                    Target -> hp = 100;
                }
                else{
                    Target->hp += 30;
                }
                *team_coins -= prices[8];
                Mix_PlayChannel(-1 , hit_fx , 0);
            }
        }
        else{
            rendermessageTEMP("Not enough coins for Special Attack" , &MessageSelection , render , 200 , font);
            *fight = SELECTING_FIGHTER;
            FIGHT_unselectallfighters(team1 , team2 , team1_count , team2_count);
            *attack_now = 0;
            *hit = 0;
            *heal = 0;
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

int is_Healer(Fighter* Attacker){
    if(strcmp(Attacker->name , "Lifeline") == 0 || strcmp(Attacker->name , "The_Medic") == 0){
        return 1;
    }
    else{
        return 0;
    }
}

#endif
