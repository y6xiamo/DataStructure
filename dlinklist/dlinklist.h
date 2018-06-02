#pragma once
//带头节点、带环的双向链表

typedef char DLinkType;

typedef struct DLinkNode
{
	DLinkType data;
	struct DLinkNode* prev;
	struct DLinkNode* next;
}DLinkNode;

void DLinkListInit(DLinkNode** phead);//初始化

void DLinkListDestroy(DLinkNode** phead);//销毁

void DLinkListPushBack(DLinkNode* phead,DLinkType value);//尾插

void DLinkListPopback(DLinkNode* phead);//尾删

void DLinkListPushFront(DLinkNode* phead,DLinkType value);//头插
void DLinkListPopFront(DLinkNode* phead);//头删

DLinkNode* DLinkListFind(DLinkNode* phead,DLinkType to_find);//查找元素

//在pos位置后面插入元素
void DLinkListInsert(DLinkNode* phead,DLinkNode* pos,DLinkType to_insert);

//在pos之前插入元素
void DLinkListInsertBefore(DLinkNode* phead,DLinkNode* pos,DLinkType to_insert);

//删除指定位置的元素
void DLinkListErase(DLinkNode* phead,DLinkNode* pos);

//删除指定值的元素
void DLinkListRemove(DLinkNode* phead,DLinkType to_remove);

//删除指定元素的所有值
void DLinkListRemoveAll(DLinkNode* phead,DLinkType to_remove);

//求双向链表的大小
size_t DLinkListSize(DLinkNode* phead);

//判断双向链表是否为空，是空链表返回1，否则返回0
int DLinkListEmpty(DLinkNode* phead);
