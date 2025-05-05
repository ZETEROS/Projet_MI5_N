#ifndef RENDERING_FONCTIONS_H
#define RENDERING_FONCTIONS_H
#include <stdlib.h>
#include <stdio.h>
#include "buttons-coord.h"

#include "structure.h"
#include "special_attacks_list.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

Fighter importandassign();

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


void rendercoins(SDL_Renderer* renderer, int coin, SDL_Rect* pos, int size, SDL_Color color , TTF_Font* font) {
    int x = pos->x ;
    int y = pos->y ;
    char coin_text[10];
    sprintf(coin_text , "%d", coin);
    
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

void showinfoandstats(SDL_Renderer* renderer , SDL_Texture* screen , Fighter* fighter , Mix_Chunk* sound , SDL_Texture* teamselection_screen , int team1_coins ,int team2_coins, SDL_Texture* blink_turn , SDL_Texture* ready_pressed, int current_team, TTF_Font* font){
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

    if (current_team == 1 ){
        Mix_PlayChannel(-1 , sound , 0);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer , teamselection_screen , NULL , NULL);
        rendercoins(renderer , team1_coins , &coins1 , 40 , dark_grey, font);
        SDL_RenderCopy(renderer , blink_turn , NULL , &yourturn1);
        SDL_RenderPresent(renderer);
    }
    else if (current_team == 2){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer , teamselection_screen , NULL , NULL);
        rendercoins(renderer , team1_coins , &coins1 , 40 , dark_grey , font);
        rendercoins(renderer , team2_coins , &coins2 , 40 , dark_grey, font);
        SDL_RenderCopy(renderer , blink_turn , NULL , &yourturn2);
        SDL_RenderCopy(renderer , ready_pressed , NULL ,&ready1);
        SDL_RenderPresent(renderer);
    }
}

int howmanyselected(Fighter** team ){
    int num = 0;
    for (int i= 0 ; i<9 ; i++){
        if(team[i]->selected == 1){
            num++;
        }
        
    }
    return num;
}

