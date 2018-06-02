#include"linkqueue.h"
#include<stdlib.h>
#include<stdio.h>
LinkNode* CreateLinkNode(LinkType value)
{
	LinkNode* new_node = (LinkNode*)malloc(sizeof(LinkNode));//为新结点开辟空间
	if(new_node == NULL)//开辟空间失败
	{
		printf("error\n");
		exit(-1);
	}
	new_node->data = value;
	new_node->next = NULL;
	
	return new_node;
}

void LinkQueueInit(LinkQueue* q)
{
	if(q == NULL)
	{
		return;
	}
	q->head = q->tail = NULL;
	return;
}

void LinkQueueDestroy(LinkQueue* q)
{
	LinkNode* cur = q->head->next;
	//循环释放链表结点
	while(cur != q->head)
	{
		LinkNode* to_delete = cur;
		free(to_delete);
		cur = cur->next;
	}
}

void LinkQueuePush(LinkQueue* q,LinkType value)
{
	if(q == NULL)
	{
		return;//非法输入
	}

	LinkNode* new_node = CreateLinkNode(value);//创建一个新结点
	
	if(q->head == NULL)//队列里没有元素
	{
		q->head = q->tail = new_node;//头指针和尾指针都指向新结点
	}
	q->tail->next = new_node;//将新结点插入到尾指针之后
	q->tail = new_node;//更新尾指针
	q->tail->next = NULL;
	return;
} 

void LinkQueuePop(LinkQueue* q)
{
	if(q == NULL)
	{
		return;//非法输入
	}
	LinkNode* to_delete = q->head;
	q->head = to_delete->next;
	free(to_delete);
	to_delete = NULL;
	return;
	
}

int LinkQueueFront(LinkQueue* q,LinkType* value)
{
	if(q == NULL)
	{
		return 0;//非法输入
	}
	if(q->head == NULL)
	{
		return 0;//空队列
	}
	*value = q->head->data;
	return 1;
}
///////////////////////////////////////
///////////以下是测试代码/////////////
/////////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n===========================%s==============================\n",__FUNCTION__);
void LinkQueuePrintChar(LinkQueue* q,char* msg)
{
	if(q == NULL)
	{
		return;
	}
	printf("[%s]\n",msg);
	LinkNode* cur = q->head;
	while(cur != q->tail->next)
	{
		printf("[%c] ",cur->data);
		cur = cur->next;
	}
	printf("\n");
	return;

}
void TestQueue()
{
	TEST_HEADER;
	LinkQueue queue;
	LinkQueueInit(&queue);
	LinkQueuePush(&queue,'a');
    LinkQueuePush(&queue,'b');
	LinkQueuePush(&queue,'c');
	LinkQueuePush(&queue,'d');
	LinkQueuePrintChar(&queue,"入队列四个元素");

	LinkType value;
	int ret = LinkQueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected a,actual %c\n",value);

	LinkQueuePop(&queue);
	LinkQueuePop(&queue);
	LinkQueuePrintChar(&queue,"出队列两个元素");
    ret = LinkQueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected c,actual %c\n",value);
	
	LinkQueuePop(&queue);
	LinkQueuePop(&queue);
	LinkQueuePrintChar(&queue,"再出队列两个元素");
    ret = LinkQueueFront(&queue,&value);
	printf("ret expected 0,actual %d\n",ret);

}

int main()
{
	TestQueue();
	printf("\n");
	return 0;
}
#endif
