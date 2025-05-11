#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"


Fighter creator(char* name){
    Fighter a ;
    //FILL THIS STATS | NECESSARY
    strcpy(a.name , name);
    printf("\nClass: ");
    scanf("%d",&a.class);
    printf("\nHP MAX: ");
    scanf("%f",&a.hp_max);  
    a.hp = a.hp_max;
    printf("\nDamage: ");
    scanf("%f",&a.dmg);
    printf("\nDefense: ");
    scanf("%f",&a.def);
    printf("\nDodging: ");
    scanf("%f",&a.dodge);
    printf("\nSpeed: ");
    scanf("%f",&a.speed);
    printf("\nPrice: ");
    scanf("%d",&a.price);
    printf("\nSpecial Attack: ");
    scanf("%f",&a.special_attack_name);
    //a.speed = 0;

    return a;
}
void show_stats(Fighter a){
    printf("Name = %s\nHP: %.2f\nHP_MAX:%.2f\nDMG:%.2f\nDEF:%.2f\nDODGE:%.2f\nSPEED:%.2f\n",a.name,a.hp,a.hp_max,a.dmg,a.dmg,a.def,a.dodge,a.speed);
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
    char name[20] ;
    char file[20] ;
    printf("Name of the fighter:\n");
    scanf("%s",name);
    printf("\nName of the file where to export the fighter:\n");
    scanf("%s",file);

    Fighter a = creator(name);

    export_fighter(a ,file);
    show_stats(a);


    return 0;
}
