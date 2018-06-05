#include <stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include"seqstack.h"

//////////////////////////////////
//      冒泡排序
//      时间复杂度：O(N * N)
//      空间复杂度：O(1)
//      稳定性：稳定
///////////////////////////////////
void Swap(int* a,int* b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
void BubbleSort(int arr[],int size)
{
    if(arr == NULL)
    {
        return;//非法输入
    }
    if(size <= 1)
    {
        return;//只有一个元素或数组为空
    }
    //[0,bound) 有序区间
    //[bound,size)  待排序区间
    int bound = 0;
    for(;bound < size;bound++)
    {
        int cur = size - 1;
        for( ;cur > bound;cur--)
        {
            if(arr[cur] < arr[cur - 1])
            {
                Swap(&arr[cur],&arr[cur-1]);
            }
        }
    }
    return;
}

///////////////////////////////////////
//      选择排序
//      时间复杂度：O(N * N)
//      空间复杂度：O(1)
//      稳定性：不稳定
/////////////////////////////////////

void SelectSort(int arr[],int size)
{
    if(arr == NULL)
    {
        return;
    }
    if(size <= 1)
    {
        return;
    }
    //[0,bound)  有序区间
    //[bound,size) 待排序区间
    int bound = 0;
    for(;bound < size;bound++)
    {
        //打擂台，bound为擂主
        //bound后面每个元素和擂主进行比较，
        //如果小于擂主，就进行交换(升序)
        int cur = bound + 1;
        for( ;cur < size;cur++)
        {
            if(arr[cur] < arr[bound])
            {
                Swap(&arr[cur],&arr[bound]);
            }
        }
    }
    return;
}

//////////////////////////////////
//     插入排序
//     时间复杂度：O(N * N)
//     空间复杂度：O(1)
//     稳定性：稳定
/////////////////////////////////
void InsertSort(int arr[],int size)
{
    if(arr == NULL)
    {
        return;
    }
    if(size <= 1)
    {
        return;
    }
    // [0,bound) 有序区间
    // [bound,size) 待排序区间
    //把有序区间看做一个线性表，
    //把当前bound指向的元素插入到这个线性表中
    int bound = 1;
    for( ;bound < size;bound++)
    {
        int cur = bound;
        int bound_key = arr[bound];
        //保存bound指向的元素
        for( ;cur > 0;cur--)
        {
            //从后往前的去找一个合适的位置放置bound_key，一边找，一边搬运
            if(arr[cur - 1] > bound_key)
            {
                arr[cur] = arr[cur - 1];
            }
            else
            {
                break;//找到一个合适的位置
            }
        }
        arr[cur] = bound_key;
    }
    return;
}



///////////////////////////////////
//      堆排序
//      时间复杂度：
//      空间复杂度：
//      稳定性：
////////////////////////////////////
void AdjustUp(int arr[],int size,int index)
{
    int child = index;
    int parent = (child - 1)/2;
    while(child > 0)
    {
        if(arr[parent] < arr[child])
        {
            Swap(&arr[parent],&arr[child]);
        }
        else
        {
            break;
        }
        child = parent;
        parent = (child - 1)/2;
    }
    return;
}
void AdjustDown(int arr[],int size,int index)
{
    if(size <= 1)
    {
        return;
    }
    int parent = index;
    int child = parent * 2 + 1;
    while(child < size)
    {
        if(child + 1 < size && arr[child] < arr[child + 1])
        {
            child = child + 1;
        }
        if(arr[parent] < arr[child])
        {
            Swap(&arr[parent],&arr[child]);
        }
        parent = child;
        child = parent * 2 + 1;
    }
    return;
}

void HeapPop(int arr[],int heap_index )
{
    if(heap_index <= 1)
    {
        return;
    }
    Swap(&arr[0],&arr[heap_index - 1]);
    AdjustDown(arr,heap_index - 1,0);
    return;
}
void HeapCreate(int arr[],int size)
{
    if(size <= 1)
    {
        return;
    }
   #if 0
    int i = (size - 1 - 1)/2;//先找到最后一个叶子结点的父节点
    for( ; i > 0;i--)
    {
        //下沉式调整
        AdjustDown(arr,size,i);
    }
    AdjustDown(arr,size,0);
   #else
    int bound = 0;
    for( ;bound < size;bound++)
    {
        AdjustUp(arr,size,bound);
    }
  #endif
}
void HeapSort(int arr[],int size)
{
    if(arr == NULL)
    {
        return;
    }
    if(size <= 1)
    {
        return;
    }
    //1.基于数组建一个堆（升序建大堆）
    HeapCreate(arr,size);
    //2.循环的删除堆顶元素,将所有元素都删除完，排序完成
    int i = 0;
    for( ;i < size - 1;i++)
    {
        //第二个参数表示哪部分符合堆的规则
        HeapPop(arr,size - i);
    }
    return;

}





////////////////////////////////////
//     希尔排序
//     时间复杂度：
//     空间复杂度：
//     稳定性：
/////////////////////////////////////







////////////////////////////////
//   归并排序
//   时间复杂度: O(N * logN)
///////////////////////////////
void _MerageArray(int arr[],int64_t beg,int64_t mid,int64_t end,int* tmp)
{
       int64_t cur1 = beg;
       int64_t cur2 = mid;
       int64_t tmp_index = beg;
     while(cur1 < mid && cur2 < end)
     {
       if(arr[cur1] < arr[cur2])
       {
           tmp[tmp_index++] = arr[cur1++];
       }
       else if(arr[cur1] > arr[cur2])
       {
           tmp[tmp_index++] = arr[cur2++];
       }
     }
       while(cur1 < mid)
       {
           tmp[tmp_index++] = arr[cur1++];
        }
       while(cur2 < end)
       {
           tmp[tmp_index++] = arr[cur2++];
       }

 //将tmp中的内容拷贝到arr中
 //arr[beg,end]   tmp[beg,end]
 //拷贝的时候要保证拷贝到正确的区间
     memcpy(arr+beg,tmp+beg,sizeof(int) * (end - beg));
     return;
 
}
void _MergeSort(int array[],int64_t beg,int64_t end,int* tmp)
{
    if(end - beg <= 1)
    {
        //要么有一个元素，要么没有元素
        return;
    }
    int64_t mid = beg + (end - beg)/2;
    //两个区间 (beg,mid]  [mid,end)
    _MergeSort(array,beg,mid,tmp);
    _MergeSort(array,mid,end,tmp);
    //合并区间
   _MerageArray(array,beg,mid,end,tmp);
    return;

}
void MergeSort(int arr[],size_t size)
{
    //创建一个临时空间来合并元素
    int* tmp = (int*)malloc(sizeof(int) * size);
    _MergeSort(arr,0,size,tmp);
    free(tmp);
}

//非递归版本的归并排序
void MergeSortByLoop(int arr[],size_t size)
{
    if(size <= 1)
    {
        return;//没有元素或者只有一个元素,直接退出
    }
     int* tmp = (int*)malloc(sizeof(int) * size);
     //将步长初始化为1
     ////相当于每次合并两个长度为区间为gap的有序区间
     size_t gap = 1;
     for( ; gap < size;gap = gap * 2)
     {
         //借助i来完成所有长度为gap的区间合并
         size_t i = 0;
         for( ;i < size;i += gap * 2)
         {
             int64_t beg = i;
             int64_t mid = i + gap;
             int64_t end = i+ 2 * gap;
            _MerageArray(arr,beg,mid,end,tmp);
         }
     }
     free(tmp);

}


/////////////////////////////////
/////  快速排序
////   时间复杂度
////////////////////////////////
//2.挖坑法
int64_t Partion2(int arr[],int64_t beg,int64_t end)
{
    int64_t left = beg;
    int64_t right = end -1;
    //取数组的最后一个数作为基准值
    int key = arr[right];
    while(left < right)
    {
        while(left < right && arr[left] <= key)
        {
            left++;
        }
        //循环结束，意味着找到一个大于key的值
        //就可以把它插入到刚right指向的坑里
        //一旦操作结束，意味着left也变成了一个坑
        if(left < right)
        {
            arr[right--] = arr[left];
        }
        while(left < right && arr[right] >= key)
        {
            right--;
        }
        //循环结束，意味着找到一个小于key的值
        //就可以把它插入到刚left指向的坑里
        //一旦操作结束，意味着right也变成了一个坑
        if(left < right)
        {
            arr[left--] = arr[right];
        }

    }
    //循环结束，说明right和left指向了相同的元素
    arr[left] = key;
    return left;

}

//1.交换法
int64_t Partion1(int arr[],int64_t beg,int64_t end)
{
    int64_t left = beg;
    int64_t right = end -1;
    //取数组的最后一个数作为基准值
    int key = arr[right];
    while(left < right)
    {
        //从左往右找一个大于key的数
        while(arr[left] <= key && left < right)
        {
            left++;
        }
        //从右往左找一个小于key的值
        while(arr[right] >= key && left < right)
        {
            right--;
        }
        //找到了，将两个元素交换
        if(left < right)
        {
            Swap(&arr[left],&arr[right]);
        }
    }
    //最后left所指向的元素和key进行交换
    Swap(&arr[left],&key);
    return left;
}
void _QuickSort(int arr[],int64_t beg,int64_t end)
{
    if(end - beg <= 1)
    {
        return;
    }
    int64_t mid = Partion2(arr,beg,end);
    //此时分成了两个区间
    //[beg,mid)  [mid+1,end)
    //左半区间的所有数一定都小于右半区间的数
    _QuickSort(arr,beg,mid);
    _QuickSort(arr,mid+1,end);
    return;
}

void QuickSort(int arr[],size_t size)
{
    //区间[0,size)
    _QuickSort(arr,0,size);
    return;
}

//快速排序非递归版本
void QuickSortByLoop(int arr[],int size)
{
    if(arr == NULL)
    {
        return;
    }
    if(size <= 0)
    {
        return;
    }
    
    //用循环主要解决区间划分，这里我们借助栈来实现
    int64_t beg = 0;
    int64_t end = size;
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,beg);
    SeqStackPush(&stack,end);
    while(1)
    {
        int ret = SeqStackTop(&stack,&end);
        SeqStackPop(&stack);
        if(ret == 0)
        {
            return;
        }
        SeqStackTop(&stack,&beg);

        if(end - beg <= 1)
        {
            continue;
        }

        int64_t mid = Partion1(arr,beg,end);
        SeqStackPush(&stack,beg);
        SeqStackPush(&stack,mid);
        SeqStackPush(&stack,mid);
        SeqStackPush(&stack,end);
        

    }
    
}











