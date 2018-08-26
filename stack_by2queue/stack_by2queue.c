#include<stdio.h>
 #include"seqqueue.h"

typedef struct StackBy2Queue
{
	SeqQueue queue1;
	SeqQueue queue2;
}StackBy2Queue;

void StackInit(StackBy2Queue* stack)
{
	if(stack == NULL)
	{
		return;//非法输入
	}
	 
	SeqQueueInit(&stack->queue1);
	SeqQueueInit(&stack->queue2);
}

void StackPush(StackBy2Queue* stack,SeqQueueType value)
{
	if(stack == NULL)
	{
		return;//非法输入
	}
	SeqQueue* input;
	//先判断哪个队列不为空，然后将元素插入到那个队列里
	if(stack->queue1.size != 0)
	{
		input = &stack->queue1;
	}
	input = &stack->queue2;
	SeqQueuePush(input,value);
}

void StackPop(StackBy2Queue* stack)
{
	if(stack == NULL)
	{
		return;//非法输入
	}
	//如果是空栈，直接返回
	if(stack->queue1.size == 0 && stack->queue2.size == 0)
	{
		return;
	}
	//先判断哪个队列为空,不为空队列为from,空队列为to
	SeqQueue* from = NULL;
	SeqQueue* to = NULL;
	if(stack->queue1.size > 0)
	{
		from = &stack->queue1;
		to = &stack->queue2;
	}
	else
	{
		from = &stack->queue2;
		to = &stack->queue1;
	}
	//把from中的元素倒腾到to中，直到from中只剩下一个元素
	while(1)
	{
		if(from->size == 1)
		{
			break;
		}
		SeqQueueType value;
		int ret = SeqQueueFront(from,&value);
		SeqQueuePop(from);
		SeqQueuePush(to,value);
	}
	SeqQueuePop(from);
}

int StackFront(StackBy2Queue* stack,SeqQueueType* value)
{
	if(stack == NULL)
	{
		return 0;//非法输入
	}
	//如果是空栈，直接返回
	if(stack->queue1.size == 0 && stack->queue2.size == 0)
	{
		return 0;
	}
	//先判断哪个队列为空,不为空队列为from,空队列为to
	SeqQueue* from = NULL;
	SeqQueue* to = NULL;
	if(stack->queue1.size > 0)
	{
		from = &stack->queue1;
		to = &stack->queue2;
	}
	else
	{
		from = &stack->queue2;
		to = &stack->queue1;
	}
	//把from中的元素倒腾到to中，直到from中只剩下一个元素
	while(1)
	{
		if(from->size == 1)
		{
			break;
		}
		SeqQueueFront(from,value);
		SeqQueuePop(from);
		SeqQueuePush(to,*value);
	}
	//将剩下的最后一个元素取出来赋给value
	SeqQueueFront(from,value);
	SeqQueuePop(from);
	SeqQueuePush(to,*value);
	return 1;
}

////////////////////////////////////
//////////以下是测试代码///////////
//////////////////////////////////

#if 1
#include<stdio.h>

#define TEST_HEADER printf("\n====================%s=======================\n",__FUNCTION__)
void TestStack()
{
	TEST_HEADER;
	StackBy2Queue stack;
	StackInit(&stack);
	StackPush(&stack,'a');
	StackPush(&stack,'b');
	StackPush(&stack,'c');
	StackPush(&stack,'d');

	SeqQueueType value;
	int ret = StackFront(&stack,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected d,actual %c\n",value);

	StackPop(&stack);
	ret = StackFront(&stack,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected c,actual %c\n",value);

	StackPop(&stack);
	ret = StackFront(&stack,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected b,actual %c\n",value);

	StackPop(&stack);
	ret = StackFront(&stack,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected a,actual %c\n",value);
	
	StackPop(&stack);
	ret = StackFront(&stack,&value);
	printf("ret expected 0,actual %d\n",ret);
}
int main()
{
	TestStack();
	printf("\n");
	return 0;
}
#endif
