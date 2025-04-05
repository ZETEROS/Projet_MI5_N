#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"


Fighter creator(char* name){
    Fighter a ;
    //FILL THIS STATS | NECESSARY
    strcpy(a.name , name);
    a.class = 1; 
    a.hp = 1;
    a.hp_max = 1;
    a.dmg = 1;
    a.def = 0;
    a.dodge = 1;
    //a.speed = 0;

    return a;
}

void export_fighter(Fighter a , char* file){
    FILE* doc = fopen(file , "wb");
    if(doc == NULL){
        printf("Failed to open");
        exit(1);
    }

    fwrite(&a , sizeof(Fighter), 1 , doc);
    fclose(doc);
}

int main(){
    char name[20] = "Here the name of the Fighter";
    char file[20] = "Here the name of the file to create";
    Fighter a = creator(name);

    export_fighter(a ,file);

    return 0;
}
