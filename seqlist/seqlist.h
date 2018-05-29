#pragma once 

#include<stddef.h>

#define SeqListMaxSize 1000


typedef char SeqListType;


typedef struct SeqList{
    SeqListType data[SeqListMaxSize];
    size_t size;
}SeqList;


void SeqListInit(SeqList *seqlist);

SeqList seqlist;

/**
 *
 *
 *      往顺序表尾部插入元素
 */
void SeqListPushBack(SeqList * seqlist,SeqListType value);


/**
 *
 *
 *        将顺序表表尾的元素删除
 */
void SeqListPopBack(SeqList *seqlist);


/**
 *
 *
 *        往顺序表表头插入元素
 */
void SeqListPushFront(SeqList *seqlist,SeqListType value);


/**
 *
 *
 *       将顺序表表头的元素删除
 */
void SeqListPopFront(SeqList *seqlist);


/**
 *
 *
 *       往顺序表插入元素
 */
void SeqListInsert(SeqList *seqlist,size_t pos,SeqListType value);

/**
 *
 *
 *       删除顺序表中的元素
 */
void SeqListErase(SeqList *seqlsit,size_t pos);

/**
 *
 *
 *       获取指定位置元素的值
 */
int SeqListGet(SeqList *seqlist,size_t pos,SeqListType* value);

/**
 *
 *
 *       给指定位置设置值
 */
void SeqListSet(SeqList *seqlist,size_t pos,SeqListType value);

/**
 *
 *
 *      找到某个元素的下标
 */
int SeqListFind(SeqList *seqlist,SeqListType value);

/**
 *
 *
 *      移除顺序表中的某个元素
 */
void SeqListRemove(SeqList *seqlist,SeqListType to_remove);
void SeqListRemoveAll(SeqList *seqlist,SeqListType to_remove);

/**
 *
 *
 *       冒泡排序
 */
void SeqListBubbleSort(SeqList *seqlist);

/**
 *   对Cmp比较函数作以下约定
 *   如果 a 和 b 满足比较规则，返回1，否则返回0
 *   满足比较规则具体值：
 *   如果是升序排序，a < b则称为满足比较规则
 */
typedef int (*Cmp)(SeqListType a,SeqListType b);
 void SeqListBubbleSortEx(SeqList *seqlist,Cmp cmp);

 /**
  *
  *
  *   获取顺序表中的元素个数
  */
 size_t SeqListSize(SeqList * seqlist);

 /**
  *
  *
  *  判断顺序表是否为空，如果为空，返回1，否则返回0
  */
 int SeqListEmpty(SeqList *seqlist);
