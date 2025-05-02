void attack(Fighter *target, Fighter *attacant){
    float impact= (attacant->dmg * (100-(target->def)/100));
    target->hp -= impact;
}