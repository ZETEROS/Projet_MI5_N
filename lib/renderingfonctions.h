#ifndef RENDERING_FONCTIONS_H
#define RENDERING_FONCTIONS_H
#include <stdlib.h>
#include <stdio.h>
#ifndef BUTTONS_COORD_H
#define BUTTONS_COORD_H
#include "lib/buttons-coord.h"
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* loadTexture(char* path , SDL_Renderer* renderer){
    SDL_Surface* surface = IMG_Load(path);
    if (!surface){
        printf("Image not found.\n%s\n",IMG_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer , surface);
    SDL_FreeSurface(surface);
    return texture;

}


void rendercoins(SDL_Renderer* renderer, int coin, SDL_Rect* pos, int size, SDL_Color color) {
    int x = pos->x ;
    int y = pos->y ;
    char coin_text[10];
    sprintf(coin_text , "%d", coin);
    TTF_Font* font = TTF_OpenFont("assets/pixel_font.ttf", size);
    if (!font) {
    printf("Failed to load font: %s\n", TTF_GetError());
    exit(1);
    } 
    SDL_Surface* surface = TTF_RenderText_Solid(font, coin_text, color); 
    if (!surface) {
        printf("Text surface error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Text texture error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_RenderCopy(renderer, texture, NULL, pos);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void showinfoandstats(SDL_Renderer* renderer , SDL_Texture* screen , Fighter* fighter , Mix_Chunk* sound , SDL_Texture* teamselection_screen , int team1_coins , SDL_Texture* blink_turn ){
    Mix_PlayChannel(-1 , sound , 0);
    SDL_Color dark_grey = {70 , 70 , 70};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer , screen , NULL , NULL);

    char hp[10] , dmg[10] , def[10] , dodge[10] , speed[10] ; 
    sprintf(hp , "%.1f", fighter-> hp_max);
    sprintf(dmg , "%.1f", fighter-> dmg);
    sprintf(def , "%.1f", fighter-> def);
    sprintf(dodge , "%.1f", fighter-> dodge);
    sprintf(speed , "%.1f", fighter-> speed);

    char* name_stats[5] = {hp , dmg , def , dodge , speed};
    SDL_Rect* list_stats_pos [5] = {&Info_HP , &Info_DMG , &Info_DEF , &Info_DODGE , &Info_SPEED };

    TTF_Font* font = TTF_OpenFont("assets/pixel_font.ttf", 24);
    if (!font) {
    printf("Failed to load font: %s\n", TTF_GetError());
    exit(1);
    }
    for (int i = 0 ; i<5 ; i++){
        SDL_Surface* surface = TTF_RenderText_Solid(font, name_stats[i], dark_grey);
         
        if (!surface) {
            printf("Text surface error: %s\n", TTF_GetError());
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            printf("Text texture error: %s\n", SDL_GetError());
            SDL_FreeSurface(surface);
            return;
        }

        SDL_RenderCopy(renderer, texture, NULL, list_stats_pos[i]);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    
    }
    SDL_RenderPresent(renderer);

    int info_visible = 1 ;
    SDL_Event sub_event ;
    while (info_visible){
        while (SDL_PollEvent(&sub_event)) {
            
        if (sub_event.type == SDL_KEYDOWN) {
            info_visible = 0;
        }
        }
    }
    Mix_PlayChannel(-1 , sound , 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer , teamselection_screen , NULL , NULL);
    rendercoins(renderer , team1_coins , &coins1 , 40 , dark_grey);
    SDL_RenderCopy(renderer , blink_turn , NULL , &yourturn1);
    SDL_RenderPresent(renderer);
}

#endif