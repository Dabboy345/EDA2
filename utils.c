#include "utils.h"

//////////////////GRAPH//////////////////////////////////

void init_adj_mat_scenario(Scenario* scene, int max_node){
    int j = 0;
    for(int i=1;i<=max_node;i++){
        scene->edges[j][0]= i;
        scene->edges[j][1]= j+2;
        j++;
        scene->edges[j][0]= i;
        scene->edges[j][1]= j+2;
        j++;
    }       
}

int get_next_num_node(int opt, int node_num, Scenario* scene, int max_node){
    for(int i=0;i<=(max_node*2)+1;i++){
        if(scene->edges[i][0]==node_num){
            return scene->edges[i+(opt-1)][1];
        }
    }
}

//////////////////QUEUE//////////////////////////////////

Queue* init_queue(){
    Queue *q = (Queue*)malloc(sizeof(Queue));
	q->head = 0;
	q->tail = 0;
	q->elements= 0;
	return q;
}
	
Queue* enqueue(Queue* q, Character c, Enemy e){
    q->c[q->tail] = c;
    q->e[q->tail] = e;
    q->tail = q->tail + 1;
    q->elements = q->elements + 1;
    return q;
}

Queue* dequeue(Queue* q){
	q->head = q->head + 1;
	q->elements = q->elements-1;
    return q;
}

//////////////////STACK//////////////////////////////////
Timestrike *createTimestrike(int capacity){
    Timestrike* stack = (Timestrike*)malloc(sizeof(Timestrike));
    stack->capacity = capacity;
    stack->top=-1;
    stack->arr = (Skill*)malloc(stack->capacity * sizeof(Skill));
    return stack;
}
// Stack is full when top is equal to the last index
bool isFull(Timestrike *stack){
    return (stack->top == stack->capacity - 1);
}

// Stack is empty when top is equal to -1
bool isEmpty(Timestrike* stack){
    return (stack->top == -1);
}

void push(Timestrike* stack, Skill skill){
    if (isFull(stack)){return;}
    stack->top++;
    stack->arr[stack->top] = skill;
}

Skill pop(Timestrike* stack){
    if (isEmpty(stack))
        return;
    stack->top--;
    return stack->arr[stack->top+1];
}

// Function to return the top from stack without removing it
Skill peek(Timestrike* stack){
    if (isEmpty(stack))
        return;
    return stack->arr[stack->top];
}


