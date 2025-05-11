#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct Fighter Fighter ;

struct Fighter {
    char name[20];
    int class ; //1: Attacker ; 2: Tank ; 3: Healer
    float hp , hp_max , dmg , def , dodge , speed ;
    int price ;

    //Visual model
    SDL_Texture* sprite;
    SDL_Texture* sprite_selected;


    char special_attack_name[20];
    int selected ;

};

#endif