void rendermessageTEMP(char* message ,SDL_Rect* pos,  SDL_Renderer* renderer , /*0 for no delay , >0 for delay , this will ignore every input during the showing of the message*/ int timeshowing , TTF_Font* font ){
    SDL_Color color = {255 , 255 , 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, message, color); 
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
    SDL_RenderPresent(renderer);

    if(timeshowing >0){
        Uint32 start = SDL_GetTicks();
        SDL_Event temp_event;
        while (SDL_GetTicks() - start < timeshowing) {
            while (SDL_PollEvent(&temp_event)) {
                // All clicks during the message showing will be treat , this will stop the number of events going up and crash the game || IMPORTANT!!
            }
            SDL_Delay(10); // Delay to prevent using all CPU in during the polling 
        }
    }
    else{
        
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void renderlogoselectedfighters(SDL_Renderer* render, Fighter** PRETEAM ,SDL_Texture** All_Logos, int team){
    SDL_Rect* team1_slots[4] = {&Team1_Member1 , &Team1_Member2 , &Team1_Member3 , &Team1_Member4};
    SDL_Rect* team2_slots[4] = {&Team2_Member1 , &Team2_Member2 , &Team2_Member3 , &Team2_Member4};
    int s=0;
    for (int i=0 ; i<9 ; i++){
        if(PRETEAM[i]->selected == 1){
            if(team == 1){
                SDL_RenderCopy(render , All_Logos[i] , NULL , team1_slots[s]);
                s++;
            }
            else if(team == 2){
                SDL_RenderCopy(render , All_Logos[i] , NULL , team2_slots[s]);
                s++;
            }
                
        }
    }
}

void addorkickfromteam(Fighter** preteam , SDL_Renderer* render , int character, TTF_Font* font ){
    if(howmanyselected(preteam) <= 4 && howmanyselected(preteam) >= 0){
            if(preteam[character]->selected == 0 ){
                if(howmanyselected(preteam) == 4){
                    rendermessageTEMP("You only can pick 4" , &MessageSelection , render , 2000 , font );
                }
                else{
                    preteam[character]->selected =1 ;
                }
            }

            else if(preteam[character]->selected == 1){
                if(howmanyselected(preteam) == 0){
                    rendermessageTEMP("Impossible" , &MessageSelection , render , 2000, font );
                }
                else{
                    preteam[character]->selected = 0;
                }
                                        
            }
    }

    else{
        rendermessageTEMP("You need to pick 2 to 4 fighters" , &MessageSelection , render , 2000 , font);
    }


}


void unselectallfighters(Fighter** PRETEAM1 , Fighter** PRETEAM2){

    for (int i = 0 ; i<9 ; i++){
        PRETEAM1[i]->selected = 0 ;
        PRETEAM2[i]->selected = 0 ;
    }
}

Fighter* createfinalteam ( Fighter** PRETEAM , SDL_Texture** visuals){

    int numberfighters = howmanyselected(PRETEAM);
    Fighter* a = malloc(sizeof(Fighter) * numberfighters);
    int j= 0;
    for (int i = 0 ; i<9 ; i++){
        if (PRETEAM[i]->selected == 1){
            switch(i){
                case 0:
                    a[j] = importandassign("Fighters/John_Wick" , visuals);
                    j++;
                break;
                case 1:
                    a[j] = importandassign("Fighters/Sans", visuals);
                    j++;
                break;
                case 2:
                    a[j] = importandassign("Fighters/Batman", visuals);
                    j++;
                break;
                case 3:
                    a[j] = importandassign("Fighters/Hulk", visuals);
                    j++;
                break;
                case 4:
                    a[j] = importandassign("Fighters/Snorlax", visuals);
                    j++;
                break;
                case 5:
                    a[j] = importandassign("Fighters/Demolisher", visuals);
                    j++;
                break;
                case 6:
                    a[j] = importandassign("Fighters/Lifeline", visuals);
                    j++;
                break;
                case 7:
                    a[j] = importandassign("Fighters/Dracula", visuals);
                    j++;
                break;
                case 8:
                    a[j] = importandassign("Fighters/The_Medic", visuals);
                    j++;
                break;
                
            }
        }
    }

    return a;

}

void renderfighters(SDL_Renderer* render, Fighter* Team1 , Fighter* Team2 , int team1_count , int team2_count){
    SDL_Rect* team1_slots[4] = {&Team1_Fighter1 , &Team1_Fighter2 , &Team1_Fighter3 , &Team1_Fighter4};
    SDL_Rect* team2_slots[4] = {&Team2_Fighter1 , &Team2_Fighter2 , &Team2_Fighter3 , &Team2_Fighter4};
    
    for (int i = 0; i < team1_count; i++) {
        if (Team1[i].model != NULL) {
            if(Team1[i].hp > 0){
                SDL_RenderCopy(render, Team1[i].model, NULL, team1_slots[i]);
            }
            else{
                SDL_RenderCopy(render, Team1[i].model, NULL, team1_slots[i]);
            }
        }
    }
    for (int j = 0; j < team2_count; j++) {
        if (Team2[j].model != NULL) {
            SDL_RenderCopyEx(render, Team2[j].model, NULL, team2_slots[j] , 0.0 , NULL , SDL_FLIP_HORIZONTAL);
        }
    
    }
}

int whostarts(Fighter* Team1 , Fighter* Team2 , int team1_count , int team2_count){

    int team1_speed = 0;
    int team2_speed = 0;
    for (int i=0 ; i< team1_count ; i++){
        team1_speed += Team1[i].speed ;
    }
    for(int j=0 ; j< team2_count ; j++){
        team2_speed += Team2[j].speed;
    }

    if(team1_speed > team2_speed){
        return 1;
    }
    else if(team2_speed > team1_speed){
        return 2;
    }
    else{
        return 1 + rand() % 2;
    }
}

int someonealive(Fighter* Team , int team_count){
    int total_hp = 0;

    for (int i=0 ; i<team_count ; i++){
        total_hp += Team[i].hp ;
    }
    return total_hp;
}


void render_fire_animation(SDL_Renderer* renderer, SDL_Texture* fire_texture, SDL_Rect* pos, int scale, int num_frames) {

    static Uint32 start_time = 0;
    if (start_time == 0) start_time = SDL_GetTicks();

    int frame_width = 15;
    int frame_height = 24;
    
    //How much time passed already?
    Uint32 elapsed = SDL_GetTicks() - start_time;

    // Change frame each 100 ms so 10 fps.
    int current_frame = (elapsed / 100) % num_frames;

    SDL_Rect src_rect = {
        .x = current_frame * frame_width,
        .y = 0,
        .w = frame_width,
        .h = frame_height
    };

    SDL_Rect dest_rect = {
        .x = (pos->x) ,
        .y = (pos->y) - (frame_height * scale),
        .w = frame_width * scale,
        .h = frame_height * scale
    };



    SDL_RenderCopy(renderer, fire_texture, &src_rect , &dest_rect);
}



#endif
