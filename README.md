# SMASH & KILL

## SETUP
### AFTER INSTALLATION
After installing the file, extract it to your PC.
Then open your terminal.
To compile the game please use in Ubuntu : 
**gcc 'Smash_N_Kill.c' -o 'Smash&Kill' -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf**
To run the program enter the following command: **./Smash&Kill**

### IF YOU DON'T HAVE THE SDL LIBRARY
💻 For Linux (Ubuntu/Debian)
Update packages :

**sudo apt update**
   

Install SDL2 and development library :

**sudo apt install libsdl2-dev**
   

Check the installation :
You can check if SDL2 is installed with the following command :

**sdl2-config --version**
   

Compile an SDL2 program :

**gcc -o test test.c $(sdl2-config --cflags --libs)**
   

