#include "combat.h"

void print_enemy(Enemy* e){
    printf("\n___________________________________________________________________________________________\n");
    printf("- %s\n", e->name);
    printf("HP: ");
    for(int i=0;i<(e->stats[2]+1)/2;i++){printf("|");}
    if(e->stats[1]>0){
        for(int i=0;i<(e->stats[1]+1)/2;i++){printf("]");}
        printf(" %d", e->stats[2]);
        printf(" + [%d]", e->stats[1]);
    }else{printf(" %d", e->stats[2]);}
    printf("\n___________________________________________________________________________________________\n");
}

void print_player(Character* p){
    printf("\n___________________________________________________________________________________________\n");
    printf("- You (%s)\n", p->name);
    printf("HP: ");
    for(int i=0;i<(p->stats[2])/2;i++){printf("|");}
    if(p->stats[1]>0){
        for(int i=0;i<(p->stats[1])/2;i++){printf("]");}
        printf(" %d", p->stats[2]);
        printf(" + [%d]", p->stats[1]);
    }else{printf(" %d", p->stats[2]);}
    printf("\n___________________________________________________________________________________________\n");
}

/////////////////////////////////////////////7

int attack(Skill* skll, char*n_atck, char*n_def, int*stats_a, int*stats_d, int max_hp, int* venom){
    int dmg = (skll->of_def)*(skll->dmg_skll + stats_a[0]);
    printf("%s used %s", n_atck, skll->name);

    if(skll->mod.chr == 'd'){
        stats_a[1]+=skll->dmg_skll;
        printf("%s gained %d defense\n\n", n_atck, skll->dmg_skll);
    }else if(skll->mod.chr == 'h'){
        stats_a[2]+=skll->dmg_skll;
        printf("%s healed %d\n\n", n_atck, skll->dmg_skll);
        if(stats_a[2]>max_hp){stats_a[2]=max_hp;}
    }else if(skll->mod.chr == 'v'){*venom = 3;}
   

    if(*venom>0){dmg+=stats_a[0];}
    if(stats_d[1]>0){
        stats_d[1]-= dmg;
        if(stats_d[1]<=0){stats_d[1]=0;printf("Defense broken\n");}
    }else{
        stats_d[2]-= dmg;
        if(stats_d[2]<=0){stats_d[2]=0;;return 1;}
    }
    if(skll->of_def==1){printf("%s dealt %d damage to %s\n\n", n_atck, dmg, n_def);}
    if(*venom>0){printf("\n%s received %d of residual damage\n\n", n_def, stats_a[0]);*venom--;}
    if(skll->mod.chr == 's'){
        printf("%s has been stunned, they can't attack next round", n_def);
        return 2;
    }
    return 0;

}

/////////////////////////////////////////////7

int combat(Character *plyr, Enemy *enmy, int size){
    Queue* q = init_queue(size);
    for(int i = 0; i<size; i++){
        q = enqueue(q, *plyr, *enmy);
    }
    int a;
    int rand_n = rand()+1;//Fix random number always 41

    int result;
    int pvenom = 0;
    int evenom = 0;
    int max_hp_plyr = 0;
    for(int i = 0; i<4; i++){max_hp_plyr += plyr->skill[i].stats_plyr[2];}
    int max_hp_enmy = enmy->stats[2];
    plyr->stats[1] = 0;
    for(int i=0;i<4;i++){
        enmy->skill[i].mod.n = 0;

//We need to reset the enemy's health and defense after each death
        plyr->skill[i].mod.n = 0; //Reset counter limited uses skills
        plyr->stats[1]+=plyr->skill[i].stats_plyr[1];//Reset defense
    }
        

    while(q->elements>0){
        print_enemy(enmy);
        printf("\n");//Print enemy?
        print_player(plyr);
        
/////////////////////////////////////////////7
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

        result = attack(&plyr->skill[a], plyr->name, enmy->name, plyr->stats, enmy->stats, max_hp_plyr, &pvenom);

        if(result == 1){printf("You won the fight against %s\nCongratulations!\n", enmy->name);return 1;}
        else if(result == 2){
            dequeue(q);
            printf("%d turns remaining\n", q->elements);
            goto choose_skill;
        }

        dequeue(q);
        printf("%d turns remaining\n", q->elements);

/////////////////////////////////////////////7

        print_enemy(enmy);
        printf("\n");//Print enemy?
        print_player(plyr);

/////////////////////////////////////////////7
        pause();
    enemy_combat:
        int rand_t = rand();
        int b = rand_t%4;
        int e_dmg = (enmy->skill[b].dmg_skll + enmy->stats[0])*enmy->skill[b].of_def;

        if((enmy->skill[b].mod.n==enmy->skill[b].mod.max)&&(enmy->skill[b].mod.chr!='n')){goto enemy_combat;}
        enmy->skill[b].mod.n++;

        result = attack(&enmy->skill[b], enmy->name, plyr->name, enmy->stats, plyr->stats, max_hp_enmy, &evenom);

        if(result==1){printf("You lost against %s\nTry again next time\n", enmy->name);return 2;}
        else if(result==2){
            dequeue(q);
            printf("%d turns remaining\n", q->elements);
            goto enemy_combat;
        }

    end_combat:
        dequeue(q);
        printf("%d turns remaining\n", q->elements);
    }
}