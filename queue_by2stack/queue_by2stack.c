#include<stdio.h>

#include"seqstack.h"

typedef struct QueueBy2Stack
{
	SeqStack input;
	SeqStack output;
}QueueBy2Stack;

void QueueInit(QueueBy2Stack* queue)
{
	if(queue == NULL)
	{
		return;//非法输入
	}
	SeqStackInit(&queue->input);
	SeqStackInit(&queue->output);
}

void QueuePush(QueueBy2Stack* q,SeqStackType value)
{
	if(q == NULL)
	{
		return;//非法输入
	}
	//先把所有output的元素出栈然后按顺序入栈到input里
	while(1)
	{
		SeqStackType top;
		int ret = SeqStackTop(&q->output,&top);
		if(ret == 0)
		{
			break;
		}
		SeqStackPush(&q->input,top);
		SeqStackPop(&q->output);
	}
	//把新元素value插入到input中
	SeqStackPush(&q->input,value);
	return;
}

void QueuePop(QueueBy2Stack* q)
{
	if(q == NULL)
	{
		return;//非法输入
	}
	//先把input里所有元素倒腾到output里
	while(1)
	{
		SeqStackType top;
		int ret = SeqStackTop(&q->input,&top);
		if(ret == 0)
		{
			break;
		}
		SeqStackPush(&q->output,top);
		SeqStackPop(&q->input);
	}
	SeqStackPop(&q->output);
	return;
}

int QueueFront(QueueBy2Stack* q,SeqStackType* value)
{
	if(q == NULL|| value == NULL)
	{
		return 0;;//非法输入
	}
	//把input里的所有元素倒腾到output里
	while(1)
	{
		SeqStackType top;
		int ret = SeqStackTop(&q->input,&top);
		if(ret == 0)
		{
			break;
		}
		SeqStackPush(&q->output,top);
		SeqStackPop(&q->input);
	}
	return SeqStackTop(&q->output,value);
	
}
////////////////////////////////////////
//////////以下是测试代码///////////////
///////////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n=================%s================\n",__FUNCTION__)

void TestQueue()
{
	TEST_HEADER;
    QueueBy2Stack queue;
	QueueInit(&queue);
	QueuePush(&queue,'a');
	QueuePush(&queue,'b');
	QueuePush(&queue,'c');
	QueuePush(&queue,'d');

	SeqStackType value;
	int ret = QueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected a,acatual %c\n",value);

	QueuePop(&queue);
	ret = QueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected b,acatual %c\n",value);
	
	QueuePop(&queue);
	ret = QueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected c,acatual %c\n",value);

	QueuePop(&queue);
	ret = QueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected d,acatual %c\n",value);
	
	QueuePop(&queue);
	ret = QueueFront(&queue,&value);
	printf("ret expected 0,actual %d\n",ret);
}

int main()
{
	TestQueue();
	printf("\n");
	return 0;
}
#endif
