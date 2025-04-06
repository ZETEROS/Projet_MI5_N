#include "structure.h"
#include <stdio.h>
#include <stdlib.h>

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


int main(){
    char file[20];
    printf("\nName of the file from where to import the fighter:\n");
    scanf("%s",file);
    Fighter a = import(file);
    show_stats(a);

}