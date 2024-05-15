#ifndef _RPGGAME_H_ //Here will put the functions regarding the funcionality of the game 
#define _RPGGAME_H_

#include "common.h"
#include "queue.h"

void try_skill(Skill *skll);

void get_skill(Skill *skill, int n);

Character* create_character(Skill *skills);

void combat(Character *plyr, Enemy *enmy, int size);

Node* get_node(int i, Node* node);

Node *create_node();

void add_Node_right( Node *root/*We could other valrable*/);

void add_Node_left(Node *root);

#endif  