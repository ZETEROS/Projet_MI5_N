#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "lib/buttons-coord.h"

//Dimensions
#define WIDTH 1280
#define HEIGHT 720

//LoadTexture or Images

SDL_Texture* loadTexture(char* path , SDL_Renderer* renderer){
    SDL_Surface* surface = IMG_Load(path);
    if (!surface){
        printf("Image not found.\n");
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer , surface);
    SDL_FreeSurface(surface);
    return texture;

}


int main(){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0 ){
        printf("Error, unable to start SDL.\n%s",SDL_GetError());
        exit(1);
    }
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        printf("Error, unable to start SDL_Image\n%s",IMG_GetError());
        exit(2);
    }
    if ( Mix_OpenAudio(44100 , MIX_DEFAULT_FORMAT , 2 , 2048) < 0){
        printf("Error , couldnt open the mixer.\n%s",Mix_GetError());
        exit(3);
    }

    //Create Window

    SDL_Window* Game = SDL_CreateWindow("Smash&Kill", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT , SDL_WINDOW_SHOWN);
    if (!Game){
        printf("Error, unabler to create the window.\n");
        exit(4);
    }

    //Create Renderer

    SDL_Renderer* render = SDL_CreateRenderer(Game , -1 , SDL_RENDERER_ACCELERATED);
    if(!render){
        printf("Error , unable to create renderer.\n");
        exit(5);
    }


    //GAME RUNNING
    int quit = 0 ;
    SDL_Event event ;

    typedef enum{
        MENU,
        GAMEMODE_SELECTION,
        TEAM_SELECTION,
        FIGHT,
        END_GAME,
        HOW_TO_PLAY,
        
    }Game_State;

    Game_State state = MENU ;

    SDL_Texture* menu_screen = loadTexture("assets/Menu.png", render);
    SDL_Texture* how_to_play_screen = loadTexture("assets/How_to_play.png", render);


    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = 1;
            }
            //Here we manage the input from the player.
            
            switch(state){

                case MENU :
                    SDL_RenderClear(render);
                    SDL_RenderCopy(render , menu_screen , NULL , NULL);
                    SDL_RenderPresent(render);
                    //Clicked?
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                        int x = event.button.x ;
                        int y = event.button.y ;

                        //WHERE?
                        if( x >= Button_PLAY.x && x <= Button_PLAY.x + Button_PLAY.w && y >= Button_PLAY.y && y <= Button_PLAY.y + Button_PLAY.h){
                            //Go to the next part , the GAME MODE SELECTION SCREEN.
                            state = GAMEMODE_SELECTION;
                        }
                        else if( x >= Button_HOWTOPLAY.x && x <= Button_HOWTOPLAY.x + Button_HOWTOPLAY.w && y >= Button_HOWTOPLAY.y && y <= Button_HOWTOPLAY.y + Button_HOWTOPLAY.h){
                            //Go to the next part , the GAME MODE SELECTION SCREEN.
                            state = HOW_TO_PLAY;
                        }
                        else if( x >= Button_EXIT.x && x <= Button_EXIT.x + Button_EXIT.w && y >= Button_EXIT.y && y <= Button_EXIT.y + Button_EXIT.h){
                            //Exit the Game.
                            quit = -1 ;
                        }


                    }


                    break;
                
                case GAMEMODE_SELECTION :
                    quit = -1; //Currently only exiting the game.
                    break;
                
                case TEAM_SELECTION :

                    break;
                
                case FIGHT:

                    break;
                
                case END_GAME:

                    break;
                
                case HOW_TO_PLAY:
                    SDL_RenderClear(render);
                    SDL_RenderCopy(render , how_to_play_screen , NULL , NULL);
                    SDL_RenderPresent(render);
                    break;

            }

        }
        

    }


}