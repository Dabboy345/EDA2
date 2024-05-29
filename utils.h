#ifndef _UTILS_H_
#define _UTILS_H_

#include "common.h"

void init_adj_mat_scenario(Scenario* scene, int max_node);
int get_next_num_node(int opt, int node_num, Scenario* scene, int max_node);

typedef struct{
    int head;
    int tail;
    int elements;
    Character c[MAX_NAME];
    Enemy e[MAX_NAME];
}Queue;

Queue* init_queue();
	
Queue* enqueue(Queue* q, Character c, Enemy e);

Queue* dequeue(Queue* q);

typedef struct{ 
    int capacity;
    int top;
    Skill *arr;
}Timestrike;

Timestrike *createTimestrike(int capacity);

bool isFull(Timestrike *stack);

bool isEmpty(Timestrike* stack);

void push(Timestrike* stack, Skill skill);

Skill pop(Timestrike* stack);

Skill peek(Timestrike* stack);

#endif