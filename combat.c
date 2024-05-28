#include "combat.h"

void print_enemy(Enemy* e){
    printf("\n___________________________________________________________________________________________\n");
    printf("- %s\n", e->name); //Print enemy's name
    printf("HP: ");
    for(int i=0;i<=(e->stats[2]+1)/2;i++){printf("|");}//Print visual representation of health
    if(e->stats[1]>0){
        for(int i=0;i<=(e->stats[1]+1)/2;i++){printf("]");}//Print visual representation of defense
        printf(" %d", e->stats[2]);
        printf(" + [%d]", e->stats[1]);
    }else{printf(" %d", e->stats[2]);}
    printf("\n___________________________________________________________________________________________\n");
}

void print_player(Character* p){
    printf("\n___________________________________________________________________________________________\n");
    printf("- You (%s)\n", p->name);//Print player's name
    printf("HP: ");
    for(int i=0;i<=(p->stats[2]+1)/2;i++){printf("|");}//Print visual representation of health
    if(p->stats[1]>0){
        for(int i=0;i<=(p->stats[1]+1)/2;i++){printf("]");}//Print visual representation of defense
        printf(" %d", p->stats[2]);
        printf(" + [%d]", p->stats[1]);
    }else{printf(" %d", p->stats[2]);}
    printf("\n___________________________________________________________________________________________\n");
}

/////////////////////////////////////////////7

int attack(Skill* skll, char*n_atck, char*n_def, int*stats_a, int*stats_d, int max_hp, int* venom, int* prob){
    printf("\n%s used %s\n", n_atck, skll->name);
    if(skll->mod.chr == 'r'){
        if(skll->of_def==1){skll->of_def=0;
            printf("Charging %s...\n\n", skll->name);}
        else{skll->of_def=1;printf("%sis charged\n\n", skll->name);}   
    }else if(skll->mod.chr == 'f'){printf("%s feels %d times stronger\n\n", n_atck, skll->dmg_skll);stats_a[0]+=skll->dmg_skll;}
    int dmg = (skll->of_def)*(skll->dmg_skll + stats_a[0]);
    if(skll->mod.chr == 'd'){
        stats_a[1]+=skll->dmg_skll;
        printf("%s gained %d defense\n\n", n_atck, skll->dmg_skll);
    }else if(skll->mod.chr == 'h'){
        stats_a[2]+=skll->dmg_skll;
        printf("%s healed %d\n\n", n_atck, skll->dmg_skll);
        if(stats_a[2]>max_hp){stats_a[2]=max_hp;}
    }else if(skll->mod.chr == 'v'){*venom = 3;}
    
   int prob_attack = rand()%100;

    if(*venom>0){dmg+=stats_a[0];}
    if(*prob<=prob_attack){
    if(stats_d[1]>0){
        stats_d[1]-= dmg;
        if(stats_d[1]<=0){stats_d[1]=0;printf("Defense broken\n\n");}
    }else{
        stats_d[2]-= dmg;
        if(stats_d[2]<=0){stats_d[2]=0;return 1;}
    }}
    if(skll->of_def==1 && *prob<=prob_attack){printf("%s dealt %d damage to %s\n\n", n_atck, dmg, n_def);}
    else if(skll->of_def==1 && *prob>prob_attack){printf("%s avoided the attack\n\n", n_def);}
    if(*venom>0){printf("\n%s received %d of residual damage\n\n", n_def, stats_a[0]);*venom--;}
    if(skll->mod.chr == 's'){
        printf("%s has been stunned, they can't attack next round\n\n", n_def);*prob = 0;
        return 2;
    }else if(skll->mod.chr == 'p'){printf("There is a chance of %d%% to avoid being attacked", skll->dmg_skll*3);
    *prob = skll->dmg_skll*3;return 0;}
    *prob = 0;
    return 0;

}

/////////////////////////////////////////////7

