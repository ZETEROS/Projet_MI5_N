void dodo_infection(Fighter *target, Fighter *attacant){
    temp_correct_attack=attacant->attack;
    attacant->attack*=0*75;
    attack(Fighter *target, Fighter *attacant);
    target->attack=0 // equivalent de l'endormissement trouvé un moyen de durée de 1 tour
}