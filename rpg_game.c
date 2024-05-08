#include "common.h"
#include"rpg_game.h"
void try_skill(Skill *skll){
    printf("\nHealth points: %d\t", skll->stats_plyr[2]);
    for(int i = 0; i<skll->stats_plyr[2]; i++){printf("|");}
    printf("\nDefense: %d\t", skll->stats_plyr[1]);
    for(int i = 0; i<skll->stats_plyr[1]; i++){printf("|");}
    printf("\nDamage: %d\t", skll->stats_plyr[0]);
    for(int i = 0; i<skll->stats_plyr[0]; i++){printf("|");};
    printf("\n");
    if(skll->of_def==0){printf("%d damage dealt\n", skll->dmg_skll);}
    else if(skll->of_def==1){printf("%d damage dealt\n", skll->dmg_skll);};
}
Character* create_character(Skill *skills){
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

Node *create_node(){//This function will create us a tree
    Node *root = (Node*)malloc(sizeof(Node));
    root->left = NULL;
    root->right = NULL;
    return root;
}

void add_Node_right( Node *root/*We could other valrable*/){ //This function enables to add new node to our tree
    Node *new = create_node();
    root->right = new;
}

void add_Node_left(Node *root){
    Node *new =  create_node();
    root->left = new;
}

/*void do_option(int n_opt, Decision* main_d){
    printf("%s\n", main_d->option[n_opt].pre_txt);

    //Combat

    printf("%s\n", main_d->option[n_opt].post_txt);
}

void do_decision(Decision* main_d){
    printf("%s\n", main_d->question_txt);
    printf("Would you like to %s (1) or to %s (2)?\n", main_d->option[1].description, main_d->option[2].description);
    int opt;
    scanf("%d", opt);
    do_option(opt-1, main_d);
}*/


