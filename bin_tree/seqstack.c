#include"seqstack.h"
#include<stdio.h>
#include<stdlib.h>
void SeqStackInit(SeqStack* stack)
{
	stack->size = 0;
	stack->capacity = 1000;
	stack->data = (SeqStackType*)malloc(stack->capacity*sizeof(SeqStackType));
}

void SeqStackDestroy(SeqStack* stack)
{
	free(stack->data);
	stack->size = 0;
	stack->capacity = 0;
}

void SeqStackReSize(SeqStack* stack)
{
	if(stack->size < stack->capacity)
	{
		return;
	}
	stack->capacity = stack->capacity*2+1;
	SeqStackType* new_ptr = (SeqStackType*)malloc(stack->capacity * sizeof(SeqStackType));
	int i = 0;
	for( ;i < stack->size;i++)
	{
		new_ptr[i] = stack->data[i];
	}
	free(stack->data);
	stack->data = new_ptr;
	return;
}
void SeqStackPush(SeqStack* stack,SeqStackType value)
{
	if(stack == NULL)
	{
		return;   //非法输入
	}
	if(stack->size >= stack->capacity)
	{
		//TODO 扩容
		SeqStackReSize(stack);
	}
	stack->data[stack->size++] = value;
}

void SeqStackPop(SeqStack* stack)
{
	if(stack == NULL)
	{
		return; //非法输入
	}
	if(stack->size == 0)
	{
		return;  //空栈
	}
	--stack->size;
	return;
}

int SeqStackTop(SeqStack* stack,SeqStackType* value)
{
	if(stack == NULL)
	{
		return 0; //非法输入
	}
	if(stack->size == 0)
	{
		return 0; //空栈
	}
	*value = stack->data[stack->size-1];
	return 1;
}





//////////////////////////////////////////////
///////////////以下为测试代码////////////////
////////////////////////////////////////////
/*#include<stdio.h>
#define TEST_HEADER printf("\n======================%s========================\n",__FUNCTION__)
void SeqStackPrintChar(SeqStack*stack,char* msg)
{
	if(stack == NULL)
	{
		return;  //非法输入
	}
	printf("[%s]\n",msg);
	int i = 0;
	for( ;i <stack->size;i++)
	{
		printf("[%c] ",stack->data[i]);
	}
	return;
}
void TestInit()
{
     TEST_HEADER;
	 SeqStack stack;
	 SeqStackInit(&stack);
	 printf("size expected 0,actual %lu\n",stack.size);
	 printf("capacity expected 1000;actual %lu\n",stack.capacity);
}
void TestDestroy()
{

     TEST_HEADER;
	 SeqStack stack;
	 SeqStackInit(&stack);
	 SeqStackDestroy(&stack);
}

void TestPush()
{
     TEST_HEADER;
	 SeqStack stack;
	 SeqStackInit(&stack);
	 SeqStackPush(&stack,'a');
	 SeqStackPush(&stack,'b');
	 SeqStackPush(&stack,'c');
	 SeqStackPush(&stack,'d');
	 SeqStackPrintChar(&stack,"入栈四个元素");
}

void TestPop()
{
     TEST_HEADER;
	 SeqStack stack;
	 SeqStackInit(&stack);
	 SeqStackPush(&stack,'a');
	 SeqStackPush(&stack,'b');
	 SeqStackPush(&stack,'c');
	 SeqStackPush(&stack,'d');
     SeqStackPop(&stack);
	 SeqStackPrintChar(&stack,"出栈栈顶元素");
}

void TestTop()
{

     TEST_HEADER;
	 SeqStack stack;
	 SeqStackInit(&stack);
	 SeqStackPush(&stack,'a');
	 SeqStackPush(&stack,'b');
	 SeqStackPush(&stack,'c');
	 SeqStackPush(&stack,'d');

	 SeqStackType value;
	 int ret = SeqStackTop(&stack,&value);
	 printf("ret expected 1,actual %d\n",ret);
	 printf("value expected d,actual %c\n",value);
    
	 SeqStackPop(&stack);
	 SeqStackPop(&stack);
	 ret = SeqStackTop(&stack,&value);
	 printf("ret expected 1,actual %d\n",ret);
	 printf("value expected b,actual %c\n",value);
	 
	 SeqStackPop(&stack);
	 SeqStackPop(&stack);
	 ret = SeqStackTop(&stack,&value);
	 printf("ret expected 0,actual %d\n",ret);
}
int main()
{
	TestInit();
	TestDestroy();
	TestPush();
	TestPop();
	TestTop();
	printf("\n");
	return 0;
}
*/
