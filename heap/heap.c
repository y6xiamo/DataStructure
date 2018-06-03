#include"heap.h"
#include<string.h>
//为小堆建立比较函数
int Less(HeapType a,HeapType b)
{
	return a < b ? 1 : 0;
}

//为大堆建立比较函数
int Greate(HeapType a,HeapType b)
{
	return a > b ? 1 : 0;
}
void HeapInit(Heap* heap,Compare cmp)
{
	if(heap == NULL)
	{
		return;
		//非法输入
	}
	heap->size = 0;
	heap->cmp = cmp;
	return;
}

void HeapDestroy(Heap* heap)
{
	if(heap == NULL)
	{
		return;
		//非法输入
	}
	heap->size = 0;
	heap->cmp = NULL;
	return;
}

void Swap(HeapType* a,HeapType* b)
{
    HeapType tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
void AdjustUp(Heap* heap,size_t index)
{
    size_t child = index;
    size_t parent = (child-1)/2;
    while(child > 0)
    {
        //如果child和parent不满足比较规则，即child > parent(大堆)，就交换child和parent
        
        if(!heap->cmp(heap->data[parent],heap->data[child]))
        {
            Swap(&heap->data[parent],&heap->data[child]);
        }
        else
        {
            //如果某一个位置下，child和parent已经满足比较规则
            //直接退出，停止上浮
            //因为更上面的节点一定是满足堆的要求的
            break;
        }
        child = parent;
        parent = (child-1)/2;
    }

}
void HeapInsert(Heap* heap,HeapType value)
{
    if(heap == NULL)
    {
        return;//非法输入
    }
    if(heap->size >= HeapMaxSize)
    {
        return;//堆满了
    }
    heap->data[heap->size++] = value;//将元素插入到最后
    AdjustUp(heap,heap->size-1);//将最后一个元素进行上浮式调整
    return;
}

int HeapRoot(Heap* heap,HeapType* value)
{
    if(heap == NULL)
    {
        return 0;//非法输入
    }
    *value = heap->data[0];
    --heap->size;
    return 1;
}

void AdjustDown(Heap* heap,size_t index)
{
    if(heap == NULL)
    {
        return;//非法输入
    }
    size_t parent = index;
    size_t child = 2 * index + 1;
    while(child < heap->size)
    {
        //如果右子树存在并且比左子树更符合堆的要求
        //大堆，即右子树大于左子树，就让child指向右子树
        if(child+1 < heap->size && heap->cmp(heap->data[child+1],heap->data[child]))
        {
            child = child + 1;
        }
        if(heap->cmp(heap->data[child],heap->data[parent]))
        {
            Swap(&heap->data[child],&heap->data[parent]);
        }
        else
        {
            break;
        }
        parent = child;
        child = parent * 2 + 1;
    }
}
void HeapErase(Heap* heap)
{
    if(heap == NULL)
    {
        return;//非法输入
    }
    if(heap->size == 0)
    {
        return;//空堆
    }
    //交换堆顶元素和最后一个元素
    Swap(&heap->data[0],&heap->data[heap->size-1]);
    //进行尾删；  
    --heap->size;
    //从根结点开始，进行下沉调整
    AdjustDown(heap,0);
    return;
}

void HeapCreate(Heap* heap,HeapType array[],size_t size)
{
    if(heap == NULL)
    {
        return;//非法输入
    }
    //遍历array数组，将每个元素依次插入到堆中
    size_t i = 0;
    for( ;i < size;i++ )
    {
        HeapInsert(heap,array[i]);
    }
    return;
}

//假设我们要升序排序，就要一个大堆
void HeapSort(HeapType array[],size_t size)
{
    //把这个数组构建成一个堆
    Heap heap;
    HeapInit(&heap,Greate);
    HeapCreate(&heap,array,size);
    //循环的删除堆顶元素
    while(heap.size > 0)
    {
        HeapErase(&heap);
    }
    //循环结束后，堆排序就完成
    memcpy(array,heap.data,size * sizeof(HeapType));
    return;

}
//////////////////////////////////////////////////////////
///////////////////以下是测试代码/////////////////////////
/////////////////////////////////////////////////////////
#include<stdio.h>

#define TEST_HEADER printf("\n======================%s======================\n",__FUNCTION__)
void HeapPrintChar(Heap* heap,char* msg)
{
    if(heap == NULL)
    {
        return;
    }
    printf("[%s]\n",msg);
    size_t i = 0;
    for( ;i < heap->size;i++)
    {
        printf("%c ",heap->data[i]);
    }
    printf("\n");
    return;

}
void TestInit()
{
	TEST_HEADER;
	Heap heap;
	HeapInit(&heap,Greate);
	printf("size expected 0,actual is %d\n",heap.size);
	printf("cmp expected %p,actual is %p\n",Greate,heap.cmp);
}

void TestInsert()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greate);
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'f');
    HeapPrintChar(&heap,"往堆里插入六个元素");
}

void TestHeapRoot()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greate);
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'f');
    HeapType value;
    int ret = HeapRoot(&heap,&value);
    printf("ret expected 1,actual is %d\n",ret);
    printf("value expected f,actual is %c\n",value);
}

void TestErase()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greate);
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'f');
    HeapErase(&heap);
    HeapPrintChar(&heap,"删除堆顶元素");
}

void TestCreate()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greate);
    HeapType array[] = "adefbc";
    HeapCreate(&heap,array,sizeof(array)/sizeof(array[0])-1);
    HeapPrintChar(&heap,"创建一个大堆");

}
void TestSort()
{
    TEST_HEADER;
    HeapType array[] = {'c','a','f','e','d','b'};
    HeapSort(array,sizeof(array)/sizeof(array[0]));
    size_t i = 0;
    for( ;i<sizeof(array)/sizeof(array[0]);i++)
    {
        printf("%c ",array[i]);
    }
    printf("\n");

}
int main()
{
	TestInit();
    TestInsert();
    TestHeapRoot();
    TestErase();
    TestCreate();
    TestSort();	
    return 0;
}
