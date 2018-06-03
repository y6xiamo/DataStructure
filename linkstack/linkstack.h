#pragma once

#include<stddef.h>

typedef char LinkStackType;

typedef struct LinkStackNode
{
	LinkStackType  data;
	struct LinkStackNode* next;
}LinkStackNode;

typedef struct LinkStack
{
	LinkStackNode* pTop;//栈顶指针
	LinkStackNode* pBottom;//栈底指针
}Stack,*pStack

void LinkStackiInit(pStack s);//初始化

void LinkStackDestroy(pStack s);//销毁

void LinkStackPush(pStack s,LinkStackType* value);//入栈

void LinkStackPop(pStack s);//出栈

void LinkSatckFron(pStack s,LinkStackType* value);//取栈顶元素



