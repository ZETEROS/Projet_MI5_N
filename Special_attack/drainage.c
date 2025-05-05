void drainage(Fighter *target, Fighter *attacant){
    float correct_def=target->def;
    target->def=0;
    attack(Fighter *target, Fighter *attacant);
    target->def=correct_def;
    float hp_drained=attacant->dmg * 0.40
    if(attacant->hp + hp_drained > hp_max){
        attacant->hp=hp_max
    }else{
        attacant->hp+= hp_drained
    }
}

void (*special_move)(Fighter *, Fighter *) = drainage;