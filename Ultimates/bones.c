void bones(Fighter *target, Fighter *attacant){
    temp_correct_attack=attacant->attack
    attacant->attack*=0*70;
    int a;
    for(int i=0;i<6;i++){
        a=rand()%2+1;
        if(a==1){
            attack(Fighter *target, Fighter *attacant);
        }
    }
    attacant->attack=temp_correct_attack
}