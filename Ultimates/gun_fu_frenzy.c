void gun_fu_frenzy(Fighter *target, Fighter *attacant){
    float temp_dodge= target->dodge
    target->dodge*=0.5;
    int a , b , c;
    a=rand()%10+1
    b=rand()%10+1
    c=rand()%10+1
    if(a>3){
        float temp_correct_dmg= attacant->dmg;
        attacant->dmg = attacant->dmg*2;
        attack(Fighter *target, Fighter *attacant);
        attacant->dmg = temp_correct_dmg;
    }else{
        attack(Fighter *target, Fighter *attacant);
    }
    if(b>3){
        float temp_correct_dmg= attacant->dmg;
        attacant->dmg = attacant->dmg*2;
        attack(Fighter *target, Fighter *attacant);
        attacant->dmg = temp_correct_dmg;
    }else{
        attack(Fighter *target, Fighter *attacant);
    }
    if(c>3){
        float temp_correct_dmg= attacant->dmg;
        attacant->dmg = attacant->dmg*2;
        attack(Fighter *target, Fighter *attacant);
        attacant->dmg = temp_correct_dmg;
    }else{
        attack(Fighter *target, Fighter *attacant);
    }
    attacant->dmg = temp_correct_dmg;
    target->dodge = temp_dodge;
}