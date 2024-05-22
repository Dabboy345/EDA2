#include "combat.h"

void print_enemy(Enemy* e){
    printf("\n________________________________________________________________________________\n");
    printf("- %s\n", e->name);
    printf("HP: ");
    for(int i=0;i<(e->stats[2]+1)/2;i++){printf("|");}
    if(e->stats[1]>0){
        for(int i=0;i<(e->stats[1]+1)/2;i++){printf("]");}
        printf(" %d", e->stats[2]);
        printf(" + [%d]", e->stats[1]);
    }else{printf(" %d", e->stats[2]);}
    printf("\n________________________________________________________________________________\n");
}

void print_player(Character* p){
    printf("\n________________________________________________________________________________\n");
    printf("- You (%s)\n", p->name);
    printf("HP: ");
    for(int i=0;i<(p->stats[2])/2;i++){printf("|");}
    if(p->stats[1]>0){
        for(int i=0;i<(p->stats[1])/2;i++){printf("]");}
        printf(" %d", p->stats[2]);
        printf(" + [%d]", p->stats[1]);
    }else{printf(" %d", p->stats[2]);}
    printf("\n________________________________________________________________________________\n");
}

int combat(Character *plyr, Enemy *enmy, int size){
    Queue* q = init_queue(size);
    for(int i = 0; i<size; i++){
        q = enqueue(q, *plyr, *enmy);
    }
    int a;
    int rand_n = rand()+1;//Fix random number always 41

    while(q!=NULL){
        print_enemy(enmy);
        printf("\n\n\n");//Print enemy?
        print_player(plyr);
        
/////////////////////////////////////////////7

        for(int j = 0; j<4; j++){printf("%d - %s",j+1, plyr->skill[j]);}
        printf("Choose skill: ");
        scanf("%d", &a);
        a--;

/////////////////////////////////////////////7

        int p_dmg = (plyr->skill[a].of_def)*(plyr->skill[a].dmg_skll + plyr->stats[0]);//Segmentation fault?
        char def = 'd';
        char heal = 'h';
        if(plyr->skill[a].mod == def){
            plyr->stats[1]+=plyr->skill[a].dmg_skll;
        }else if(plyr->skill[a].mod == heal){
            plyr->stats[2]+=plyr->skill[a].dmg_skll;

        }

        if(enmy->stats[1]>0){
            enmy->stats[1]-= p_dmg;
            if(enmy->stats[1]<=0){enmy->stats[1]=0;printf("Defense broken\n");}
        }else{
            enmy->stats[2]-= p_dmg;
            if(enmy->stats[2]<0){enmy->stats[2]=0;printf("GG");return 1;}//Return 1 = playr wins
        }
        if(plyr->skill[a].of_def==1){
            printf("%s dealt %d damage to %s\n\n", plyr->name, p_dmg, enmy->name);
        }    

/////////////////////////////////////////////7

        int rand_t = rand();
        int b = 0; //rand_t%4;
        int e_dmg = (enmy->skill[b].dmg_skll + enmy->stats[0])*enmy->skill[b].of_def;



        if(plyr->stats[1]>0){
            plyr->stats[1]-= e_dmg;
            if(plyr->stats[1]<0){plyr->stats[1]=0;printf("Defense broken\n");}
        }else{
            plyr->stats[2]-= e_dmg;
            if(plyr->stats[2]<0){plyr->stats[2]=0;printf("FFFFF");return 2;}//Return 2 = Enemy wins
        }
        if(enmy->skill[b].of_def==1){
            printf("%s dealt %d damage to %s\n\n", enmy->name, e_dmg, plyr->name);
        }  

        dequeue(q);
        printf("\n-_------____----_____---------_____--_____------_____---_____\n");
    }
    
    

}