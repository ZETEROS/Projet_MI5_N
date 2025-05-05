void thunder_clap(Fighter* attacker, Fighter* defender, Fighter* ally, Fighter* team[]){
    for(int i=0 ; i<nbr_of_ennemy : i++){
        if (team[i]->attack <= 20){
            team[i]->attack = 0;
        }else{
            team[i]->attack -= 20;
        }
    }
// trouvé une manière de le faire pour un seul tour
