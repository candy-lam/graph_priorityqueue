/*
* File: priorityQueue.h
*/
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <stdbool.h>

typedef struct priorityQueueCDT *priorityQueueADT;\
typedef float pQueueElementT ;

priorityQueueADT EmptyPriorityQueue(void);
void PriorityEnqueue(priorityQueueADT, pQueueElementT);
pQueueElementT PriorityDequeue(priorityQueueADT);
bool PriorityQueueIsEmpty(priorityQueueADT);


#endif // PRIORITYQUEUE_H
