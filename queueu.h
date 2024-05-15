#ifndef _QUEUEU_H_
#define _QUEUEU_H_ // In this libary we have our queueus
#include "common.h"

typedef struct{
    int head;
    int tail;
    int elements;
    Character* c;
    Enemy* e;
}Queueu;

Queueu* init_queue(){
    Queueu *q = (Queueu*)malloc(sizeof(Queueu));
	q->head = 0;
	q->tail = 0;
	q->elements= 0;
	return q;
}
	
Queueu* enqueue(Queueu* q, Character c, Enemy e){
    q->c[q->tail] = c;
    q->e[q->tail] = e;
    q->tail = q->tail + 1;
    q->elements = q->elements + 1;
    return q;
}

Queueu* dequeue(Queueu* q){
	q->head = q->head + 1;
	q->elements = q->elements-1;
    return q;
}
	




#endif