void hulk_smash(Fighter *target, Fighter *attacant){
    if(target->hp<45){
        target->hp=0;
    }else{
        target->hp-=45;
    }
    target->attack=0; //equivalent d'un stun trouver un moyen de durée d'1 tour
}