#include "common.h"
#include "rpg_game.h"
#include "prints.h"

void try_skill(Skill *skll){
    printf("Health points: %d\n", skll->stats_plyr[2]);
    for(int i = 0; i<skll->stats_plyr[2]; i++){printf("/");}
    printf("\n");
    printf("Defense: %d\n", skll->stats_plyr[1]);
    for(int i = 0; i<skll->stats_plyr[1]; i++){printf("/");}
    printf("\n");
    printf("Damage: %d\n", skll->stats_plyr[0]);
    for(int i = 0; i<skll->stats_plyr[0]; i++){printf("/");};
    printf("\n");
    if(skll->of_def==0){printf("%d def or heal?\n", skll->dmg_skll);}
    else if(skll->of_def==1){printf("%d damage dealt\n", skll->dmg_skll);};
    printf("It has %s modifier\n", skll->modifier);
}

Character* create_character(Skill *skills){
    Character *player = (Character*)malloc(sizeof(Character));
    printf("Choose you character's name: ");
    scanf("%s", &player->name);
    //Choose skills

    //print all skills
    for(int i = 0; i<20; i++){
        printf("%d.-%s",i+1, skills[i].name);
    }

    printf("\n");
    int temp=1;
    int test=0;
    while(temp!=0){
        printf("Try a skill (1-20): ");
        test = scanf("%d", &temp);
        if((test!=0)&&(1<=temp) && (temp<=20)){
            try_skill(&(skills[temp]));
        }else{printf("Wrong input\n");}//When typing a letter it crashes
        
    }
   
    //create a function to try a skill "try_skill(skills[20], n)" n = number of skill
    //                                  description + test
    //...
    
    for(int i = 0; i<4; i++){
        printf("Choose a skill %d: ", i+1);
        scanf("%d", &temp); //We need to code so that the player can't have repeated skills
        player->skill[i] = skills[temp-1];
        printf(" %s\n", &(player->skill[i].name));

    }
    
    for(int i = 0; i<3; i++){
        temp = 0;
        for(int j = 0; j<4; j++){
            temp += player->skill[j].stats_plyr[i]; //With errors
        }
        player->stats[i] = temp;
    }
    return player;
}

void get_skill(Skill skill[]){
    FILE *fp;
    int i = 0;
    char c[MAX_NAME];
    fp = fopen("list_character_skill.txt", "r");
    while(!feof(fp)){
        fgets((skill[i]).name, MAX_NAME, fp);
        fgets((skill[i]).description, MAX_TXT, fp);
        fscanf(fp, "%d\n", &(skill[i]).of_def);
        fscanf(fp, "%d\n", &(skill[i]).dmg_skll);
        fgets((skill[i]).modifier, MAX_NAME, fp);
        fscanf(fp, "%d, %d, %d\n", &(skill[i]).stats_plyr[0], &(skill[i]).stats_plyr[1], &(skill[i]).stats_plyr[2]);
        
        printf("-%s\n", (skill[i]).name);
        printf("%s\n", (skill[i]).description);
        printf("%d\n", (skill[i]).of_def);
        printf("%d\n", (skill[i]).dmg_skll);
        printf("%s\n", (skill[i]).modifier);
        printf("%d, %d, %d\n", (skill[i]).stats_plyr[0], (skill[i]).stats_plyr[1], (skill[i]).stats_plyr[2]);
        i++;
    }
    fclose(fp); 
}

Node* get_node(int i1, int i2, Node* node){
    FILE *fp;
    int a = 0;
    int b = 0;
    fp = fopen("option.txt", "r");

    while (a!=i1 && b!=i2){fscanf(fp, "%d.%d\n", &a, &b);}
    while(!feof(fp)){
        //fgets((skill[i]).name, MAX_NAME, fp);
    fclose(fp); 
    } 
}

