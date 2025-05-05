void crusaders_crossbow(Fighter* attacker, Fighter* defender, Fighter* ally){
    if(ally->hp>ally_hp_max-30){
        ally->hp=ally->hp_max
    }else{
        ally->hp+=30
    }
}