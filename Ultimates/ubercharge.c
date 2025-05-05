void uber_charge(Fighter* attacker, Fighter* defender, Fighter* ally){
    attacker->dodge = 1;
    ally->dodge = 1; //équivalent a l'invulnérabilité trouvé un moyen de durée de 2tours
}