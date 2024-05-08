#include "common.h"
#include"rpg_game.h"

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



