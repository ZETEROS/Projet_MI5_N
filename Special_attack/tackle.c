void tackle(Fighter *target, Fighter *attacant){
    correct_def=target->def;
    target->def*=0.70;
    attack(Fighter *target, Fighter *attacant);
    target->def=correct_def;
}

void (*special_move)(Fighter *, Fighter *) = tackle;