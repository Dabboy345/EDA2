#ifndef _QUEUE_H_
#define _QUEUE_H_ // In this libary we have our queueus
#include "common.h"

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
	

#endif