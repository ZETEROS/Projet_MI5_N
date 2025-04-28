#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "lib/structure.h"
#include "lib/buttons-coord.h"
#include "lib/special_attacks_list.h"
#include "lib/renderingfonctions.h"

//Dimensions
#define WIDTH 1280
#define HEIGHT 720

int coins_giver(){
    int coins = 100 + rand() % 101 ;
    return coins; 
}



int main(int argc , char** argv){
    (void)argc;
    (void)argv;
    //STARTING SDL
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
    if (TTF_Init() == -1) {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
        exit(1);
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

    //
    srand(time(NULL));

    //GAME RUNNING
    int quit = 0 ;
    SDL_Event event ;

    //GAME STATES (MOMENTS)
    typedef enum{
        MENU,
        GAMEMODE_SELECTION,
        TEAM_SELECTION,
        FIGHT,
        END_GAME,
        HOW_TO_PLAY,
        
    }Game_State;

    //ALWAYS START IN THE MENU
    Game_State state = MENU ;


    //SCREENS , OBJECTS AND SOUND TO RENDER OR REPRODUCE
    SDL_Texture* menu_screen = loadTexture("assets/menu.png", render);
    SDL_Texture* how_to_play_screen = loadTexture("assets/how_to_play.png", render);
    SDL_Texture* gamemode_screen = loadTexture("assets/gamemode_selection.png", render);
    SDL_Texture* teamselection_screen= loadTexture("assets/team_selection.png", render);
    SDL_Texture* blink_turn= loadTexture("assets/yourturn.png", render);
    SDL_Texture* ready_pressed= loadTexture("assets/readypressed.png", render);
    SDL_Texture* Info_JohnWick = loadTexture("assets/Info_JohnWick.png", render);
    SDL_Texture* Info_Sans = loadTexture("assets/Info_Sans.png", render);
    SDL_Texture* Info_Batman = loadTexture("assets/Info_Batman.png", render);
    SDL_Texture* Info_Hulk = loadTexture("assets/Info_Hulk.png", render);
    SDL_Texture* Info_Snorlax = loadTexture("assets/Info_Snorlax.png", render);
    SDL_Texture* Info_Demolisher = loadTexture("assets/Info_Demolisher.png", render);
    SDL_Texture* Info_Lifeline = loadTexture("assets/Info_Lifeline.png", render);
    SDL_Texture* Info_Dracula = loadTexture("assets/Info_Dracula.png", render);
    SDL_Texture* Info_Medic = loadTexture("assets/Info_Medic.png", render);
    SDL_Texture* Square_JohnWick = loadTexture("assets/Logos/Logo_JohnWick.png", render);
    SDL_Texture* Square_Sans = loadTexture("assets/Logos/Logo_Sans.png", render);
    SDL_Texture* Square_Batman = loadTexture("assets/Logos/Logo_Batman.png", render);
    SDL_Texture* Square_Hulk = loadTexture("assets/Logos/Logo_Hulk.png", render);
    SDL_Texture* Square_Snorlax = loadTexture("assets/Logos/Logo_Snorlax.png", render);
    SDL_Texture* Square_Demolisher = loadTexture("assets/Logos/Logo_Demolisher.png", render);
    SDL_Texture* Square_Lifeline = loadTexture("assets/Logos/Logo_Lifeline.png", render);
    SDL_Texture* Square_Dracula = loadTexture("assets/Logos/Logo_Dracula.png", render);
    SDL_Texture* Square_Medic = loadTexture("assets/Logos/Logo_Medic.png", render);

    Mix_Chunk* select_sound = Mix_LoadWAV("assets/select.ogg");
    Mix_Chunk* tick_sound = Mix_LoadWAV("assets/tick.ogg");
    Mix_Chunk* back_sound = Mix_LoadWAV("assets/back.ogg");
    Mix_Music* menu_music = Mix_LoadMUS("assets/Stray_Cat.ogg");
    Mix_Music* combat_music = Mix_LoadMUS("assets/The_Trial.ogg");

    Fighter John_Wick = importandassign("Fighters/John_Wick");
    Fighter Sans = importandassign("Fighters/Sans");
    Fighter Batman = importandassign("Fighters/Batman");
    Fighter Hulk = importandassign("Fighters/Hulk");
    Fighter Snorlax = importandassign("Fighters/Snorlax");
    Fighter Demolisher = importandassign("Fighters/Demolisher");
    Fighter Lifeline = importandassign("Fighters/Lifeline");
    Fighter Dracula = importandassign("Fighters/Dracula");
    Fighter Medic = importandassign("Fighters/The_Medic");
    

    //Initial Values 
    int currentMusic = -1 ; // 0 : menu , 1 : fight music , -1 : none 
    int current_team = 1;
    int team1_coins = 0;
    int team2_coins = 0;
    int members_team1 = 0;
    int members_team2 = 0;
    //TEAMS IN SELECTION PHASE , ALL UN-SELECTED HERE
    Fighter PRETEAM1[9] = {John_Wick , Sans , Batman , Hulk , Snorlax , Demolisher , Lifeline , Dracula , Medic};
    Fighter PRETEAM2[9] = {John_Wick , Sans , Batman , Hulk , Snorlax , Demolisher , Lifeline , Dracula , Medic};

    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = 1;
            }
            //Here we manage the input from the player and render in the window everything.
            
            switch(state){

                case MENU :
                    SDL_RenderClear(render);
                    SDL_RenderCopy(render , menu_screen , NULL , NULL);
                    SDL_RenderPresent(render);
                    //music ON:
                    if(currentMusic != 0){
                        Mix_HaltMusic();
                        Mix_FadeInMusic(menu_music,-1 , 6000);
                        currentMusic = 0;
                    }
                    //Clicked?
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                        int x = event.button.x ;
                        int y = event.button.y ;

                        //WHERE?
                        if( x >= Button_START.x && x <= Button_START.x + Button_START.w && y >= Button_START.y && y <= Button_START.y + Button_START.h){
                            //Go to the next part , the GAME MODE SELECTION SCREEN.
                            Mix_PlayChannel(-1 , select_sound , 0);
                            state = GAMEMODE_SELECTION;
                        }
                        else if( x >= Button_HOWTOPLAY.x && x <= Button_HOWTOPLAY.x + Button_HOWTOPLAY.w && y >= Button_HOWTOPLAY.y && y <= Button_HOWTOPLAY.y + Button_HOWTOPLAY.h){
                            //Go to the next part , the GAME MODE SELECTION SCREEN.
                            Mix_PlayChannel(-1 , select_sound , 0);                            
                            state = HOW_TO_PLAY;
                        }
                        else if( x >= Button_QUIT.x && x <= Button_QUIT.x + Button_QUIT.w && y >= Button_QUIT.y && y <= Button_QUIT.y + Button_QUIT.h){
                            //Exit the Game.
                            Mix_PlayChannel(-1 , select_sound , 0);
                            quit = -1 ;
                        }


                    }


                    break;
                
                case GAMEMODE_SELECTION :
                    SDL_RenderClear(render);
                    SDL_RenderCopy(render , gamemode_screen , NULL , NULL);
                    SDL_RenderPresent(render);
                    //Music on?
                    if(currentMusic != 0){
                        Mix_HaltMusic();
                        Mix_FadeInMusic(menu_music,-1 , 3000);
                        currentMusic = 0;
                    }
                    //Clicked?
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                        int x = event.button.x ;
                        int y = event.button.y ;

                        //WHERE?
                        if( x >= Button_SelectPVP.x && x <= Button_SelectPVP.x + Button_SelectPVP.w && y >= Button_SelectPVP.y && y <= Button_SelectPVP.y + Button_SelectPVP.h){
                            //Go to the next part , the TEAM SELECTION SCREEN.
                            Mix_PlayChannel(-1 , select_sound , 0);
                            state = TEAM_SELECTION;
                        }
                        else if( x >= Button_SelectPVB.x && x <= Button_SelectPVB.x + Button_SelectPVB.w && y >= Button_SelectPVB.y && y <= Button_SelectPVB.y + Button_SelectPVB.h){
                            //Go to the next part , the TEAM SELECTION SCREEN.
                            Mix_PlayChannel(-1 , select_sound , 0);
                            state = TEAM_SELECTION;
                        }
                        else if( x >= Button_MAINMENU_FROM_SELECTION_HTP.x && x <= Button_MAINMENU_FROM_SELECTION_HTP.x + Button_MAINMENU_FROM_SELECTION_HTP.w && y >= Button_MAINMENU_FROM_SELECTION_HTP.y && y <= Button_MAINMENU_FROM_SELECTION_HTP.y + Button_MAINMENU_FROM_SELECTION_HTP.h){
                            Mix_PlayChannel(-1 , back_sound , 0);
                            state = MENU;
                        }



                    }

                    break;
                
                case TEAM_SELECTION :

                    //Fighting music on:
                    if(currentMusic != 1){
                        Mix_HaltMusic();
                        Mix_FadeInMusic(combat_music,-1 , 5000);
                        //Mix_PlayMusic(combat_music , -1);
                        currentMusic = 1;
                    }
                    SDL_Color dark_gray = { 70 , 70 , 70};

                    if(team1_coins == 0 && team2_coins == 0){
                        team1_coins = coins_giver();
                        team2_coins = coins_giver();
                    }
                    if(current_team == 1){
                        SDL_RenderClear(render);
                        SDL_RenderCopy(render , teamselection_screen , NULL , NULL);
                        rendercoins(render , team1_coins , &coins1 , 40 , dark_gray);
                        SDL_RenderCopy(render , blink_turn , NULL , &yourturn1);
                        SDL_RenderPresent(render);
                        //Clicked?
                        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                            int x = event.button.x ;
                            int y = event.button.y ;


                            //WHERE?
                            if( x >= Left_Key_Logos.x && x <= Left_Key_Logos.x + Left_Key_Logos.w && y >= Left_Key_Logos.y && y <= Left_Key_Logos.y + Left_Key_Logos.h){
                                Mix_PlayChannel(-1 , back_sound , 0);
                                state = GAMEMODE_SELECTION;
                            }
                            else if( x >= ready1.x && x <= ready1.x + ready1.w && y >= ready1.y && y <= ready1.y + ready1.h){
                                
                                Mix_PlayChannel(-1 , select_sound , 0);
                                SDL_RenderCopy(render , ready_pressed , NULL , &ready1);
                                SDL_RenderPresent(render);
                                current_team = 2;
                            }
                            else if( x >= Logo_John_Wick.x && x <= Logo_John_Wick.x + Logo_John_Wick.w && y >= Logo_John_Wick.y && y <= Logo_John_Wick.y + Logo_John_Wick.h){
  /*NEED TO CHECK*/                              if(howmanyselected(PRETEAM1) < 4 && howmanyselected(PRETEAM1)){
                                    if(PRETEAM1[0].selected == 0){
                                        PRETEAM1[0].selected = 1 ;
                                    }
                                    else if(PRETEAM1[0].selected == 1){
                                        PRETEAM1[0].selected = 0;
                                    }
                                }
                                else{
                                    rendermessageTEMP("You need to pick 2 to 4 fighters" , &MessageSelection , render , 2000);
                                }
                                

                            }



                        }
                        //Right Clicked?
                        else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT){
                            int x = event.button.x ;
                            int y = event.button.y ;
                            //Where?
                            if( x >= Logo_John_Wick.x && x <= Logo_John_Wick.x + Logo_John_Wick.w && y >= Logo_John_Wick.y && y <= Logo_John_Wick.y + Logo_John_Wick.h){
                                showinfoandstats(render , Info_JohnWick , &John_Wick, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Sans.x && x <= Logo_Sans.x + Logo_Sans.w && y >= Logo_Sans.y && y <= Logo_Sans.y + Logo_Sans.h){
                                showinfoandstats(render , Info_Sans , &Sans, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Batman.x && x <= Logo_Batman.x + Logo_Batman.w && y >= Logo_Batman.y && y <= Logo_Batman.y + Logo_Batman.h){
                                showinfoandstats(render , Info_Batman , &Batman, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Hulk.x && x <= Logo_Hulk.x + Logo_Hulk.w && y >= Logo_Hulk.y && y <= Logo_Hulk.y + Logo_Hulk.h){
                                showinfoandstats(render , Info_Hulk , &Hulk, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Snorlax.x && x <= Logo_Snorlax.x + Logo_Snorlax.w && y >= Logo_Snorlax.y && y <= Logo_Snorlax.y + Logo_Snorlax.h){
                                showinfoandstats(render , Info_Snorlax , &Snorlax, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Demolisher.x && x <= Logo_Demolisher.x + Logo_Demolisher.w && y >= Logo_Demolisher.y && y <= Logo_Demolisher.y + Logo_Demolisher.h){
                                showinfoandstats(render , Info_Demolisher , &Demolisher, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Lifeline.x && x <= Logo_Lifeline.x + Logo_Lifeline.w && y >= Logo_Lifeline.y && y <= Logo_Lifeline.y + Logo_Lifeline.h){
                                showinfoandstats(render , Info_Lifeline , &Lifeline, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Dracula.x && x <= Logo_Dracula.x + Logo_Dracula.w && y >= Logo_Dracula.y && y <= Logo_Dracula.y + Logo_Dracula.h){
                                showinfoandstats(render , Info_Dracula , &Dracula, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Medic.x && x <= Logo_Medic.x + Logo_Medic.w && y >= Logo_Medic.y && y <= Logo_Medic.y + Logo_Medic.h){
                                showinfoandstats(render , Info_Medic , &Medic, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }

                            
                            
                            
                        }
                    }
                    if(current_team == 2){
                        SDL_RenderClear(render);
                        SDL_RenderCopy(render , teamselection_screen , NULL , NULL);
                        rendercoins(render , team1_coins , &coins1 , 40 , dark_gray);
                        rendercoins(render , team2_coins , &coins2 , 40 , dark_gray);
                        SDL_RenderCopy(render , blink_turn , NULL , &yourturn2);
                        SDL_RenderCopy(render , ready_pressed , NULL ,&ready1);
                        SDL_RenderPresent(render);

                        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                            int x = event.button.x ;
                            int y = event.button.y ;


                            //WHERE?
                            if( x >= Left_Key_Logos.x && x <= Left_Key_Logos.x + Left_Key_Logos.w && y >= Left_Key_Logos.y && y <= Left_Key_Logos.y + Left_Key_Logos.h){
                                Mix_PlayChannel(-1 , back_sound , 0);
                                current_team = 1;
                                state = GAMEMODE_SELECTION;
                            }
                            else if( x >= ready2.x && x <= ready2.x + ready2.w && y >= ready2.y && y <= ready2.y + ready2.h){
                                Mix_PlayChannel(-1 , select_sound , 0);
                                SDL_RenderClear(render);
                                SDL_RenderCopy(render , teamselection_screen , NULL , NULL);
                                SDL_RenderCopy(render , blink_turn , NULL , &yourturn2);
                                SDL_RenderCopy(render , ready_pressed , NULL ,&ready1);
                                SDL_RenderCopy(render , ready_pressed , NULL , &ready2);
                                SDL_RenderPresent(render);
                                current_team = 1;
                                state= FIGHT;
                            }



                        }
                        //Right Clicked?
                        else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT){
                            int x = event.button.x ;
                            int y = event.button.y ;
                            //Where?
                            if( x >= Logo_John_Wick.x && x <= Logo_John_Wick.x + Logo_John_Wick.w && y >= Logo_John_Wick.y && y <= Logo_John_Wick.y + Logo_John_Wick.h){
                                showinfoandstats(render , Info_JohnWick , &John_Wick, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Sans.x && x <= Logo_Sans.x + Logo_Sans.w && y >= Logo_Sans.y && y <= Logo_Sans.y + Logo_Sans.h){
                                showinfoandstats(render , Info_Sans , &Sans, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Batman.x && x <= Logo_Batman.x + Logo_Batman.w && y >= Logo_Batman.y && y <= Logo_Batman.y + Logo_Batman.h){
                                showinfoandstats(render , Info_Batman , &Batman, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Hulk.x && x <= Logo_Hulk.x + Logo_Hulk.w && y >= Logo_Hulk.y && y <= Logo_Hulk.y + Logo_Hulk.h){
                                showinfoandstats(render , Info_Hulk , &Hulk, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Snorlax.x && x <= Logo_Snorlax.x + Logo_Snorlax.w && y >= Logo_Snorlax.y && y <= Logo_Snorlax.y + Logo_Snorlax.h){
                                showinfoandstats(render , Info_Snorlax , &Snorlax, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Demolisher.x && x <= Logo_Demolisher.x + Logo_Demolisher.w && y >= Logo_Demolisher.y && y <= Logo_Demolisher.y + Logo_Demolisher.h){
                                showinfoandstats(render , Info_Demolisher , &Demolisher, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Lifeline.x && x <= Logo_Lifeline.x + Logo_Lifeline.w && y >= Logo_Lifeline.y && y <= Logo_Lifeline.y + Logo_Lifeline.h){
                                showinfoandstats(render , Info_Lifeline , &Lifeline, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Dracula.x && x <= Logo_Dracula.x + Logo_Dracula.w && y >= Logo_Dracula.y && y <= Logo_Dracula.y + Logo_Dracula.h){
                                showinfoandstats(render , Info_Dracula , &Dracula, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }
                            else if(x >= Logo_Medic.x && x <= Logo_Medic.x + Logo_Medic.w && y >= Logo_Medic.y && y <= Logo_Medic.y + Logo_Medic.h){
                                showinfoandstats(render , Info_Medic , &Medic, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team);
                            }

                    }

                    break;
                
                case FIGHT:
                    state = GAMEMODE_SELECTION;
                    break;
                
                case END_GAME:

                    break;
                
                case HOW_TO_PLAY:
                    SDL_RenderClear(render);
                    SDL_RenderCopy(render , how_to_play_screen , NULL , NULL);
                    SDL_RenderPresent(render);
                    //Music on?
                    if(currentMusic != 0){
                        Mix_HaltMusic();
                        Mix_FadeInMusic(menu_music,-1 , 3000);
                        currentMusic = 0;
                    }
                    //CLICKED?
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                        int x = event.button.x ;
                        int y = event.button.y ;
                        //WHERE?
                        if( x >= Button_MAINMENU_FROM_SELECTION_HTP.x && x <= Button_MAINMENU_FROM_SELECTION_HTP.x + Button_MAINMENU_FROM_SELECTION_HTP.w && y >= Button_MAINMENU_FROM_SELECTION_HTP.y && y <= Button_MAINMENU_FROM_SELECTION_HTP.y + Button_MAINMENU_FROM_SELECTION_HTP.h){
                            Mix_PlayChannel(-1 , back_sound , 0);
                            state = MENU;
                        }

                    }

                    break;

            }

        }
        

    }


    }
}