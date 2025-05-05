void drone_fight(Fighter* attacker, Fighter* defender, Fighter* ally){
    if(ally->hp>ally->hp_max-20){
        ally->hp=ally->hp_max
    }else{
        ally->hp+=20
    }
    // importe le fighter et redonner les stats par défat pour esuqie/attack/defense
}