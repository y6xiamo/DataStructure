#include<stddef.h>
#include<stdlib.h>
#include"dlinklist.h"
#include<stdio.h>
DLinkNode* CreateDLinkNode(DLinkType value)
{
	DLinkNode* new_node =(DLinkNode*)malloc(sizeof(DLinkNode));
	new_node->data = value;
	new_node->prev = new_node;
	new_node->next= new_node;
	return new_node;
}
void DLinkListInit(DLinkNode** phead)
{
	if(phead == NULL)
	{
		return;       //非法输入
	}
	*phead = CreateDLinkNode(0);
}

void DestroyNode(DLinkNode* node)
{
	free(node);
}

void DLinkListDestroy(DLinkNode** phead)
{
	if(phead == NULL)
	{
		return;     //非法输入
	}
	DLinkNode* cur = (*phead)->next;
	while(cur != *phead)
	{
		DLinkNode* next = cur->next;
		DestroyNode(cur);
		cur = next;
	}
	*phead = NULL;
}

void DLinkListPushBack(DLinkNode* phead,DLinkType value)
{
	if(phead == NULL)
	{
		return;   //非法输入
	}
	DLinkNode* new_node = CreateDLinkNode(value);
	DLinkNode* tail = phead->prev;

	tail->next = new_node;
    new_node->prev = tail;
	
	phead->prev = new_node;
	new_node->next = phead;
	return;
}

void DLinkListPopBack(DLinkNode* phead)
{
	if(phead == NULL)
	{
		return;      //非法输入
	}
    if(phead->next == phead)
	{
		return;      //链表为空
	}
	DLinkNode* to_delete = phead->prev;
	DLinkNode* prev = to_delete->prev;

	phead->prev = prev;
	prev->next = phead;
	DestroyNode(to_delete);
	return;
}

void DLinkListPushFront(DLinkNode* phead,DLinkType value)
{
	if(phead == NULL)
	{
		return;        //非法输入
	}

	DLinkNode* new_node = CreateDLinkNode(value);
	DLinkNode* next_node= phead->next;

	next_node->prev = new_node;
    new_node->next = next_node;
	
	phead->next = new_node;
	new_node->prev = phead;
	return;

}

void DLinkListPopFront(DLinkNode* phead)
{
	if(phead == NULL)
	{
		return;      //非法输入
	}
    if(phead->next == phead)
	{
		return;      //链表为空
	}
	DLinkNode* to_delete = phead->next;
	DLinkNode* next_node = to_delete->next;

	phead->next = next_node;
	next_node->prev = phead;
	DestroyNode(to_delete);
	return;
}

DLinkNode* DLinkListFind(DLinkNode* phead,DLinkType to_find)
{
	if(phead == NULL)
	{
		return NULL;         //非法输入
	}
	if(phead->next == phead)
	{
		return NULL;      //空链表
	}

    DLinkNode* cur = phead->next;
	for( ;cur != phead;cur = cur->next)
	{
		if(cur->data == to_find)
		{
			return cur;
		}
	}
	return NULL;
}

void DLinkListInsert(DLinkNode* phead,DLinkNode* pos,DLinkType to_insert)
{
	if(phead == NULL || pos == NULL)
	{
		return;       //非法输入
	}
	DLinkNode* new_node = CreateDLinkNode(to_insert);
	DLinkNode* next_node = pos->next;
	pos->next = new_node;
	new_node->prev = pos;

	new_node->next = next_node;
	next_node->prev = new_node;
}

void DLinkListInsertBefore(DLinkNode* phead,DLinkNode* pos,DLinkType to_insert)
{
	if(phead == NULL || pos == NULL)
	{
		return;         //非法输入
	}
	DLinkNode* new_node = CreateDLinkNode(to_insert);
	DLinkNode* prev_node = pos->prev;

	prev_node->next = new_node;
	new_node->prev = prev_node;

	new_node->next = pos;
	pos->prev = new_node;
}

void DLinkListErase(DLinkNode* phead,DLinkNode* pos)
{
	if(phead == NULL || pos == NULL)
	{
		return;            //非法输入
	}

	DLinkNode* prev_node = pos->prev;
	DLinkNode* next_node = pos->next;

	prev_node->next = next_node;
	next_node->prev = prev_node;
	DestroyNode(pos);

}

void DLinkListRemove(DLinkNode* phead,DLinkType to_remove)
{
	if(phead == NULL)
	{
		return;      //非法输入
	}
	if(phead->next == phead)
	{
		return;      //空链表
	}
	DLinkNode* cur = phead->next;
	for( ;cur != phead;cur = cur->next)
	{
		if(cur->data == to_remove)
		{
			DLinkListErase(phead,cur);
			break;
		}
	}
	return;
}

