#include"seqqueue.h"

void SeqQueueInit(SeqQueue* q)
{
	if(q == NULL)
	{
		return;    //非法输入
	}
	q->head = 0;
	q->tail= 0;
	q->size = 0;
	return;
}

void SeqQueueDestroy(SeqQueue* q)
{
	if(q == NULL)
	{
		return; //非法输入
	}
	q->head = 0;
	q->tail = 0;
	q->size = 0;
}

void SeqQueuePush(SeqQueue* q,SeqQueueType value)
{
	if(q == NULL)
	{
		return;//非法输入
	}
	if(q->size >= SeqQueueMaxSize)
	{
		return;//队列已满
	}
	q->data[q->tail++] = value;

	if(q->tail == SeqQueueMaxSize)
	{
		q->tail = 0;
	}
	q->size++;
}

void SeqQueuePop(SeqQueue* q)
{
	if(q == NULL)
	{
		return;//非法输入
	}
	if(q->size == 0)
	{
		return;//空列表
	}
	++q->head;

	if(q->head == SeqQueueMaxSize)
	{
	    q->head = 0;
	}
	--q->size;
	return;
}

int SeqQueueFront(SeqQueue* q,SeqQueueType* value)
{
	if(q == NULL||value == NULL)
	{
		return 0;//非法输入
	}
	if(q->size == 0)
	{
		return 0;//空队列
	}
	*value = q->data[q->head];
	return 1;
}

////////////////////////////////////////
/////////以下是测试代码////////////////
///////////////////////////////////////
/*#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n==================%s================\n",__FUNCTION__)
void TestQueue()
{
	TEST_HEADER;
	SeqQueue queue;
	SeqQueueInit(&queue);
	SeqQueuePush(&queue,'a');
	SeqQueuePush(&queue,'b');
	SeqQueuePush(&queue,'c');
	SeqQueuePush(&queue,'d');

	SeqQueueType value;
	int ret = SeqQueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected a,actual %c\n",value);

	SeqQueuePop(&queue);
	SeqQueuePop(&queue);
	ret = SeqQueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected c,actual %c\n",value);
	
	SeqQueuePop(&queue);
	SeqQueuePop(&queue);
	ret = SeqQueueFront(&queue,&value);
	printf("ret expected 0,actual %d\n",ret);

}
int main()
{
	TestQueue();
	printf("\n");
	return 0;
}
#endif
*/
