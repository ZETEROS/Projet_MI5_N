#ifndef ENUM_H
#define ENUM_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


typedef struct Fighter Fighter ;

struct Fighter {
    char name[20];
    int class; //1: Attacker ; 2: Tank ; 3: Healer
    float hp , hp_max , dmg , def , dodge , speed ;
    int price ;

    //Visual model
    SDL_Texture* sprite;
    SDL_Texture* sprite_selected;


    char special_attack_name[20];
    int selected ;

};

typedef enum{
        SELECTING_FIGHTER,
        PAUSE,
        SELECTING_ATTACK,
        SELECTING_TARGET,
}Fight_State;

typedef enum{
    BASIC_ATTACK ,
    SPECIAL_ATTACK,
    
    NO_ATTACK,
}Type_attack;

//GAME STATES (MOMENTS)
    typedef enum{
        MENU,
        GAMEMODE_SELECTION,
        TEAM_SELECTION,
        FIGHT,
        END_GAME,
        HOW_TO_PLAY,
        
}Game_State;


void special_attack (Fighter* Attacker, Fighter* Target , int* team_coins , Fight_State* fight , SDL_Renderer* render , TTF_Font* font , Fighter* team1 , Fighter* team2 , int team1_count , int team2_count , int* attack_now , int* hit , int* heal , int* did_dodge , Mix_Chunk* hit_fx , Mix_Chunk* dodge_fx);
Fighter importandassign(char* file , SDL_Texture** visuals , SDL_Texture** visuals_selected);
void show_stats(Fighter a);
int is_Healer(Fighter* Attacker);
SDL_Texture* loadTexture(char* path , SDL_Renderer* renderer);
void rendercoins(SDL_Renderer* renderer, int coin, SDL_Rect* pos, int size, SDL_Color color , TTF_Font* font);
void showprices(SDL_Renderer* render , Fighter** PRETEAM , TTF_Font* font);
void showinfoandstats(SDL_Renderer* renderer , SDL_Texture* screen , Fighter* fighter , Mix_Chunk* sound , SDL_Texture* teamselection_screen , int team1_coins ,int team2_coins, SDL_Texture* blink_turn , SDL_Texture* ready_pressed, int current_team, TTF_Font* font);
int howmanyselected(Fighter** team );
int FIGHT_didselectedsomeone(Fighter* team );
void rendermessageTEMP(char* message ,SDL_Rect* pos,  SDL_Renderer* renderer , /*0 for no delay , >0 for delay , this will ignore every input during the showing of the message*/ int timeshowing , TTF_Font* font );
void renderlogoselectedfighters(SDL_Renderer* render, Fighter** PRETEAM ,SDL_Texture** All_Logos, int team);
void addorkickfromteam(Fighter** preteam , SDL_Renderer* render , int character, TTF_Font* font , Mix_Chunk* tick_sound , int* team_coins);
void unselectallfighters(Fighter** PRETEAM1 , Fighter** PRETEAM2);
void FIGHT_unselectallfighters(Fighter* team_to_unselect1 , Fighter* team_to_unselect2 , int team1_count , int team2_count);
Fighter* createfinalteam ( Fighter** PRETEAM , SDL_Texture** visuals , SDL_Texture** visuals_selected);
void render_animation(SDL_Renderer* renderer, SDL_Texture* sprites, SDL_Rect* pos, int frame_width ,int frame_height, int scale, int num_frames , int whatteam , int ms_to_change_frame);
void render_hp(SDL_Renderer* render , SDL_Texture* hp_sprite , SDL_Rect* pos , Fighter fighter );
void renderfighters(SDL_Renderer* render,SDL_Texture* hp_sprite ,SDL_Texture* grave, Fighter* Team1 , Fighter* Team2 , int team1_count , int team2_count );
float whostarts(Fighter* Team1 , Fighter* Team2 , int team1_count , int team2_count);
int someonealive(Fighter* Team , int team_count);
void init_teams(Fighter** team1, Fighter** team2 , Fighter** PRETEAM1 ,Fighter** PRETEAM2 , SDL_Texture** visuals , SDL_Texture ** visuals_selected);
void cleanup_teams(Fighter** team1, Fighter** team2 , int* team1_coins , int* team2_coins);
void FIGHT_fire_in_background(SDL_Renderer* render , SDL_Texture* fire_animation ,SDL_Texture* fight_torches_texture);
int OnlyOneTargetsSelected(Fighter* enemy_team , int team_count , Fighter exception );
int AnyTargetSelected(Fighter* enemy_team , int team_count);
Fighter* WhoIsSelected(Fighter* team , int team_count);
int Dodged(Fighter* target );
int if_still_alive_only(Fighter fighter);
void END_GAME_renderfighters(SDL_Renderer* render , Fighter* winning_team ,SDL_Texture* grave ,  int team_count );
Fighter* select_target_for_special_attack(int x_click , int y_click , Fighter* Attacker , Fighter* aly_team , Fighter* enemy_team , int aly_count ,int enemy_count, int turn_to_attack , int number_turn);
void no_attack(int turn , int* team1_coins , int* team2_coins);

#endif



