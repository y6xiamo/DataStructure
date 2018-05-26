#pragma once

#include<stddef.h>

#define SeqQueueMaxSize 1000

typedef char SeqQueueType;

typedef struct SeqQueue
{
	SeqQueueType data[SeqQueueMaxSize];
	size_t head;
	size_t tail;
	size_t size;
}SeqQueue;

void SeqQueueInit(SeqQueue* q);//初始化

void SeqQueueDestroy(SeqQueue* q);//销毁

void SeqQueuePush(SeqQueue* q,SeqQueueType value);//入队列

void SeqQueuePop(SeqQueue* q);//出队列

int SeqQueueFront(SeqQueue* q,SeqQueueType* value);
