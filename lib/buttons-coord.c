#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>



SDL_Rect Button_START = {509 , 404 , 259 , 55};
SDL_Rect Button_HOWTOPLAY = {509 , 478 , 259 , 55};
SDL_Rect Button_QUIT = {509 , 553 , 259 , 55};
SDL_Rect Button_MAINMENU_FROM_SELECTION_HTP = {987 , 637 , 267 , 67};
SDL_Rect Fire1 ={145 , 244-(24*10) ,15 , 24 };
SDL_Rect Fire2 ={964 , 244-(24*10) ,15 , 24 };

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


//PRICES POSITIONS
SDL_Rect Price_John_Wick= {111+30 , 156 , 32 , 32};
SDL_Rect Price_Sans = {230+30 , 156 , 32 , 32};
SDL_Rect Price_Batman = {351+30 , 156 , 32 , 32};
SDL_Rect Price_Hulk = {479+30 , 156 , 32 , 32};
SDL_Rect Price_Snorlax = {597+30 , 156 , 32 , 32};
SDL_Rect Price_Demolisher = {718+30 , 156 , 32 , 32};
SDL_Rect Price_Lifeline = {847+30 , 156 , 32 , 32};
SDL_Rect Price_Dracula = {966+30 , 156 , 32 , 32};
SDL_Rect Price_The_Medic = {1088+30 , 156 , 32 , 32};



SDL_Rect Button_SelectPVP = {230 , 472 , 267 , 67};
//SDL_Rect Button_SelectPVB = {780 , 472 , 267 , 67};


//ERROR MESSAGES
SDL_Rect MessageSelection = {485 ,420 , 310 , 40};

//Stats rendering

SDL_Rect Info_HP = {974 , 193+15 , 106 , 39};
SDL_Rect Info_DMG = {974 , 247+15 , 106 , 39};
SDL_Rect Info_DEF = {974 , 312+15 , 106 , 39};
SDL_Rect Info_DODGE = {974 , 368+15 , 106 , 39};
SDL_Rect Info_SPEED = {974 , 424+15 , 106 , 39};


//FIGHT
//Modification size || Resolution native of the models is 105 * 165 px.
const int my = 40;
const int mx = 40;
SDL_Rect Team1_Fighter1 = { 310 , 325-my , 105+mx , 165+my};
SDL_Rect Team1_Fighter2 = { 290 , 541-my , 105+mx , 165+my};
SDL_Rect Team1_Fighter3 = { 177 , 408-my , 105+mx , 165+my};
SDL_Rect Team1_Fighter4 = { 39, 491-my , 105+mx , 165+my};

SDL_Rect Team2_Fighter1 = {865 ,325-my , 105+mx , 165+my};
SDL_Rect Team2_Fighter2= { 885 , 541-my , 105+mx , 165+my};
SDL_Rect Team2_Fighter3 = { 998 , 408-my , 105+mx , 165+my};
SDL_Rect Team2_Fighter4 = { 1136 , 491-my , 105+mx , 165+my};

SDL_Rect Pause_button = {1280/2-262/2 , 10 , 262 , 59};
SDL_Rect Continue_button_pause= {509 , 260 , 255 , 50};
SDL_Rect Menu_button_pause= {509 , 339 , 255 , 50};
SDL_Rect Quit_button_pause= {509 , 418 , 255 , 50};

SDL_Rect fight_torch1 = {263 , 172-24 , 15 , 24};
SDL_Rect fight_torch2 = {477 , 172-24 , 15 , 24};
SDL_Rect fight_torch3 = {787 , 172-24 , 15 , 24};
SDL_Rect fight_torch4 = {1002 , 172-24 , 15 , 24};

SDL_Rect Basic_Attack = {467 , 594 , 110 , 106};
SDL_Rect Special_Attack = {586 , 594 , 110 , 106};
//SDL_Rect Ultimate_Attack = {644 , 594 , 110 , 106};
SDL_Rect No_Attack = {707 , 594 , 110 , 106};

SDL_Rect ATTACK_BUTTON = {585 , 642 , 108 , 78};

SDL_Rect Coin_ammount = {1100 , 110 , 47 , 28};

SDL_Rect hitordodge = { 889 , 122 , 165 , 21};

//END GAME

SDL_Rect Main_Menu_Button_From_EndGame = {20 , 24 , 260 , 55};
SDL_Rect END_GAME_Fighter1 = { 328 ,459 , 105 , 165};
SDL_Rect END_GAME_Fighter2 = { 473 , 459, 105 , 165};
SDL_Rect END_GAME_Fighter3 = { 703 , 459, 105 , 165};
SDL_Rect END_GAME_Fighter4 = { 847, 459, 105 , 165};

