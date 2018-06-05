#pragma once
#include<stdint.h>

#include<stddef.h>

//#define FOR_MAZE
//#ifdef FOR_MAZE
//typedef struct Point
//{
//	int ROW;
//	int COL;
//}Point;
//typedef Point SeqStackType;
//#else

typedef int64_t SeqStackType;
//#endif
typedef struct SeqStack
{
	SeqStackType* data;
    size_t size;
	size_t capacity;//data这段内存中能容纳的元素个数
}SeqStack;

void SeqStackInit(SeqStack* stack);//初始化

void SeqStackDestroy(SeqStack* stack);//销毁

void SeqStackReSize(SeqStack* stack);//重新设置大小

void SeqStackPush(SeqStack* stack,SeqStackType value);//压栈

void SeqStackPop(SeqStack* stack);//出栈

//返回两个信息：执行成功失败，栈顶元素是多少
int SeqStackTop(SeqStack* stack,SeqStackType* value);//取栈顶元素，value输出型参数
