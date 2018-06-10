#include<stdio.h>
#include<stddef.h>
#define SharedStackMixSize 1000

typedef char SharedStackType;

//[0,top1)表示第一个栈
//[top2,SharedSatckMixSize)表示第二个栈
typedef struct SharedStack
{
	SharedStackType data[SharedStackMixSize];
	size_t top1;
	size_t top2;
}SharedStack;

void SharedStackInit(SharedStack* stack)
{
	if(stack == NULL)
	{
		return;//非法输入
	}
	stack->top1 = 0;
	stack->top2 = SharedStackMixSize;
	return;
}

void SharedStackPush1(SharedStack* stack,SharedStackType value)
{
	if(stack == NULL)
	{
		return;//非法输入
	}
	if(stack->top1 >= stack->top2)
	{
		return;//栈已满，不能再插入元素
	}
	stack->data[stack->top1++] = value;//将元素插入到top1指向的位置，再将top1指向下一个位置
	return;
}

void SharedStackPush2(SharedStack* stack,SharedStackType value)
{
	if(stack == NULL)
	{
		return;//非法输入
	}
	if(stack->top1 >= stack->top2)
	{
		return;//栈已满，不能再插入元素
	}
	stack->data[--stack->top2] = value;//先将top2减一，再将元素插入到top2指向的位置
	return;
}

int SharedStackTop1(SharedStack* stack,SharedStackType* value)
{
	if(stack == NULL)
	{
		return 0;//非法输入
	}
	if(stack->top1 == 0)
	{
		return 0;//空栈
	}
	*value = stack->data[stack->top1-1];//top1的前一个位置为有效值，将其赋给value
	return 1;
}

int SharedStackTop2(SharedStack* stack,SharedStackType* value)
{
	if(stack == NULL)
	{
		return 0;//非法输入
	}
	if(stack->top2 == SharedStackMixSize)
	{
		return 0;//空栈
	}
	*value = stack->data[stack->top2];//top2指向的位置就是有效值，将其赋给value
	return 1;
}

void SharedStackPop1(SharedStack* stack)
{
	if(stack == NULL)
	{
		return;//非法输入
	}
	if(stack->top1 == 0)
	{
		return;//空栈
	}
	--stack->top1;
	return;
}

void SharedStackPop2(SharedStack* stack)
{
	if(stack == NULL)
	{
		return;//非法输入
	}
	if(stack->top2 == SharedStackMixSize)
	{
		return;//空栈
	}
	++stack->top2;
	return;
}
/////////////////////////////////////////////
///////////////以下是测试代码///////////////
///////////////////////////////////////////
#include<stdio.h>
#if 1
#define TEST_HEADER printf("\n=======================%s====================\n",__FUNCTION__)
void TestInit()
{
	TEST_HEADER;
	SharedStack stack;
	SharedStackInit(&stack);
}
void Test1()
{

	TEST_HEADER;
	SharedStack stack;
	SharedStackInit(&stack);
	SharedStackPush1(&stack,'a');
	SharedStackPush1(&stack,'b');
	SharedStackPush1(&stack,'c');
	SharedStackPush1(&stack,'d');

	SharedStackType value;
	int ret = SharedStackTop1(&stack,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected d,actual %c\n",value);

	SharedStackPop1(&stack);
	SharedStackPop1(&stack);
	ret = SharedStackTop1(&stack,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected b,actual %c\n",value);

	SharedStackPop1(&stack);
	SharedStackPop1(&stack);
	ret = SharedStackTop1(&stack,&value);
	printf("ret expected 0,actual %d\n",ret);
}

void Test2()
{

	TEST_HEADER;
	SharedStack stack;
	SharedStackInit(&stack);
	SharedStackPush2(&stack,'a');
	SharedStackPush2(&stack,'b');
	SharedStackPush2(&stack,'c');
	SharedStackPush2(&stack,'d');

	SharedStackType value;
	int ret = SharedStackTop2(&stack,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected d,actual %c\n",value);

	SharedStackPop2(&stack);
	SharedStackPop2(&stack);
	ret = SharedStackTop2(&stack,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected b,actual %c\n",value);

	SharedStackPop2(&stack);
	SharedStackPop2(&stack);
	ret = SharedStackTop2(&stack,&value);	
	printf("ret expected 0,actual %d\n",ret);
}
int main()
{
	TestInit();
	Test1();
	Test2();
	printf("\n");
	return 0;
}
#endif


