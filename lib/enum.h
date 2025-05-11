#ifndef ENUM_H
#define ENUM_H
#include <stdio.h>

typedef enum{
        SELECTING_FIGHTER,
        PAUSE,
        SELECTING_ATTACK,
        SELECTING_TARGET,
}Fight_State;

typedef enum{
    BASIC_ATTACK ,
    SPECIAL_ATTACK,
    ULTIMATE_ATTACK,
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

#endif



