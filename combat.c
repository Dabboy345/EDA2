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

int combat(Character *plyr, Enemy *enmy, int size){
    Queue* q = init_queue(size);
    for(int i = 0; i<size; i++){
        q = enqueue(q, *plyr, *enmy);
    }
    int a;
    int rand_n = rand()+1;//Fix random number always 41

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

        if(plyr->skill[a].mod.chr == 'd'){
            plyr->stats[1]+=plyr->skill[a].dmg_skll;
            printf("%s gained %d defense\n\n", plyr->name, plyr->skill[a].dmg_skll);
        }else if(plyr->skill[a].mod.chr == 'h'){
            plyr->stats[2]+=plyr->skill[a].dmg_skll;
            printf("%s healed %d\n\n", plyr->name, plyr->skill[a].dmg_skll);
            if(plyr->stats[2]>max_hp_plyr){plyr->stats[2]=max_hp_plyr;}
        }else if(plyr->skill[a].mod.chr == 'v'){pvenom = 3;}
        else if(plyr->skill[a].mod.chr == 's'){
            
        }

/////////////////////////////////////////////7

        if(pvenom>0){p_dmg+=plyr->stats[0];}
        if(enmy->stats[1]>0){
            enmy->stats[1]-= p_dmg;
            if(enmy->stats[1]<=0){enmy->stats[1]=0;printf("Defense broken\n");}
        }else{
            enmy->stats[2]-= p_dmg;
            if(enmy->stats[2]<=0){enmy->stats[2]=0;
            printf("You won the fight against %s\nCongratulations!\n", enmy->name);return 1;}//Return 1 = playr wins
        }
        if(plyr->skill[a].of_def==1){printf("%s dealt %d damage to %s\n\n", plyr->name, p_dmg, enmy->name);}
        if(pvenom>0){printf("\n%s received %d of residual damage\n\n", enmy->name, plyr->stats[0]);pvenom--;}

        dequeue(q);
        printf("%d turns remaining\n", q->elements);

/////////////////////////////////////////////7

        print_enemy(enmy);
        printf("\n");//Print enemy?
        print_player(plyr);

/////////////////////////////////////////////7

    enemy_combat:
        int rand_t = rand();
        int b = rand_t%4;
        int e_dmg = (enmy->skill[b].dmg_skll + enmy->stats[0])*enmy->skill[b].of_def;

/////////////////////////////////////////////7

        if((enmy->skill[b].mod.n==enmy->skill[b].mod.max)&&(enmy->skill[b].mod.chr!='n')){goto enemy_combat;}
        enmy->skill[a].mod.n++;

        if(enmy->skill[b].mod.chr == 'd'){
            enmy->stats[1]+=enmy->skill[b].dmg_skll;
            printf("%s gained %d defense\n\n", enmy->name, enmy->skill[b].dmg_skll);
        }else if(enmy->skill[b].mod.chr == 'h'){
            enmy->stats[2]+=enmy->skill[b].dmg_skll;
            printf("%s healed %d\n\n", enmy->name, enmy->skill[b].dmg_skll);
            if(enmy->stats[2]>max_hp_enmy){enmy->stats[2]=max_hp_enmy;}
        }else if(enmy->skill[b].mod.chr == 'v'){evenom = 3;}
        else if(enmy->skill[b].mod.chr == 's'){
            
        }

/////////////////////////////////////////////7

        if(evenom>0){e_dmg += enmy->stats[0];}
        if(plyr->stats[1]>0){
            plyr->stats[1]-= e_dmg;
            if(plyr->stats[1]<0){plyr->stats[1]=0;printf("Defense broken\n");}
        }else{
            plyr->stats[2]-= e_dmg;
            if(plyr->stats[2]<=0){plyr->stats[2]=0;
            printf("You lost against %s\nTry again next time\n", enmy->name);return 2;}//Return 2 = Enemy wins
        }
        if(enmy->skill[b].of_def==1){
            printf("%s dealt %d damage to %s\n\n", enmy->name, e_dmg, plyr->name);
            if(evenom>0){printf("\n%s received %d of residual damage\n\n", plyr->name, enmy->stats[0]);evenom--;}
        }  

    end_combat:
        dequeue(q);
        printf("%d turns remaining\n", q->elements);
    }
    
    

}