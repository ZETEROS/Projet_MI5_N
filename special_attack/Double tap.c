void Double_tap(Fightera *target, Fighter *attacant){
    float correct_dmg= attacant->dmg;
    attacant->dmg = attacant->dmg*0.75;
    attack(Fighter *target, Fighter *attacant);
    attack(Fighter *target, Fighter *attacant);
    attacant->dmg = correct_dmg
}

void (*special_move)(Fighter *, Fighter *) = Double_tap;
// appelation : special_move(target, attacant);