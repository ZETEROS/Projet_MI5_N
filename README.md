# SMASH & KILL
### PROJECT_MI5_N


## Project Progress
### 06 - 04 - 2025
So far, we've organized ourselves to try and create a base of operations and concepts. **We've created a list of characters with some stats that are still in Beta**, we'll have to look at them later once the fighting system is established in case the character stats are too unbalanced.
**We've implemented 2 toolcodes that will allow us to create a Fighter structure** , which we can save in a binary file in the folder of the same name, Fighters. And, of course, another code allows us to load the Fighter into RAM from the binary file and then manipulate it.
We've decided to work in english for the coding and for this github repository.

### 10 - 04 - 2025
In this update, **we've managed to implement special abilities for characters using pointers to functions in their Fighter structure**. Now, characters, when loaded into the program, **will be assigned their special abilities based on the name of their ability found in their own member in the fighter structure**, called "special_attack_name".

### 16 - 04 - 2025
In this advancement **we have made several decisions that could be modified later**, but we have decided to work using the **SDL library** that will allow us to realize a **graphical and interactive interface**. For this we will use SDL_Image to load and render in the window **our own designs** of the menu, buttons, game, etc. Today we have added the file Smash_N_Kill.c in which we have already formed something basic and that we will use later in the game, a simple menu that **at this time is not interactive yet**. **We plan to work on a 1280 x 720 p game**, we will see if we continue with this later. To test it must be compiled and executed in the same folder as the assets folder in which is the Menu.png which is the actual design of our menu.



## SETUP

To compile the game please use in Ubuntu : **gcc 'Smash_N_Kill.c' -o 'Smash&Kill' -lSDL2 -lSDL2_image**
