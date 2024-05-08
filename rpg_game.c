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



