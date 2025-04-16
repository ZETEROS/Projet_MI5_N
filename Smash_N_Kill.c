#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

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

    //Create Window

    SDL_Window* Game = SDL_CreateWindow("Smash&Kill", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT , SDL_WINDOW_SHOWN);
    if (!Game){
        printf("Error, unabler to create the window.\n");
        exit(3);
    }

    //Create Renderer

    SDL_Renderer* render = SDL_CreateRenderer(Game , -1 , SDL_RENDERER_ACCELERATED);
    if(!render){
        printf("Error , unable to create renderer.\n");
        exit(4);
    }

    SDL_Texture* menu = loadTexture("assets/Menu.png", render);

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
        EXIT
    }Game_State;

    Game_State state = MENU ;

    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = 1;
            }
            //Here we manage the input from the player.
            
            switch(state){

                case MENU :
                    SDL_RenderClear(render);
                    SDL_RenderCopy(render , menu , NULL , NULL);
                    SDL_RenderPresent(render);
                    break;
                
                case GAMEMODE_SELECTION :

                    break;
                
                case TEAM_SELECTION :

                    break;
                
                case FIGHT:

                    break;
                
                case END_GAME:

                    break;
                
                case HOW_TO_PLAY:

                    break;
                
                case EXIT:
                    quit = 1;
                    break;

            }

        }
        

    }


}