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

### 25 - 04 - 2025
During all this week I was advancing in the physical design of the characters, of course trying to do it in my style. The style I had already chosen was Pixel art, so it was necessary to draw the characters in Pixel Art. Now all the characters were drawn, and received each one a page of information about them. On this page are their physical stats, such as life, defense, speed, and dodge. These stats are dynamic, that is, they are not drawn by default on the page but are rendered on top of the page in their precise positions each time the page is loaded in the game. These statistics are obtained from the binary files of the fighters set in their Fighter variables loaded at the start of the game execution from the game folder. So let's go back to what we said before about the character information.
From now on at the team building stage, when you right click on a character's logo this page will show up with his appearance, stats, skills and a short sentence that can show us what this character is like.
The next step will be to program the actual team formation so we can move on to the combat phase. When we get there, I guess I'll have to draw the combat location and more. Anxious to see how this turns out.
Also, I forgot to mention that I added a background music and sound effects when you click on the buttons. These sounds are in the “assets” folder of course along with the rest of the content to be rendered. These same sounds were selected from the page Itch.io, the authors AlexMdle and ArcOfDream leave these pixel art style music free to use, both commercial and professional.



## SETUP

To compile the game please use in Ubuntu : **gcc 'Smash_N_Kill.c' -o 'Smash&Kill' -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf**