int combat(Character *plyr, Enemy *enmy, int size){
    Queue* q = init_queue(size);
    for(int i = 0; i<size; i++){
        q = enqueue(q, *plyr, *enmy);
    }
    int a;
    int rand_n = rand();

    int prob=0;
    int result;
    int pvenom = 0;
    int evenom = 0;
    int max_hp_plyr = 0;
    int max_hp_enmy = 0;
    
    for(int i = 0; i<4; i++){
        max_hp_plyr += plyr->skill[i].stats_plyr[2];
        plyr->skill[i].stats_plyr[2];
        max_hp_enmy += enmy->skill[i].stats_plyr[2];
        if(plyr->skill[i].mod.chr == 'r'){plyr->skill[i].of_def=1;}
        if(enmy->skill[i].mod.chr == 'r'){enmy->skill[i].of_def=1;}
    }
    enmy->stats[2]=max_hp_enmy;
    
    for(int i = 0; i<2; i++){
        plyr->stats[i] = 0;
        enmy->stats[i] = 0;
    }
    
    
    for(int i=0;i<4;i++){
        enmy->skill[i].mod.n = 0;
        enmy->stats[1]+=enmy->skill[i].stats_plyr[1];//Reset defense
        enmy->stats[0]+=enmy->skill[i].stats_plyr[0];

        plyr->skill[i].mod.n = 0; //Reset counter limited uses skills
        plyr->stats[1]+=plyr->skill[i].stats_plyr[1];//Reset defense
        plyr->stats[0]+=plyr->skill[i].stats_plyr[0];
    }
    int turn=rand()%2;
    if(turn == 0){printf("The player %s starts\n\n", plyr->name);
    }else{printf("The enemy %s starts\n\n", enmy->name);}

    while(q->elements>0){
        if(turn==0){
            print_enemy(enmy);
            printf("\n");//Print enemy?
            print_player(plyr);
        choose_skill:
            for(int j = 0; j<4; j++){printf("%d - %s",j+1, plyr->skill[j]);}
            printf("Choose skill: ");
            scanf("%d", &a);
            a--;
            int p_dmg = (plyr->skill[a].of_def)*(plyr->skill[a].dmg_skll + plyr->stats[0]);//Segmentation fault?

    /////////////////////////////////////////////7

            if((plyr->skill[a].mod.n==plyr->skill[a].mod.max)&&(plyr->skill[a].mod.chr!='n')){
                printf("You cannot use that hability again\n");
                goto choose_skill;}
            plyr->skill[a].mod.n++;

            result = attack(&plyr->skill[a], plyr->name, enmy->name, plyr->stats, enmy->stats, max_hp_plyr, &pvenom, &prob);

            if(result == 1){printf("You won the fight against %s\nCongratulations!\n\n", enmy->name);return 1;}
            else if(result == 2){
                dequeue(q);
                printf("\n%d turns remaining\n", q->elements);
                print_enemy(enmy);
                printf("\n");//Print enemy?
                print_player(plyr);
                goto choose_skill;
            }

            dequeue(q);
            printf("\n%d turns remaining\n", q->elements);
            turn = 1;
        }   

        if(turn==1){
            print_enemy(enmy);
            printf("\n");//Print enemy?
            print_player(plyr);
            pause();

        enemy_combat:
            int rand_t = rand();
            int b = rand_t%4;
            int e_dmg = (enmy->skill[b].dmg_skll + enmy->stats[0])*enmy->skill[b].of_def;

            if((enmy->skill[b].mod.n==enmy->skill[b].mod.max)&&(enmy->skill[b].mod.chr!='n')){goto enemy_combat;}
            enmy->skill[b].mod.n++;

            result = attack(&enmy->skill[b], enmy->name, plyr->name, enmy->stats, plyr->stats, max_hp_enmy, &evenom, &prob);

            if(result==1){printf("You lost against %s\nTry again next time\n", enmy->name);return 2;}
            else if(result==2){
                dequeue(q);
                printf("%d turns remaining\n", q->elements);
                print_enemy(enmy);
                printf("\n");
                print_player(plyr);
                pause();
                goto enemy_combat;
            }

            dequeue(q);
            printf("\n%d turns remaining\n", q->elements);
            turn = 0;
        }
    }
}