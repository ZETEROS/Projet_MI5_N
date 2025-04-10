#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "special_attacks_list.h"

Fighter import(char* file){
    Fighter a;
    FILE* doc = fopen(file , "rb");
    if(doc == NULL){
        printf("File not found");
        exit(1);

    }
    fread(&a , sizeof(Fighter), 1 , doc);
    fclose(doc);
    return a;

}

void show_stats(Fighter a){
    printf("Name = %s\nHP: %.2f\nHP_MAX:%.2f\nDMG:%.2f\nDEF:%.2f\nDODGE:%.2f\nSPEED:%.2f\n",a.name,a.hp,a.hp_max,a.dmg,a.dmg,a.def,a.dodge,a.speed);
}


int main(){
    char file[20];
    printf("\nName of the file from where to import the fighter:\n");
    scanf("%s",file);
    Fighter a = import(file);
    show_stats(a);
    assign_special(&a);
    a.special1(&a);

}