/////////////////////////////////////////
//////////以下是测试代码/////////////////
/////////////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n==================%s===================\n",__FUNCTION__)
void SortPrint(int arr[],size_t size,char* msg)
{
    printf("%s\n",msg);
     size_t i = 0;
     for( ;i < size;i++)
     {
         printf("%d ",arr[i]);
     }
}

void TestBubble()
{
    TEST_HEADER;
    int arr[] = {20,18,70,52,64,92,21,58};
    size_t size = sizeof(arr)/sizeof(arr[0]);

//    printf("%lu",size);
    BubbleSort(arr,size);
    SortPrint(arr,size,"冒泡排序");
    printf("\n");
}

void TestSelect()
{
    TEST_HEADER;
    int arr[] = {20,18,70,52,64,92,21,58};
    size_t size = sizeof(arr)/sizeof(arr[0]);

//    printf("%lu",size);
    SelectSort(arr,size);
    SortPrint(arr,size,"选择排序");
    printf("\n");
}

void TestInsert()
{
    TEST_HEADER;
    int arr[] = {20,18,70,52,64,92,21,58};
    size_t size = sizeof(arr)/sizeof(arr[0]);

//    printf("%lu",size);
    InsertSort(arr,size);
    SortPrint(arr,size,"插入排序");
    printf("\n");
}

void TestHeap()
{
    TEST_HEADER;
    int arr[] = {20,18,70,52,64,92,21,58};
    size_t size = sizeof(arr)/sizeof(arr[0]);

//    printf("%lu",size);
    HeapSort(arr,size);
    SortPrint(arr,size,"堆排序");
    printf("\n");
}
void TestMerge()
{
    TEST_HEADER;
    int arr[] = {20,18,70,52,64,92,21,58};
    size_t size = sizeof(arr)/sizeof(arr[0]);

//    printf("%lu",size);
    MergeSort(arr,size);
    SortPrint(arr,size,"归并排序");
    printf("\n");
}
void TestQuick()
{
    TEST_HEADER;
    int arr[] = {20,18,70,52,64,92,21,58};
    size_t size = sizeof(arr)/sizeof(arr[0]);

//    printf("%lu",size);
    QuickSort(arr,size);
    SortPrint(arr,size,"快速排序");
    printf("\n");
}

int main()
{
    TestBubble();
    TestSelect();
    TestInsert();
    TestHeap();
    TestMerge();
    TestQuick();
    return 0;
}
#endif
