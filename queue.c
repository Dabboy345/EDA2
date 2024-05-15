#include "queue.h"
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