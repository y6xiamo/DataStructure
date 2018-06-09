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

void SeqStackAssgin(SeqStack* from,SeqStack* to)
{
	//为了保证to里面的内存能够足够的容纳from中的元素
	//采用以下策略：
	//1.释放to中的原有内存
	SeqStackDestroy(to);
	//2.根据from中的元素个数，确定内存申请的大小
	to->size = from->size;
	to->capacity = from->capacity;
	//3.给to申请一个足够的内存
	to->data = (SeqStackType*)malloc(to->capacity*sizeof(SeqStackType));
	//4.最后进行数据的拷贝
	size_t i = 0;
	for( ;i < from->size;i++)
	{
		to->data[i] = from->data[i];
	}
	return;
}
void SeqStackPrintDebug(SeqStack* stack,char* msg)
{
	printf("[%s]\n",msg);
	size_t i = 0;
	for( ;i < stack->size;i++)
	{
		printf("(%d,%d)\n",stack->data[i].ROW,stack->data[i].COL);
	}
	printf("\n");
}


//////////////////////////////////////////////
///////////////以下为测试代码////////////////
////////////////////////////////////////////
#include<stdio.h>
#define TEST_HEADER printf("\n======================%s========================\n",__FUNCTION__)
/*void SeqStackPrintChar(SeqStack*stack,char* msg)
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

*/
/*void TestInit()
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
