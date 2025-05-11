#ifndef BUTTONS_COORD_H
#define BUTTONS_COORD_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>


 
extern    SDL_Rect Button_START ;
extern    SDL_Rect Button_HOWTOPLAY ;
extern    SDL_Rect Button_QUIT ;
extern    SDL_Rect Button_MAINMENU_FROM_SELECTION_HTP ;
extern    SDL_Rect Fire1 ;
extern    SDL_Rect Fire2 ;

    //TEAM SELECTION - LOGOS COORD
extern    SDL_Rect Logo_John_Wick ;
extern    SDL_Rect Logo_Sans ;
extern    SDL_Rect Logo_Batman ;
extern    SDL_Rect Logo_Hulk ;
extern    SDL_Rect Logo_Snorlax ;
extern    SDL_Rect Logo_Demolisher ;
extern    SDL_Rect Logo_Lifeline ;
extern    SDL_Rect Logo_Dracula ;
extern    SDL_Rect Logo_Medic ;
extern    SDL_Rect Left_Key_Logos ;
    //team 1 
extern    SDL_Rect Team1_Member1 ;
extern    SDL_Rect Team1_Member2 ;
extern    SDL_Rect Team1_Member3 ;
extern    SDL_Rect Team1_Member4 ;
extern    SDL_Rect coins1 ;
extern    SDL_Rect ready1 ;
extern    SDL_Rect yourturn1 ;


    //team 2
extern    SDL_Rect Team2_Member1 ;
extern    SDL_Rect Team2_Member2 ;
extern    SDL_Rect Team2_Member3 ;
extern    SDL_Rect Team2_Member4 ;
extern    SDL_Rect coins2 ;
extern    SDL_Rect ready2 ;
extern    SDL_Rect yourturn2 ;


    //PRICES POSITIONS
extern    SDL_Rect Price_John_Wick;
extern    SDL_Rect Price_Sans;
extern   SDL_Rect Price_Batman ;
extern    SDL_Rect Price_Hulk ;
extern    SDL_Rect Price_Snorlax ;
extern    SDL_Rect Price_Demolisher;
extern    SDL_Rect Price_Lifeline ;
extern    SDL_Rect Price_Dracula ;
extern    SDL_Rect Price_The_Medic ;



extern   SDL_Rect Button_SelectPVP ;
    //SDL_Rect Button_SelectPVB = {780 , 472 , 267 , 67};


    //ERROR MESSAGES
extern    SDL_Rect MessageSelection ;

    //Stats rendering

extern    SDL_Rect Info_HP;
extern    SDL_Rect Info_DMG;
extern    SDL_Rect Info_DEF ;
extern    SDL_Rect Info_DODGE ;
extern    SDL_Rect Info_SPEED ;


    //FIGHT
    //Modification size || Resolution native of the models is 105 * 165 px.
extern    SDL_Rect Team1_Fighter1;
extern    SDL_Rect Team1_Fighter2 ;
extern    SDL_Rect Team1_Fighter3 ;
extern    SDL_Rect Team1_Fighter4 ;

extern    SDL_Rect Team2_Fighter1 ;
extern    SDL_Rect Team2_Fighter2;
extern    SDL_Rect Team2_Fighter3 ;
extern    SDL_Rect Team2_Fighter4 ;

extern   SDL_Rect Pause_button ;
extern    SDL_Rect Continue_button_pause;
extern    SDL_Rect Menu_button_pause;
extern    SDL_Rect Quit_button_pause;

extern    SDL_Rect fight_torch1 ;
extern    SDL_Rect fight_torch2 ;
extern    SDL_Rect fight_torch3;
extern    SDL_Rect fight_torch4 ;

extern    SDL_Rect Basic_Attack ;
extern    SDL_Rect Special_Attack ;
    //SDL_Rect Ultimate_Attack = {644 , 594 , 110 , 106};
extern    SDL_Rect No_Attack ;

extern    SDL_Rect ATTACK_BUTTON ;

extern    SDL_Rect Coin_ammount ;

extern    SDL_Rect hitordodge ;

    //END GAME

extern    SDL_Rect Main_Menu_Button_From_EndGame ;
extern    SDL_Rect END_GAME_Fighter1 ;
extern    SDL_Rect END_GAME_Fighter2 ;
extern    SDL_Rect END_GAME_Fighter3 ;
extern    SDL_Rect END_GAME_Fighter4 ;

#endif
