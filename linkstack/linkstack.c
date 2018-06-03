#include"linkstack.h"
#include<stdio.h>
#include<stdlib.h>
LinkStackNode*  CreateStack(pStack s)
{
	s->pButtom = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	if(s->pButtom == NULL)
	{
		printf("error\n");
		exit(-1);
	}
	s->pTop = s->pButtom;
	s->pTop->data= 0;
	s->pTop->next = NULL;
	return s
}

void LinkStackInit(LinkStackNode** phead)
{
	if(phead == NULL)
	{
		return;//非法输入
	}
	*phead == NULL;
	return;
}

void LinkStackDestroy(pStack s)
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
	(*phead) = CreateStackNode(value);
    (*phead)->next = cur;

	return;
}







///////////////////////////////////////
////////////以下为测试代码////////////
/////////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n===========================%s=============================\n",__FUNCTION__)
void LinkStackPrintChar(pStack s,const char* msg)
{
    if(s == NULL)
	{
		return;
	}
	printf("[%s]\n",msg);
    LinkStackNode* cur = s->pTop;
    *for( ;cur != pBottom;cur = cur->next)
    {
        printf("[%c] ",cur->data);
    }
    printf("\n");
    
}

void TestInit()
{
	TEST_HEADER;
	LinkStack stack;
	LinkStackInit(&stack);
}

void TestPush()
{

	TEST_HEADER;
	LinkStack stack;
	LinkStackInit(&stack;

	LinkStackPush(&stack,'a');
    LinkStackPush(&stack,'b');
	LinkStackPush(&stack,'c');
	LinkStackPush(&stack,'d');

	LinkStackPrintChar(stack,"入栈四个元素");
}




int main()
{
	TestInit();
//	TestPush();
	printf("\n");
	return 0;
}


#endif
