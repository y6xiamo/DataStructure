#include"linkstack.h"
#include<stdio.h>
#include<stdlib.h>

LinkStackNode* CreateLinkStackNode(LinkStackType value)//创建结点
{
	LinkStackNode* new_node = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	new_node->data = value;
	new_node->next = NULL;

	return new_node;
}

void LinkStackInit(LinkStackNode** phead)
{
	if(phead == NULL)
	{
		return;
	}
	*phead = NULL;
	return;
}

void LinkStackDestroy(LinkStackNode** phead)
{
	if(phead == NULL)
	{
		return;//非法输入
	}
	if(*phead == NULL)
	{
		return;//空栈
	}
	LinkStackNode* cur = *phead;
	while(cur != NULL)
	{
		LinkStackNode* to_delete = cur;
		free(to_delete);
		cur = cur->next;
	}
	return;
}

void LinkStackPush(LinkStackNode** phead,LinkStackType value)
{
	if(phead == NULL)
	{
		return;//非法输入
	}
	
	LinkStackNode* cur = *phead;
	(*phead) = CreateLinkStackNode(value);
    (*phead)->next = cur;

	return;
}

void LinkStackPop(LinkStackNode** phead)
{
	if(phead == NULL)
	{
		return; //非法输入
	}
	if(*phead == NULL)
	{
		return;//空栈
	}
	LinkStackNode* to_delete = *phead;
    (*phead) = to_delete->next;
	free(to_delete);
	
	return;
}


int LinkStackTop(LinkStackNode* phead,LinkStackType* value)
{
	if(phead == NULL)
	{
		return 0;//非法操作
	}
	*value = (phead)->data;

	return 1;
}

////////////////////////////////////////////////
/////////////以下是测试代码////////////////////
///////////////////////////////////////////////
#include<stdio.h>
#if 1
#define TEST_HEADER printf("\n===============================%s===================================\n",__FUNCTION__)

void LinkStackPrintChar(LinkStackNode* phead,const char* msg)
{
	printf("[%s]\n",msg);
    if(phead == NULL)
	{
		return;
	}
    LinkStackNode* cur = phead;
    for( ;cur != NULL;cur = cur->next)
    {
        printf("[%c] ",cur->data);
    }
    printf("\n");
    
}

void TestInit()
{
	TEST_HEADER;
	LinkStackNode* head;
	LinkStackInit(&head);
}

void TestPush()
{

	TEST_HEADER;
	LinkStackNode* head;
	LinkStackInit(&head);

	LinkStackPush(&head,'a');
    LinkStackPush(&head,'b');
	LinkStackPush(&head,'c');
	LinkStackPush(&head,'d');

	LinkStackPrintChar(head,"入栈四个元素");
}

void TestPop()
{

	TEST_HEADER;
	LinkStackNode* head;
	LinkStackInit(&head);

	LinkStackPop(&head);
	LinkStackPrintChar(head,"尝试对空栈操作");
	LinkStackPush(&head,'a');
    LinkStackPush(&head,'b');
	LinkStackPush(&head,'c');
	LinkStackPush(&head,'d');

	LinkStackPop(&head);
	LinkStackPop(&head);
	LinkStackPrintChar(head,"出栈两个元素");
	LinkStackPop(&head);
	LinkStackPop(&head);
	LinkStackPrintChar(head,"出栈两个元素");
}

void TestTop()
{

	TEST_HEADER;
	LinkStackNode* head;
	LinkStackInit(&head);
	
	LinkStackPush(&head,'a');
    LinkStackPush(&head,'b');
	LinkStackPush(&head,'c');
	LinkStackPush(&head,'d');
	
	LinkStackType value;
	int ret = LinkStackTop(head,&value);
	printf("ret expected 1.actual %d\n",ret);
	printf("value expected d,actual %c\n",value);
	
	LinkStackPop(&head);
	LinkStackPop(&head);
    ret = LinkStackTop(head,&value);
	printf("ret expected 1.actual %d\n",ret);
	printf("value expected b,actual %c\n",value);
	
	LinkStackPop(&head);
	LinkStackPop(&head);
    ret = LinkStackTop(head,&value);
	printf("ret expected 0,actual %d\n",ret);
}

int main()
{
	TestInit();
	TestPush();
	TestPop();
	TestTop();
	printf("\n");

}
#endif
