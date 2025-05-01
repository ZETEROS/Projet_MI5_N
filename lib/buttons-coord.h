#ifndef BUTTONS_COORD_H
#define BUTTONS_COORD_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>



SDL_Rect Button_START = {509 , 404 , 259 , 55};
SDL_Rect Button_HOWTOPLAY = {509 , 478 , 259 , 55};
SDL_Rect Button_QUIT = {509 , 553 , 259 , 55};
SDL_Rect Button_MAINMENU_FROM_SELECTION_HTP = {987 , 637 , 267 , 67};

//TEAM SELECTION - LOGOS COORD
SDL_Rect Logo_John_Wick = {107 , 193 , 90 , 90};
SDL_Rect Logo_Sans = {227 , 193 , 90 , 90};
SDL_Rect Logo_Batman = {348 , 193 , 90 , 90};
SDL_Rect Logo_Hulk = {475 , 193 , 90 , 90};
SDL_Rect Logo_Snorlax = {595 , 193 , 90 , 90};
SDL_Rect Logo_Demolisher = {717 , 193 , 90 , 90};
SDL_Rect Logo_Lifeline = {844 , 193 , 90 , 90};
SDL_Rect Logo_Dracula = {964 , 193 , 90 , 90};
SDL_Rect Logo_Medic = {1085 , 193 , 90 , 90};
SDL_Rect Left_Key_Logos = {15 , 26 , 57 , 57};
//team 1 
SDL_Rect Team1_Member1 = {34 , 557 , 90 , 90};
SDL_Rect Team1_Member2 = {154 , 557 , 90 , 90};
SDL_Rect Team1_Member3 = {275 , 557 , 90 , 90};
SDL_Rect Team1_Member4 = {396 , 557 , 90 , 90};
SDL_Rect coins1 = {466 , 518 , 76 , 36};
SDL_Rect ready1 = {167 , 667 , 187 , 39};
SDL_Rect yourturn1 = {184 , 357 , 169 , 33};


//team 2
SDL_Rect Team2_Member1 = {785 , 557 , 90 , 90};
SDL_Rect Team2_Member2 = {905 , 557 , 90 , 90};
SDL_Rect Team2_Member3 = {1026 , 557 , 90 , 90};
SDL_Rect Team2_Member4 = {1147 , 557 , 90 , 90};
SDL_Rect coins2 = {690 , 518 , 76 , 36};
SDL_Rect ready2 = {918 , 667 , 187 , 39};
SDL_Rect yourturn2 = {926 , 357 , 169 , 33};


//ERROR MESSAGES
SDL_Rect MessageSelection = {485 ,420 , 310 , 40};

//Stats rendering

SDL_Rect Info_HP = {974 , 193+15 , 106 , 39};
SDL_Rect Info_DMG = {974 , 247+15 , 106 , 39};
SDL_Rect Info_DEF = {974 , 312+15 , 106 , 39};
SDL_Rect Info_DODGE = {974 , 368+15 , 106 , 39};
SDL_Rect Info_SPEED = {974 , 424+15 , 106 , 39};



SDL_Rect Button_SelectPVP = {230 , 472 , 267 , 67};
SDL_Rect Button_SelectPVB = {780 , 472 , 267 , 67};

#endif
