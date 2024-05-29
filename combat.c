#include "combat.h"

void print_enemy(Enemy* e){//Function to print the hp and def of the enemy
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

void print_player(Character* p){//Function to print the hp and def of the player
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

//Function to execute the attack
//a-atck is the one who uses the skill and d-def is the receiver
int attack(Skill* skll, char*n_atck, char*n_def, int*stats_a, int*stats_d, int max_hp, int* venom, int* prob, Timestrike* stack){
    printf("\n%s used %s\n", n_atck, skll->name); //print the skill used
    if(skll->mod.chr == 't'){//The hability is Timestrike
        int t = rand()%(stack->top-1);//Choose a random hability from the stack
        Skill* skill_time = (Skill*)malloc(sizeof(Skill));//Create a new pointer of skill to change the damage without changing the original skill
        *skill_time = stack->arr[t];//We copy the randomly selected skill in the new pointer
        skill_time->dmg_skll*=2;//We double the damage
        printf("Random hability chosen %s\n", skill_time);
        return attack(skill_time, n_atck, n_def, stats_a, stats_d, max_hp, venom, prob, stack);//Return the result of the random skill to end the attack funtion
    }else if(skll->mod.chr == 'r'){//If mod is recharge
        if(skll->of_def==1){//If of_def is 1, it's not charged
            skll->of_def=0;//Change of_def so it doesn't deal dmg when is not charged
            printf("Charging %s...\n\n", skll->name);
        }
        else{skll->of_def=1;printf("%sis charged\n\n", skll->name);}//If of_def is 0, it's charged
        //Change of_def so it  deals dmg when is charged
    }else if(skll->mod.chr == 'f'){//If mod is force 
        printf("%s feels %d times stronger\n\n", n_atck, skll->dmg_skll);
        stats_a[0]+=skll->dmg_skll;//We increase the main attacker damage to make their attacks stronger
    }

    int dmg = (skll->of_def)*(skll->dmg_skll + stats_a[0]);//We calculate the total damage of the skill

    if(skll->mod.chr == 'd'){//If mod is defense
        stats_a[1]+=skll->dmg_skll;//We increase the main attacker defense
        printf("%s gained %d defense\n\n", n_atck, skll->dmg_skll);
    }else if(skll->mod.chr == 'h'){//If mod is healing
        stats_a[2]+=skll->dmg_skll;//We increase the main attacker health
        printf("%s healed %d\n\n", n_atck, skll->dmg_skll);
        if(stats_a[2]>max_hp){stats_a[2]=max_hp;}//We ensure that the new healed hp isn't greater than the hp the attacker initially had upon creation
    }else if(skll->mod.chr == 'v'){*venom = 3;}//If mod is venom
    //We set venom to 3, (during 3 turns the enemy will receive some damage)
    
    int prob_attack = rand()%100;//Number from 0 to 99 to calculate the probability of dealing damage

    if(*venom>0){dmg+=stats_a[0];}//If venom is not 0, there is still venom turns that the opponent will receive extra damage
    if(*prob<=prob_attack){//Probability by default is 0, 100% of dealing damage
        if(stats_d[1]>0){//If the opponent still has defense
            stats_d[1]-= dmg;//Deal all damage to defense
        //Until the defense is down, the attacker cannot damage the health, is like a shield of damage
        //If opponent has 1 def and the dmg of the skill is 100, it will only break the def, not damage the skill
            if(stats_d[1]<=0){
                stats_d[1]=0;
                printf("Defense broken\n\n");
            }//When def negative set it to 0
        }else{//When no defense it can damage the health
            stats_d[2]-= dmg;//Deal damage to health
            if(stats_d[2]<=0){
                stats_d[2]=0;
                return 1;
            }//When hp negative set it to 0, return 1(attacker won)
        }
    }
    //If skill->of_def is 0 de skill doesn't deal damage, other wise if it's one it deals damage
    if(skll->of_def==1 && *prob<=prob_attack){
        printf("%s dealt %d damage to %s\n\n", n_atck, dmg, n_def);
    }
    else if(skll->of_def==1 && *prob>prob_attack){
        printf("%s avoided the attack\n\n", n_def);
    }if(*venom>0){
        printf("\n%s received %d of residual damage\n\n", n_def, stats_a[0]);
        *venom--;//We decrease the turns until venom reaches 0 and doesn't deal damage anymore
    }
    if(skll->mod.chr == 's'){//If modifier is stun
        printf("%s has been stunned, they can't attack next round\n\n", n_def);
        *prob = 0;//Set prob to 0 before return
        return 2;//Return 2 because the attacker will attack 2 times in a row because opponent is stunned
    }else if(skll->mod.chr == 'p'){//If modifier probability
        printf("There is a chance of %d%% to avoid being attacked", skll->dmg_skll*3);
        *prob = skll->dmg_skll*3;//Calculate the probability of 100 to avoid an attack, avoids the damage not the effect
        return 0;
    }
    *prob = 0;//Set prob to 0 before return
    return 0;//Nobody died, the combat continues

}

/////////////////////////////////////////////7

int combat(Character *plyr, Enemy *enmy, int size, Timestrike *stack){
    //initialize the queue of the combat
    Queue* q = init_queue(size);
    for(int i = 0; i<size; i++){
        q = enqueue(q, *plyr, *enmy);
    }
    int a;//Initialize varible for choosing skill of player
    int rand_n = rand();//Get random number to decide who starts

    int prob=0;//Set probability of avoiding attack to 0 (default)
    int result; //Initialize  result of an attack
    int pvenom = 0;//Number of turns the venom will have effect on the enemy (enemy receives extra damage)
    int evenom = 0;//Number of turns the venom will have effect on the player (player receives extra damage)
    int max_hp_plyr = 0;//Set the max hp to get the max hp from the stats_plyr[2] of the 4 skills
    int max_hp_enmy = 0;
    
    for(int i = 0; i<4; i++){
        max_hp_plyr += plyr->skill[i].stats_plyr[2];//Add the part of skill that gives the health to the player
        max_hp_enmy += enmy->skill[i].stats_plyr[2];
        if(plyr->skill[i].mod.chr == 'r'){plyr->skill[i].of_def=1;}//Reset the skills with recgarge modifier to uncharged
        if(enmy->skill[i].mod.chr == 'r'){enmy->skill[i].of_def=1;}
    }
    enmy->stats[2]=max_hp_enmy;//Enemy always start full health
    
    for(int i = 0; i<2; i++){//Reset damage and def of player and enemy to set it to their original values
    //Def always resets after each combat and damage migth be altered because of a force modifier
        plyr->stats[i] = 0;
        enmy->stats[i] = 0;
    }
    
    
    for(int i=0;i<4;i++){
        enmy->skill[i].mod.n = 0;//Reset counter limited uses skills
        enmy->stats[1]+=enmy->skill[i].stats_plyr[1];//Reset defense
        enmy->stats[0]+=enmy->skill[i].stats_plyr[0];//Reset damage

        plyr->skill[i].mod.n = 0; //Reset counter limited uses skills
        plyr->stats[1]+=plyr->skill[i].stats_plyr[1];//Reset defense
        plyr->stats[0]+=plyr->skill[i].stats_plyr[0];//Reset damge
    }
    int turn=rand()%2;//Get a random number from 0 to 1 (0 or 1)
    if(turn == 0){printf("The player %s starts\n\n", plyr->name);//Say who starts
    }else{printf("The enemy %s starts\n\n", enmy->name);}

///////////////////////////////////////////////////////////////////////////7

    while(q->elements>0){//While loop until queue is empty
        if(turn==0){
            print_enemy(enmy);//Print visual representation of the characters in the combat
            printf("\n");
            print_player(plyr);
            for(int i = 0;i<4;i++){//Iterate through every skill
                if((plyr->skill[i].mod.n!=plyr->skill[i].mod.max)||(plyr->skill[i].mod.chr=='n')){break;}
            //We look if the player is stuck and can't use any hability because he ran out of uses per combat
            //Habilities with modifiers have limited uses
                if(i==3){
                    printf("\nYou lost against %s because you ran out of skills\nTry again next time\n", enmy->name);
                    return 2;//Return 2, enemy wins
                }
            }
            

        choose_skill:
            for(int j = 0; j<4; j++){printf("%d - %s",j+1, plyr->skill[j]);}//Print the skills available
            printf("Choose skill: ");
            a = get_valid_input(1,4);//Choose a skill
            a--;

    /////////////////////////////////////////////7

            if((plyr->skill[a].mod.n==plyr->skill[a].mod.max)&&(plyr->skill[a].mod.chr!='n')){
                printf("You cannot use that hability again\n");
                //Check if you can use the hability (habilities with n modifier (normal) infinite uses)
                goto choose_skill;}//If you can't choose that hability go back to choose another one
            plyr->skill[a].mod.n++;//Add one use the the skill for the limited uses of the mod skills

            push(stack, plyr->skill[a]);//Push the hability used to the stack for timestrike skill

            result = attack(&plyr->skill[a], plyr->name, enmy->name, plyr->stats, enmy->stats, max_hp_plyr, &pvenom, &prob, stack);
            //Result from attack

            if(result == 1){
                printf("\nYou won the fight against %s\nCongratulations!\n\n", enmy->name);
                return 1;//If result is one attacker won, so player won
            }
            else if(result == 2){
                //If result is 2, opponent can't attack (stun modifier)
                turn = 0;//Turn is 0 so player attacks again
            }else{turn = 1;}//Change the turn to one, meaning

            dequeue(q);//dequeue the turn
            printf("\n%d turns remaining\n", q->elements);//Change the turn to one, meaning
        }   

        if(turn==1){
            print_enemy(enmy);//Print visual representation of the characters in the combat
            printf("\n");
            print_player(plyr);
            pause();//Pause function to let the player see the effect of their attack

        enemy_combat:
            int rand_t = rand();
            int b = rand_t%4;//Get a random number from 0 to 3 to choose a random skill

            if((enmy->skill[b].mod.n==enmy->skill[b].mod.max)&&(enmy->skill[b].mod.chr!='n')){goto enemy_combat;}
            enmy->skill[b].mod.n++;
            //If the skill chosen has modifier and no more uses get another random number until it chooses an hability you can use
            //Enemy won't get stuck since it always have an skill without modifier

            result = attack(&enmy->skill[b], enmy->name, plyr->name, enmy->stats, plyr->stats, max_hp_enmy, &evenom, &prob, stack);
            //Get the result of the attack

            if(result==1){
                printf("\nYou lost against %s\nTry again next time\n", enmy->name);
                return 2;//If result is one attacker won, so enmy won
            }

            else if(result==2){
                turn = 1;//Player is stunned so enemy attacks again
            }else{turn = 0;}//Change turn to allow player to attack
            dequeue(q);//Dequeue the turn
            printf("\n%d turns remaining\n", q->elements);
            
        }
    }
}