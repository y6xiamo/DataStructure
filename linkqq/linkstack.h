#pragma once

#include<stddef.h>

typedef char LinkStackType;

typedef struct LinkStackNode
{
	LinkStackType data;
	struct LinkStackNode* next;
}LinkStackNode;

LinkStackNode* phead;

void LinkStackInit(LinkStackNode** phead);//链式栈初始化

void LinkStackPush(LinkStackNode** phead,LinkStackType value);//入栈

void LinkStackPop(LinkStackNode** phead);//出栈

int LinkStackTop(LinkStackNode* phead,LinkStackType* value);//取栈顶元素
