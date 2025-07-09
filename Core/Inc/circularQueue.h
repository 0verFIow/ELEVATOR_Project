/*
* circularQueue.h
*
*/
#ifndef CIRCULARQUEUE_H_
#define CIRCULARQUEUE_H_

#include "main.h"

#define TRUE 1
#define FALSE 0
#define QUEUE_MAX 10

int queue_empty(void);
int queue_full(void);
void insert_queue(int value);
unsigned char read_queue();

#endif /* CIRCULARQUEUE_H_ */
