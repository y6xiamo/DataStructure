#include"seqstack.h"
#include<stdio.h>

typedef struct MinStack
{
	SeqStack stack;
}MinStack;

void MinStackInit(MinStack* min_stack)
{
	if(min_stack == NULL)
	{
		return;
	}
	SeqStackInit(&min_stack->stack);
}

void MinStackPush(MinStack* min_stack,SeqStackType value)
{
	if(min_stack == NULL)
	{
		return;//非法输入
	}
	SeqStackType min = value;
    //取栈顶元素
	SeqStackType top;
	int ret = SeqStackTop(&min_stack->stack,&top);
    if(ret != 0)
	{
		//将栈顶元素和value值进行比较，将小指赋给min
		if(top > value)
		{
			min = value;
		}
		min = top;
	}
	//一次入两个元素，先插value,后插min,才能保证栈顶元素是最小的
	SeqStackPush(&min_stack->stack,value);
	SeqStackPush(&min_stack->stack,min);
}

void MinStackPop(MinStack* min_stack)
{
	if(min_stack == NULL)
	{
		return;//非法输入
	}

	if(min_stack->stack.size == 0)
	{
		return;//空栈
	}
	//连续出栈两个元素
	SeqStackPop(&min_stack->stack);
	SeqStackPop(&min_stack->stack);
//	min_stack->stack.size -= 2;
	return;
}
int MinStackTop(MinStack* min_stack,SeqStackType* value)
{
	if(min_stack == NULL)
	{
		return 0;//非法输入
	}
	SeqStackTop(&min_stack->stack,value);
}

///////////////////////////////////////
/////////以下是测试代码///////////////
//////////////////////////////////////

#define TEST_HEADER printf("\n==============%s============\n",__FUNCTION__)

void TestMinStack()
{
	TEST_HEADER;
	MinStack min_stack;
	MinStackInit(&min_stack);
	MinStackPush(&min_stack,'a');
	MinStackPush(&min_stack,'b');
	MinStackPush(&min_stack,'c');
	MinStackPush(&min_stack,'d');
 
	SeqStackType value;
	int ret = MinStackTop(&min_stack,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected a,actual %c\n",value);

	MinStackPop(&min_stack);
	MinStackPop(&min_stack);
	ret = MinStackTop(&min_stack,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value1 expected c,actual %c\n",value);	
}

int main()
{
	TestMinStack();
	printf("\n");
	return 0;
}
