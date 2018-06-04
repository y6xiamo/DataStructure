#include<stdio.h>
#include<stddef.h>
#include"seqstack.h"
#include<string.h>

//返回1表示能变换成功
//返回0表示不能变换成功

int StackOrder(char input[],size_t input_size,char output[],size_t output_size)
{
	SeqStack stack;
	SeqStackInit(&stack);
	size_t i = 0;
	size_t output_index = 0;

	char top;
	for( ;i < input_size;i++)
	{
		  
    	  //1.循环的把input入栈
		  SeqStackPush(&stack,input[i]);
		  int ret = SeqStackTop(&stack,&top);
	     //2.取栈顶元素，和output_index指向的元素进行比较
		  while(1)
		  {
				SeqStackTop(&stack,&top);
				 if(output_index >= output_size)
				 {
					 break;//output_index走到output数组的最后一个
				 }
			     //3.如果不相等，继续循环取下一个input元素入栈
				 if(top != output[output_index])
				 {
					 break;
				 }
				 //4.如果相等
				//  a)移进output_index
				//  b)把栈顶元素出栈
				//  c)再循环的比较栈顶元素和output_index指向的值
				 ++output_index;
				 SeqStackPop(&stack);
		  }
		  if(ret == 0)
		  {
			  break;//栈为空进行最终审判
		  }


	}

	//5.如果最后栈为空并且output_index指向output数组中的最后一个元素的下一个元素，
	//就认为output可以通过input变换得到
	//6.否则则不能通过变换得到
	if(stack.size == 0 && output_index == output_size)
	{
		return 1;
	}
	return 0;
}

////////////////////////////////////
//////////以下为测试代码////////////
///////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n====================%s======================\n",__FUNCTION__)
void TestOrder()
{
	TEST_HEADER;
	char input[6] = "abcde";
	char output[6] = "decba";
	size_t input_size = strlen(input);
	size_t output_size = strlen(output);
	int ret = StackOrder(input,input_size,output,output_size);
	printf("ret expected 1,actual %d\n",ret);
	if(ret == 1)
	{
		printf("output 可以通过input变换得到\n");
	}
	else
	{
	    printf("output 不能通过input变换得到\n");
	}
	
}
int main()
{
	TestOrder();
	printf("\n");
	return 0;
}
#endif
