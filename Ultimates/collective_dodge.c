void collective_dodge(Fighter* attacker, Fighter* defender, Fighter* ally,Fighter* team[],nbr_of_ally){
    for(int i=0; i<nbr_of_ally ; i++){
        if(team[i]->hp>team[i]->hp_max+70*team[i]->dodge){
            team[i]->hp=team[i]->hp_max;
        }else{
            team[i]->hp+=team[i]->dodge*70;
        }
}
