#pragma once

#include<stddef.h>

//动态扩容，最大尺寸为1024
#define HeapMaxSize 1024

//可以选择创建大堆还是小堆，通过结构体成员cmp
//如果 a 和 b 满足比较规则，返回1，否则返回0
//所谓的比较规则，对于小堆来说，就是 a < b
//对于大堆来说，就是a > b

typedef char HeapType;

typedef int(*Compare)(HeapType a,HeapType b);


typedef struct Heap
{
	HeapType data[HeapMaxSize];
	size_t size;
	Compare cmp;
}Heap;

//初始化的时候就决定是大堆还是小堆
void HeapInit(Heap* heap,Compare cmp);//初始化

void HeapDestroy(Heap* heap);//堆的销毁

void HeapInsert(Heap* heap,HeapType value);//堆的插入

int HeapRoot(Heap* heap,HeapType *value);//取堆顶元素

void HeapErase(Heap* heap);//删除堆顶元素

void HeapCreate(Heap* heap,HeapType array[],size_t size);//创建一个大堆

void HeapSort(HeapType array[],size_t size);//堆排序