void DLinkListRemoveAll(DLinkNode* phead,DLinkType to_remove)
{
	if(phead == NULL)
	{
		return;          //非法输入
	}
	if(phead->next == phead)
	{
		return;         //空链表
	}
	DLinkNode* cur = phead->next;
	while(cur != phead)
	{

	    DLinkNode* pos = DLinkListFind(phead,to_remove);
	    if(pos == NULL)
	    {
		     return;      
      	}
    	DLinkNode* prev_node = pos->prev;
    	DLinkNode* next_node = pos->next;
	    prev_node->next = next_node;
	    next_node->prev = prev_node;
	    DestroyNode(pos);
	}
}

size_t DLinkListSize(DLinkNode* phead)
{
	if(phead == NULL)
	{
		return -1;      //非法输入
	}
	if(phead->next == phead)
	{
		return 0;      //空链表
	}
	DLinkNode* cur = phead->next;
	size_t size = 1;
	while(cur->next != phead)
	{
		size++;
        cur = cur->next;
	}
	return size;
}

int DLinkListEmpty(DLinkNode* phead)
{
	if(phead == NULL)
	{
		return -1;    //非法输入
	}
	if(phead->next == phead)
	{
		return 1;     //空链表
	}
	return 0;
}
//////////////////////////////////////
///////////////测试代码//////////////
////////////////////////////////////
#define TEST_HEADER printf("\n===============================%s===============================\n",__FUNCTION__)
void DLinkListPrintChar(DLinkNode* phead,const char* msg)
{
	printf("[%s]\n",msg);
	DLinkNode* cur1 = phead->next;
	for( ;cur1 != phead;cur1 = cur1->next)
	{
	   printf("[%c|%p]",cur1->data,cur1);
	}
	printf("\n");
	DLinkNode* cur2 = phead->prev;
	for( ;cur2 != phead;cur2 = cur2->prev)
	{
     	printf("[%c|%p]",cur2->data,cur2);
	}
	printf("\n");
	return;
}

void TestInit()
{
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	printf("head expected not NULL, actual %p\n",head);
	printf("head expected 0,actual %d\n",head->data);
}

void TestPushBack()
{
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPrintChar(head,"尾插两个元素");
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');
	DLinkListPrintChar(head,"再尾插两个元素");
}

void TestPopBack()
{
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');

	DLinkListPopBack(head);
	DLinkListPopBack(head);
	DLinkListPrintChar(head,"尾删两个元素");
	DLinkListPopBack(head);
	DLinkListPopBack(head);
	DLinkListPrintChar(head,"再尾删两个元素");
}
void TestPushFront()
{
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushFront(head,'a');
	DLinkListPushFront(head,'b');
	DLinkListPrintChar(head,"头插两个元素");
	DLinkListPushFront(head,'c');
	DLinkListPushFront(head,'d');
	DLinkListPrintChar(head,"再头插两个元素");
}

void TestPopFront()
{
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushFront(head,'a');
	DLinkListPushFront(head,'b');
	DLinkListPushFront(head,'c');
	DLinkListPushFront(head,'d');

	DLinkListPopFront(head);
	DLinkListPopFront(head);
	DLinkListPrintChar(head,"头删两个元素");
	DLinkListPopFront(head);
	DLinkListPopFront(head);
	DLinkListPrintChar(head,"再头删两个元素");
}

void TestFind()
{

	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');

	DLinkListPrintChar(head,"查找元素c的位置");
	DLinkNode* pos_c = DLinkListFind(head,'c');
	printf("pos_c expected %p,actual %p",head->next->next->next,pos_c);
}

void TestInsert()
{

	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');

	DLinkListInsert(head,head->next->next,'x');
	DLinkListPrintChar(head,"在b之后插入元素x");
}

void TestInsertBefore()
{

	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');

	DLinkListInsertBefore(head,head->next->next,'x');
	DLinkListPrintChar(head,"在b之前插入元素x");
}

void TestErase()
{
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');
	
	DLinkListPrintChar(head,"打印双向链表");
	DLinkNode* pos_b = DLinkListFind(head,'b');
	DLinkListErase(head,pos_b);
	DLinkListPrintChar(head,"删除pos_b位置的值");

}

void TestRemove()
{
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');
	
    DLinkListPrintChar(head,"打印双向链表");
	DLinkListRemove(head,'a');
	DLinkListPrintChar(head,"删除a");
}

void TestRemoveAll()
{

	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'d');

	DLinkListPrintChar(head,"打印双向链表");
	DLinkListRemoveAll(head,'b');
	DLinkListPrintChar(head,"删除链表中所有的b");
}

void TestSize()
{

	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');

	size_t size = DLinkListSize(head);
	printf("size expected 4,actual %d",size);
}

void TestEmpty()
{

	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);

	int ret1 = DLinkListEmpty(head);
	printf("ret1 expected 1,actual %d\n",ret1);
	
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	
	int ret2 = DLinkListEmpty(head);
	printf("ret2 expected 0,actual %d",ret2);
}
int main()
{
	TestInit();
	TestPushBack();
	TestPopBack();
	TestPushFront();
	TestPopFront();
	TestFind();
	TestInsert();
	TestInsertBefore();
	TestErase();
	TestRemove();
	TestRemoveAll();
	TestSize();
	TestEmpty();
	printf("\n");
	return 0;
}
