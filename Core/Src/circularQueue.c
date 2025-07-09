/*
* circularQueue.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "circularQueue.h"
#include "extern.h"

#define TRUE 1
#define FALSE 0
#define QUEUE_MAX 10

int front1=-1;  // read index
int rear1=-1;   // insert index
int queue[QUEUE_MAX];

int queue_empty(void)
{
	if (front1==rear1) //front와 rear가 같으면 큐는 비어있는 상태
	     return TRUE;
	else return FALSE;
}

int queue_full(void)
{
	int tmp=(rear1+1)%QUEUE_MAX; //원형 큐에서 rear+1을 MAX로 나눈 나머지값이
	if (tmp == front1) //front와 같으면 큐는 가득차 있는 상태
		return TRUE;
	else
		return FALSE;
}
void insert_queue(int value)
{
	if (queue_full())
	{
		printf("Queue is Full.\n");
	}
	else
	{
		rear1 = (rear1+1) % QUEUE_MAX;
		queue[rear1]=value;
	}

}
int check_queue(void)
{
	return queue[rear1];
}

void de_queue()
{
	if (queue_empty())
		printf("Queue is Empty.\n");
	else
	{
		front1 = (front1+1) % QUEUE_MAX;
	}
}

void queue_init() // 텅 빈 경우 front와 rear은 동일위치 가리킴
{
	front1 = -1;
	rear1 = -1;
}
