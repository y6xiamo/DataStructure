#pragma once

#include<stddef.h>

typedef char LinkType;

typedef struct LinkNode
{
	LinkType data;
	struct LinkNode* next;
}LinkNode;

typedef struct LinkQueue
{
	LinkNode* head;
	LinkNode* tail;
}LinkQueue;

void LinkQueueInit(LinkQueue* queue);//初始化

void LinkQueueDestroy(LinkQueue* queue);//销毁

void LinkQueuePush(LinkQueue* queue,LinkType value);//入队列

void LinkQueuePop(LinkQueue* queue);//出队列

int LinkQueueFront(LinkQueue* queue,LinkType* value);//取队首元素
