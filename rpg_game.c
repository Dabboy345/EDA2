#include"rpg_game.h"

Character* create_character(Skill skills[20]){
    Character *player = (Character*)malloc(sizeof(Character));
    printf("Choose you character's name: \n");
    scanf("%s", &player->name);
    //Choose skills

    //print all skills
    for(int i = 0; i<20; i++){
        printf("%s\t", skills[i].name);
    }
    //create a function to try a skill "try_skill(skills[20], n)" n = number of skill
    //                                  description + test
    //...
    int temp;
    for(int i = 0; i<4; i++){
        scanf("Choose a skill: %d", &temp); //We need to code so that the player can't have repeated skills
        player->skill[i] = skills[temp];

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

execute_option(Option* opt, Decision* main_d){
    printf("%s\n", opt->description);
    printf("%s\n", opt->pre_txt);

    //Combat

    printf("%s\n", opt->post_txt);

}