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

    //CLEAR PIXELS
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

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

    typedef enum{
        IN_FIGHT,
        PAUSE,
        SELECTING,
    }Fight_State;

    //ALWAYS START IN THE MENU
    Game_State state = MENU ;

    Fight_State fight = IN_FIGHT;


    //SCREENS , OBJECTS AND SOUND TO RENDER OR REPRODUCE
    SDL_Texture* menu_screen = loadTexture("assets/menu.png", render);
    SDL_Texture* how_to_play_screen = loadTexture("assets/how_to_play.png", render);
    SDL_Texture* gamemode_screen = loadTexture("assets/gamemode_selection.png", render);
    SDL_Texture* teamselection_screen= loadTexture("assets/team_selection.png", render);
    SDL_Texture* fight_scenario = loadTexture("assets/fight/map2_2.0.png" , render);
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
    SDL_Texture* All_Logos[9] = {Square_JohnWick , Square_Sans , Square_Batman , Square_Hulk , Square_Snorlax , Square_Demolisher , Square_Lifeline , Square_Dracula , Square_Medic};
    SDL_Texture* fire_animation = loadTexture("assets/anim/burning_loop_3.png", render);
    SDL_Color dark_gray = { 70 , 70 , 70};
    SDL_Texture* visuals[9] = {loadTexture("assets/anim/John_Wick_model_idle.png" , render) , loadTexture("assets/anim/Sans_model_idle.png" ,render  ) , loadTexture( "assets/anim/Batman_model_idle.png",  render) , loadTexture( "assets/anim/Hulk_model_idle.png", render ) ,loadTexture( "assets/anim/Snorlax_model_idle.png", render ) ,loadTexture( "assets/anim/Demolisher_model_idle.png", render ) ,loadTexture( "assets/anim/Lifeline_model_idle.png", render ) ,loadTexture( "assets/anim/Dracula_model_idle.png", render ) ,loadTexture( "assets/anim/Medic_model_idle.png", render ) };
    SDL_Texture* visuals_selected[9] = {loadTexture("assets/anim/John_Wick_model_idle_selected.png" , render) , loadTexture("assets/anim/Sans_model_idle_selected.png" ,render  ) , loadTexture( "assets/anim/Batman_model_idle_selected.png",  render) , loadTexture( "assets/anim/Hulk_model_idle_selected.png", render ) ,loadTexture( "assets/anim/Snorlax_model_idle_selected.png", render ) ,loadTexture( "assets/anim/Demolisher_model_idle_selected.png", render ) ,loadTexture( "assets/anim/Lifeline_model_idle_selected.png", render ) ,loadTexture( "assets/anim/Dracula_model_idle_selected.png", render ) ,loadTexture( "assets/anim/Medic_model_idle_selected.png", render ) };
    SDL_Texture* Pause_button_texture = loadTexture("assets/fight/pause.png", render);
    SDL_Texture* Paused_ui = loadTexture("assets/fight/pauseui.png", render);
    SDL_Texture* torches = loadTexture("assets/2torches.png" , render);
    SDL_Texture* fight_torches_texture = loadTexture("assets/fight/torches_fight.png" , render);

    TTF_Font* font = TTF_OpenFont("assets/pixel_font.ttf", 40);
    if(!font){
        printf("Error , unable to load the font || START || : %s", TTF_GetError());
        exit(10);
    }

    Mix_Chunk* select_sound = Mix_LoadWAV("assets/select.ogg");
    Mix_Chunk* tick_sound = Mix_LoadWAV("assets/tick.ogg");
    Mix_Chunk* back_sound = Mix_LoadWAV("assets/back.ogg");
    Mix_Music* menu_music = Mix_LoadMUS("assets/Stray_Cat.ogg");
    Mix_Music* selection_music = Mix_LoadMUS("assets/The_Trial.ogg");
    Mix_Music* fighting_music = Mix_LoadMUS("assets/Point_Zero.ogg");

    //FIGHTERS TEAM 2
    Fighter John_Wick1 = importandassign("Fighters/John_Wick" , visuals , visuals_selected);
    Fighter Sans1 = importandassign("Fighters/Sans", visuals, visuals_selected);
    Fighter Batman1 = importandassign("Fighters/Batman", visuals, visuals_selected);
    Fighter Hulk1 = importandassign("Fighters/Hulk", visuals, visuals_selected);
    Fighter Snorlax1 = importandassign("Fighters/Snorlax", visuals, visuals_selected);
    Fighter Demolisher1 = importandassign("Fighters/Demolisher", visuals, visuals_selected);
    Fighter Lifeline1 = importandassign("Fighters/Lifeline", visuals, visuals_selected);
    Fighter Dracula1 = importandassign("Fighters/Dracula", visuals, visuals_selected);
    Fighter Medic1 = importandassign("Fighters/The_Medic", visuals, visuals_selected);

    //FIGHTERS TEAM 2
    Fighter John_Wick2 = importandassign("Fighters/John_Wick", visuals, visuals_selected);
    Fighter Sans2 = importandassign("Fighters/Sans", visuals, visuals_selected);
    Fighter Batman2 = importandassign("Fighters/Batman", visuals, visuals_selected);
    Fighter Hulk2 = importandassign("Fighters/Hulk", visuals, visuals_selected);
    Fighter Snorlax2 = importandassign("Fighters/Snorlax", visuals, visuals_selected);
    Fighter Demolisher2 = importandassign("Fighters/Demolisher", visuals, visuals_selected);
    Fighter Lifeline2 = importandassign("Fighters/Lifeline", visuals, visuals_selected);
    Fighter Dracula2 = importandassign("Fighters/Dracula", visuals, visuals_selected);
    Fighter Medic2 = importandassign("Fighters/The_Medic", visuals, visuals_selected);
    

    //Initial Values 
    int currentMusic = -1 ; // 0 : menu , 1 : selection music , 2: fighting music , -1 : none 
    //Which team needs to choose its fighters?
    int current_team ;
    //Amount of coins team1 has
    int team1_coins ;
    //Amount of coins team2 has
    int team2_coins ;
    
    //finished selecting fighters:
    int selecting_team1 ;
    int selecting_team2 ;

    //ERROR MESSAGE
    int error_message_1 = 0;
    //TEAMS IN SELECTION PHASE , ALL UN-SELECTED HERE
    Fighter* PRETEAM1[9] = {&John_Wick1 , &Sans1 , &Batman1 , &Hulk1 , &Snorlax1 , &Demolisher1 , &Lifeline1 , &Dracula1 , &Medic1};
    Fighter* PRETEAM2[9] = {&John_Wick2 , &Sans2 , &Batman2 , &Hulk2 , &Snorlax2 , &Demolisher2 , &Lifeline2 , &Dracula2 , &Medic2};

    //are the final teams made already or not? 0 is NO , 1 is yes .
    int team1_made = 0;
    int team2_made = 0;

    Fighter* team1 = NULL;
    Fighter* team2= NULL;


   
    while(!quit){
        while(SDL_PollEvent(&event)){
            
                if(event.type == SDL_QUIT){
                    quit = 1;
                }
                //Here we manage the input from the player and render in the window everything.
                
                switch(state){

                    case MENU :

                        if(team1_coins != 0 && team2_coins != 0){
                           
                            team1_coins = 0;
                            team2_coins = 0;
                        }

                        selecting_team1 = 0;
                        selecting_team2 = 0;

                        current_team = 1;
                        
                        //music ON:
                        if(currentMusic != 0){
                            Mix_HaltMusic();
                            Mix_VolumeMusic(MIX_MAX_VOLUME * 0.8);
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

                    case END_GAME:

                        break;
                    
                    case HOW_TO_PLAY:
                        
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
                    
                    case GAMEMODE_SELECTION :
                       
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

                        //Selection music on:
                        if(currentMusic != 1){
                            Mix_HaltMusic();
                            Mix_FadeInMusic(selection_music,-1 , 5000);
                            //Mix_PlayMusic(combat_music , -1);
                            currentMusic = 1;
                        }
                        

                        if(team1_coins == 0 && team2_coins == 0){
                            int coins_temp = coins_giver();
                            team1_coins = coins_temp;
                            team2_coins = coins_temp;
                        }
                        if(current_team == 1){
                            
                            //Clicked?
                            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                                int x = event.button.x ;
                                int y = event.button.y ;


                                //WHERE?
                                if( x >= Left_Key_Logos.x && x <= Left_Key_Logos.x + Left_Key_Logos.w && y >= Left_Key_Logos.y && y <= Left_Key_Logos.y + Left_Key_Logos.h){
                                    Mix_PlayChannel(-1 , back_sound , 0);
                                    unselectallfighters(PRETEAM1 , PRETEAM2);
                                    state = GAMEMODE_SELECTION;
                                }
                                else if( x >= ready1.x && x <= ready1.x + ready1.w && y >= ready1.y && y <= ready1.y + ready1.h){
                                    if(howmanyselected(PRETEAM1) <= 4 && howmanyselected(PRETEAM1) >= 2){
                                        
                                        Mix_PlayChannel(-1 , select_sound , 0);
                                        selecting_team1 = 1;
                                        
                                    }
                                    else{
                                        if(howmanyselected(PRETEAM1) < 2){
                                            Mix_PlayChannel(-1 , tick_sound , 0);
                                            error_message_1 = 1;
                                            
                                        }
                                        
                                    }
                                    
                                }
                                else if( x >= Logo_John_Wick.x && x <= Logo_John_Wick.x + Logo_John_Wick.w && y >= Logo_John_Wick.y && y <= Logo_John_Wick.y + Logo_John_Wick.h){
    /*NEED TO CHECK*/             addorkickfromteam(PRETEAM1 , render , 0 , font);
                                }
                                else if(x >= Logo_Sans.x && x <= Logo_Sans.x + Logo_Sans.w && y >= Logo_Sans.y && y <= Logo_Sans.y + Logo_Sans.h){
                                    addorkickfromteam(PRETEAM1 , render , 1 , font);
                                }
                                else if(x >= Logo_Batman.x && x <= Logo_Batman.x + Logo_Batman.w && y >= Logo_Batman.y && y <= Logo_Batman.y + Logo_Batman.h){
                                    addorkickfromteam(PRETEAM1 , render , 2 , font);
                                }
                                else if(x >= Logo_Hulk.x && x <= Logo_Hulk.x + Logo_Hulk.w && y >= Logo_Hulk.y && y <= Logo_Hulk.y + Logo_Hulk.h){
                                    addorkickfromteam(PRETEAM1 , render , 3 , font);
                                }
                                else if(x >= Logo_Snorlax.x && x <= Logo_Snorlax.x + Logo_Snorlax.w && y >= Logo_Snorlax.y && y <= Logo_Snorlax.y + Logo_Snorlax.h){
                                    addorkickfromteam(PRETEAM1 , render , 4 , font);
                                }
                                else if(x >= Logo_Demolisher.x && x <= Logo_Demolisher.x + Logo_Demolisher.w && y >= Logo_Demolisher.y && y <= Logo_Demolisher.y + Logo_Demolisher.h){
                                    addorkickfromteam(PRETEAM1 , render , 5 , font);
                                }
                                else if(x >= Logo_Lifeline.x && x <= Logo_Lifeline.x + Logo_Lifeline.w && y >= Logo_Lifeline.y && y <= Logo_Lifeline.y + Logo_Lifeline.h){
                                    addorkickfromteam(PRETEAM1 , render , 6 , font);
                                }
                                else if(x >= Logo_Dracula.x && x <= Logo_Dracula.x + Logo_Dracula.w && y >= Logo_Dracula.y && y <= Logo_Dracula.y + Logo_Dracula.h){
                                    addorkickfromteam(PRETEAM1 , render , 7 , font);
                                }
                                else if(x >= Logo_Medic.x && x <= Logo_Medic.x + Logo_Medic.w && y >= Logo_Medic.y && y <= Logo_Medic.y + Logo_Medic.h){
                                    addorkickfromteam(PRETEAM1 , render , 8 , font);
                                }



                            }
                            //Right Clicked?
                            else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT){
                                int x = event.button.x ;
                                int y = event.button.y ;
                                //Where?
                                if( x >= Logo_John_Wick.x && x <= Logo_John_Wick.x + Logo_John_Wick.w && y >= Logo_John_Wick.y && y <= Logo_John_Wick.y + Logo_John_Wick.h){
                                    showinfoandstats(render , Info_JohnWick , &John_Wick1, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team , font);
                                }
                                else if(x >= Logo_Sans.x && x <= Logo_Sans.x + Logo_Sans.w && y >= Logo_Sans.y && y <= Logo_Sans.y + Logo_Sans.h){
                                    showinfoandstats(render , Info_Sans , &Sans1, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Batman.x && x <= Logo_Batman.x + Logo_Batman.w && y >= Logo_Batman.y && y <= Logo_Batman.y + Logo_Batman.h){
                                    showinfoandstats(render , Info_Batman , &Batman1, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Hulk.x && x <= Logo_Hulk.x + Logo_Hulk.w && y >= Logo_Hulk.y && y <= Logo_Hulk.y + Logo_Hulk.h){
                                    showinfoandstats(render , Info_Hulk , &Hulk1, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Snorlax.x && x <= Logo_Snorlax.x + Logo_Snorlax.w && y >= Logo_Snorlax.y && y <= Logo_Snorlax.y + Logo_Snorlax.h){
                                    showinfoandstats(render , Info_Snorlax , &Snorlax1, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Demolisher.x && x <= Logo_Demolisher.x + Logo_Demolisher.w && y >= Logo_Demolisher.y && y <= Logo_Demolisher.y + Logo_Demolisher.h){
                                    showinfoandstats(render , Info_Demolisher , &Demolisher1, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Lifeline.x && x <= Logo_Lifeline.x + Logo_Lifeline.w && y >= Logo_Lifeline.y && y <= Logo_Lifeline.y + Logo_Lifeline.h){
                                    showinfoandstats(render , Info_Lifeline , &Lifeline1, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Dracula.x && x <= Logo_Dracula.x + Logo_Dracula.w && y >= Logo_Dracula.y && y <= Logo_Dracula.y + Logo_Dracula.h){
                                    showinfoandstats(render , Info_Dracula , &Dracula1, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Medic.x && x <= Logo_Medic.x + Logo_Medic.w && y >= Logo_Medic.y && y <= Logo_Medic.y + Logo_Medic.h){
                                    showinfoandstats(render , Info_Medic , &Medic1, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }

                                
                                
                                
                            }
                        }
                        else if(current_team == 2){

                            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                                int x = event.button.x ;
                                int y = event.button.y ;


                                //WHERE?
                                if( x >= Left_Key_Logos.x && x <= Left_Key_Logos.x + Left_Key_Logos.w && y >= Left_Key_Logos.y && y <= Left_Key_Logos.y + Left_Key_Logos.h){
                                    Mix_PlayChannel(-1 , back_sound , 0);
                                    current_team = 1;
                                    unselectallfighters(PRETEAM1 , PRETEAM2);
                                    state = GAMEMODE_SELECTION;
                                }
                                else if( x >= ready2.x && x <= ready2.x + ready2.w && y >= ready2.y && y <= ready2.y + ready2.h){
                                    if(howmanyselected(PRETEAM2) <= 4 && howmanyselected(PRETEAM2) >= 2){
                                            Mix_PlayChannel(-1 , select_sound , 0);
                                            selecting_team2 = 1;
                                           
                                    }
                                    else {
                                        if(howmanyselected(PRETEAM2) < 2){
                                            Mix_PlayChannel(-1 , tick_sound , 0);
                                            error_message_1 = 1;
                                        }

                                    }
                                }
                                else if( x >= Logo_John_Wick.x && x <= Logo_John_Wick.x + Logo_John_Wick.w && y >= Logo_John_Wick.y && y <= Logo_John_Wick.y + Logo_John_Wick.h){
                                    addorkickfromteam(PRETEAM2 , render , 0, font);
                                }
                                else if(x >= Logo_Sans.x && x <= Logo_Sans.x + Logo_Sans.w && y >= Logo_Sans.y && y <= Logo_Sans.y + Logo_Sans.h){
                                    addorkickfromteam(PRETEAM2 , render , 1, font);
                                }
                                else if(x >= Logo_Batman.x && x <= Logo_Batman.x + Logo_Batman.w && y >= Logo_Batman.y && y <= Logo_Batman.y + Logo_Batman.h){
                                    addorkickfromteam(PRETEAM2 , render , 2, font);
                                }
                                else if(x >= Logo_Hulk.x && x <= Logo_Hulk.x + Logo_Hulk.w && y >= Logo_Hulk.y && y <= Logo_Hulk.y + Logo_Hulk.h){
                                    addorkickfromteam(PRETEAM2 , render , 3, font);
                                }
                                else if(x >= Logo_Snorlax.x && x <= Logo_Snorlax.x + Logo_Snorlax.w && y >= Logo_Snorlax.y && y <= Logo_Snorlax.y + Logo_Snorlax.h){
                                    addorkickfromteam(PRETEAM2 , render , 4, font);
                                }
                                else if(x >= Logo_Demolisher.x && x <= Logo_Demolisher.x + Logo_Demolisher.w && y >= Logo_Demolisher.y && y <= Logo_Demolisher.y + Logo_Demolisher.h){
                                    addorkickfromteam(PRETEAM2 , render , 5, font);
                                }
                                else if(x >= Logo_Lifeline.x && x <= Logo_Lifeline.x + Logo_Lifeline.w && y >= Logo_Lifeline.y && y <= Logo_Lifeline.y + Logo_Lifeline.h){
                                    addorkickfromteam(PRETEAM2 , render , 6, font);
                                }
                                else if(x >= Logo_Dracula.x && x <= Logo_Dracula.x + Logo_Dracula.w && y >= Logo_Dracula.y && y <= Logo_Dracula.y + Logo_Dracula.h){
                                    addorkickfromteam(PRETEAM2 , render , 7, font);
                                }
                                else if(x >= Logo_Medic.x && x <= Logo_Medic.x + Logo_Medic.w && y >= Logo_Medic.y && y <= Logo_Medic.y + Logo_Medic.h){
                                    addorkickfromteam(PRETEAM2 , render , 8, font);
                                }



                            }
                            //Right Clicked?
                            else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT){
                                int x = event.button.x ;
                                int y = event.button.y ;
                                //Where?
                                if( x >= Logo_John_Wick.x && x <= Logo_John_Wick.x + Logo_John_Wick.w && y >= Logo_John_Wick.y && y <= Logo_John_Wick.y + Logo_John_Wick.h){
                                    showinfoandstats(render , Info_JohnWick , &John_Wick2, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Sans.x && x <= Logo_Sans.x + Logo_Sans.w && y >= Logo_Sans.y && y <= Logo_Sans.y + Logo_Sans.h){
                                    showinfoandstats(render , Info_Sans , &Sans2, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Batman.x && x <= Logo_Batman.x + Logo_Batman.w && y >= Logo_Batman.y && y <= Logo_Batman.y + Logo_Batman.h){
                                    showinfoandstats(render , Info_Batman , &Batman2, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Hulk.x && x <= Logo_Hulk.x + Logo_Hulk.w && y >= Logo_Hulk.y && y <= Logo_Hulk.y + Logo_Hulk.h){
                                    showinfoandstats(render , Info_Hulk , &Hulk2, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Snorlax.x && x <= Logo_Snorlax.x + Logo_Snorlax.w && y >= Logo_Snorlax.y && y <= Logo_Snorlax.y + Logo_Snorlax.h){
                                    showinfoandstats(render , Info_Snorlax , &Snorlax2, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Demolisher.x && x <= Logo_Demolisher.x + Logo_Demolisher.w && y >= Logo_Demolisher.y && y <= Logo_Demolisher.y + Logo_Demolisher.h){
                                    showinfoandstats(render , Info_Demolisher , &Demolisher2, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Lifeline.x && x <= Logo_Lifeline.x + Logo_Lifeline.w && y >= Logo_Lifeline.y && y <= Logo_Lifeline.y + Logo_Lifeline.h){
                                    showinfoandstats(render , Info_Lifeline , &Lifeline2, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Dracula.x && x <= Logo_Dracula.x + Logo_Dracula.w && y >= Logo_Dracula.y && y <= Logo_Dracula.y + Logo_Dracula.h){
                                    showinfoandstats(render , Info_Dracula , &Dracula2, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }
                                else if(x >= Logo_Medic.x && x <= Logo_Medic.x + Logo_Medic.w && y >= Logo_Medic.y && y <= Logo_Medic.y + Logo_Medic.h){
                                    showinfoandstats(render , Info_Medic , &Medic2, tick_sound , teamselection_screen , team1_coins , team2_coins , blink_turn , ready_pressed , current_team, font);
                                }

                        }
                        }

                        break;
                    
                    case FIGHT:
                        //Fighting music on:
                        if(currentMusic != 2){
                            Mix_HaltMusic();
                            Mix_FadeInMusic(fighting_music,-1 , 2000);
                            currentMusic = 2;
                        }
                        

                        if(team1 == NULL && team2 == NULL ){
                            init_teams(&team1 , &team2 , PRETEAM1 , PRETEAM2 , visuals , visuals_selected);

                        }

                        //
                        SDL_Event fighting_event  ;

                        fight = IN_FIGHT; //IMPORTANT!!! ALWAYS START WITH IN_FIGHT when a match is started.

                        
                        int fight_running = 0;
                        //DECIDES AT THE BEGINNING WHO STARTS ATTACKING IN FONCTION OF WHAT TEAM HAS THE FASTEST FIGHTERS
                        int turn_to_attack = whostarts(team1 , team2 , howmanyselected(PRETEAM1) , howmanyselected(PRETEAM2));
                        
/*__________________________________________________________________________________________________FIGHT LOOP STARTS HERE_____________________________________________________________________________________________________________*/
                       
                        while(someonealive(team1 , howmanyselected(PRETEAM1)) && someonealive(team2 , howmanyselected(PRETEAM2)) && fight_running == 0){

                        
            /*_____________________________________________________________MANAGING INPUT FROM USER FOR THE FIGHT__________________________________________________________________*/
                            while(SDL_PollEvent(&fighting_event)){

                                if(fighting_event.type == SDL_QUIT){
                                    fight_running = 1;
                                    quit = 1;
                
                                }
                                
                                switch(fight){

                                    case IN_FIGHT:
                                        /*_________________________________________TEAM 1 _________________________________________*/
                                        if(turn_to_attack == 1){
                                            if(fighting_event.type ==  SDL_MOUSEBUTTONDOWN && fighting_event.button.button == SDL_BUTTON_LEFT){
                                                int x = fighting_event.button.x ;
                                                int y = fighting_event.button.y;

                                                if(x >= Pause_button.x && x <= Pause_button.x + Pause_button.w && y >= Pause_button.y && y <= Pause_button.y + Pause_button.h){
                                                    fight = PAUSE;
                                                }
                                                else if(x >= Team1_Fighter1.x && x <= Team1_Fighter1.x + Team1_Fighter1.w && y >= Team1_Fighter1.y && y <= Team1_Fighter1.y + Team1_Fighter1.h){
                                                    FIGHT_unselectallfighters(team1 , team2);
                                                    team1[0].selected = 1;

                                                }
                                                else if(x >= Team1_Fighter2.x && x <= Team1_Fighter2.x + Team1_Fighter2.w && y >= Team1_Fighter2.y && y <= Team1_Fighter2.y + Team1_Fighter2.h){
                                                    FIGHT_unselectallfighters(team1 , team2);
                                                    team1[1].selected = 1;
                                                }
                                                else if(x >= Team1_Fighter3.x && x <= Team1_Fighter3.x + Team1_Fighter3.w && y >= Team1_Fighter3.y && y <= Team1_Fighter3.y + Team1_Fighter3.h && howmanyselected(PRETEAM1) >= 3){
                                                    FIGHT_unselectallfighters(team1 , team2);
                                                    team1[2].selected = 1;
                                                }
                                                else if(x >= Team1_Fighter4.x && x <= Team1_Fighter4.x + Team1_Fighter4.w && y >= Team1_Fighter4.y && y <= Team1_Fighter4.y + Team1_Fighter4.h && howmanyselected(PRETEAM1) == 4){
                                                    FIGHT_unselectallfighters(team1 , team2);
                                                    team1[3].selected = 1;
                                                }
                                                
                                            }
                                        }
                                        /*_________________________________________TEAM 2 _________________________________________*/
                                        else if(turn_to_attack == 2){
                                            if(fighting_event.type ==  SDL_MOUSEBUTTONDOWN && fighting_event.button.button == SDL_BUTTON_LEFT){
                                                int x = fighting_event.button.x ;
                                                int y = fighting_event.button.y;

                                                if(x >= Pause_button.x && x <= Pause_button.x + Pause_button.w && y >= Pause_button.y && y <= Pause_button.y + Pause_button.h){
                                                    fight = PAUSE;
                                                }
                                                else if(x >= Team2_Fighter1.x && x <= Team2_Fighter1.x + Team2_Fighter1.w && y >= Team2_Fighter1.y && y <= Team2_Fighter1.y + Team2_Fighter1.h){
                                                    FIGHT_unselectallfighters(team1 , team2);
                                                    team2[0].selected = 1;
                                                }
                                                else if(x >= Team2_Fighter2.x && x <= Team2_Fighter2.x + Team2_Fighter2.w && y >= Team2_Fighter2.y && y <= Team2_Fighter2.y + Team2_Fighter2.h){
                                                    FIGHT_unselectallfighters(team1 , team2);
                                                    team2[1].selected = 1;
                                                }
                                                else if(x >= Team2_Fighter3.x && x <= Team2_Fighter3.x + Team2_Fighter3.w && y >= Team2_Fighter3.y && y <= Team2_Fighter3.y + Team2_Fighter3.h && howmanyselected(PRETEAM2) >= 3){
                                                    FIGHT_unselectallfighters(team1 , team2);
                                                    team2[2].selected = 1;
                                                }
                                                else if(x >= Team2_Fighter4.x && x <= Team2_Fighter4.x + Team2_Fighter4.w && y >= Team2_Fighter4.y && y <= Team2_Fighter4.y + Team2_Fighter4.h && howmanyselected(PRETEAM2) == 4){
                                                    FIGHT_unselectallfighters(team1 , team2);
                                                    team2[3].selected = 1;
                                                }
                                                
                                            }
                                        }

                                        break;

                                    
                                    /*_______________________________________________________PAUSE____________________________________________________________________________________________*/

                                    case PAUSE:
                                
                                        if(fighting_event.type ==  SDL_MOUSEBUTTONDOWN && fighting_event.button.button == SDL_BUTTON_LEFT){
                                            int x = fighting_event.button.x ;
                                            int y = fighting_event.button.y;

                                            if(x >= Continue_button_pause.x && x <= Continue_button_pause.x + Continue_button_pause.w && y >= Continue_button_pause.y && y <= Continue_button_pause.y + Continue_button_pause.h){
                                                fight = IN_FIGHT;
                                            }
                                            else if(x >= Menu_button_pause.x && x <= Menu_button_pause.x + Menu_button_pause.w && y >= Menu_button_pause.y && y <= Menu_button_pause.y + Menu_button_pause.h){
                                                //RESETING ALL VALUES 
                                                state = MENU;
                                                fight_running = 1;
                                                unselectallfighters(PRETEAM1, PRETEAM2);
                                                cleanup_teams(&team1 , &team2 , &team1_coins , &team2_coins);

                                            }
                                            else if(x >= Quit_button_pause.x && x <= Quit_button_pause.x + Quit_button_pause.w && y >= Quit_button_pause.y && y <= Quit_button_pause.y + Quit_button_pause.h){
                                                fight_running=1;
                                                quit = 1;
                                            }
                                            
                                        }
                                        
                                        break;
                                }
                            }
                     /*_____________________________________________________________RENDERING THE FIGHT NON STOP __________________________________________________________________*/

                                        switch(fight){

                                            case IN_FIGHT:
                                                SDL_RenderClear(render);
                                                SDL_RenderCopy(render , fight_scenario , NULL , NULL);
                                                renderfighters(render, team1 , team2 , howmanyselected(PRETEAM1) , howmanyselected(PRETEAM2));
                                                SDL_RenderCopy(render , Pause_button_texture , NULL , &Pause_button);
                                                render_animation(render , fire_animation , &fight_torch1 , 15 , 24 , 1 , 6 , 1 , 100);
                                                render_animation(render , fire_animation , &fight_torch2 , 15 , 24 , 1 , 6 , 1, 100);
                                                render_animation(render , fire_animation , &fight_torch3 , 15 , 24 , 1 , 6 , 1, 100);
                                                render_animation(render, fire_animation , &fight_torch4 , 15 , 24 , 1 , 6 , 1, 100);
                                                SDL_RenderCopy(render , fight_torches_texture , NULL , NULL);
                                                SDL_RenderPresent(render);
                                                break;
                                            
                                            case PAUSE:
                                                SDL_RenderCopy(render , Paused_ui , NULL , NULL);
                                                SDL_RenderPresent(render);
                                                break;
                                        


                                        }


                        }

                        
                        
                        break;
                        
                    

                

            }

            }

/*---------------------------RENDER EVERYTHING EXCEPT THE FIGHT , THE FIGHT HAS ITS OWN RENDERING LOOP AND EVENT POLLING-------------------------------------------------------*/            
            //always render and show things 
            switch(state){
                    
                case MENU:
                    SDL_RenderClear(render);
                    SDL_RenderCopy(render , menu_screen , NULL , NULL);
                    render_animation(render, fire_animation , &Fire1 , 15 , 24 , 10 , 6 , 1 , 100);
                    render_animation(render, fire_animation , &Fire2 , 15 , 24 , 10 , 6 , 1 , 100);
                    SDL_RenderCopy(render , torches , NULL , NULL);
                    SDL_RenderPresent(render);
                    break;
                
                case HOW_TO_PLAY:
                    SDL_RenderClear(render);
                    SDL_RenderCopy(render , how_to_play_screen , NULL , NULL);
                    SDL_RenderPresent(render);
                    break;

                case GAMEMODE_SELECTION:
                    SDL_RenderClear(render);
                    SDL_RenderCopy(render , gamemode_screen , NULL , NULL);
                    SDL_RenderPresent(render);
                    break;
                
                case TEAM_SELECTION:
                    if(current_team == 1){
                        SDL_RenderClear(render);
                        SDL_RenderCopy(render , teamselection_screen , NULL , NULL);
                        rendercoins(render , team1_coins , &coins1 , 40 , dark_gray, font);
                        rendercoins(render , team2_coins , &coins2 , 40 , dark_gray , font);

                        SDL_RenderCopy(render , blink_turn , NULL , &yourturn1);
                        renderlogoselectedfighters(render , PRETEAM1 ,All_Logos , current_team);
                        SDL_RenderPresent(render);
                        
                        if(selecting_team1 == 1){
                            //ready button pressed
                            SDL_RenderCopy(render , ready_pressed , NULL , &ready1);
                            SDL_RenderPresent(render);
                            current_team = 2;
                        }
                        else if(error_message_1 == 1){
                            rendermessageTEMP("You need to pick at least 2 fighters" , &MessageSelection , render , 2000 , font);
                            error_message_1 = 0;
                        }
                    
                    }
                    else if(current_team ==2){
                        SDL_RenderClear(render);
                        SDL_RenderCopy(render , teamselection_screen , NULL , NULL);
                        rendercoins(render , team1_coins , &coins1 , 40 , dark_gray, font);
                        rendercoins(render , team2_coins , &coins2 , 40 , dark_gray, font);
                        SDL_RenderCopy(render , blink_turn , NULL , &yourturn2);
                        SDL_RenderCopy(render , ready_pressed , NULL ,&ready1);
                        renderlogoselectedfighters(render , PRETEAM1 ,All_Logos , 1);
                        renderlogoselectedfighters(render , PRETEAM2 ,All_Logos , current_team);
                        SDL_RenderPresent(render);

                        if(selecting_team2 == 1){
                            SDL_RenderClear(render);
                            SDL_RenderCopy(render , teamselection_screen , NULL , NULL);
                            rendercoins(render , team1_coins , &coins1 , 40 , dark_gray, font);
                            rendercoins(render , team2_coins , &coins2 , 40 , dark_gray, font);
                            SDL_RenderCopy(render , blink_turn , NULL , &yourturn2);
                            SDL_RenderCopy(render , ready_pressed , NULL ,&ready1);
                            SDL_RenderCopy(render , ready_pressed , NULL , &ready2);
                            renderlogoselectedfighters(render , PRETEAM1 ,All_Logos , 1);
                            renderlogoselectedfighters(render , PRETEAM2 ,All_Logos , current_team);
                            SDL_RenderPresent(render);         
                            state= FIGHT;
                        }
                        else if(error_message_1){
                            rendermessageTEMP("You need to pick at least 2 fighters" , &MessageSelection , render , 2000 , font);
                            error_message_1 = 0;
                        }
                    }
                    break;
                
                
                case END_GAME:

                    break;
                

                
                
            }
        }


}

