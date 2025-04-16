#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef STRUCTURE_H
#include "structure.h"
#endif
#include "special_attacks_list.h"


void assign_special(Fighter* a){
    if(strcmp(a->special_attack_name , "test")){
        a->special1 = test ;
    }
}