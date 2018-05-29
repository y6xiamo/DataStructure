#include"seqlist.h"


void swap(SeqListType *a,SeqListType *b)
{
    SeqListType tmp = *a;
    *a = *b;
    *b = tmp;
}

void SeqListInit(SeqList * seqlist)
{
    if(seqlist == NULL)
        return;
    seqlist->size = 0;
}



void SeqListPushBack(SeqList *seqlist,SeqListType value)
{
    if(seqlist == NULL)
        return;                     //非法输入
    
    if(seqlist->size == SeqListMaxSize)
        return;                     //顺序表已满

    seqlist->data[seqlist->size] = value;
    seqlist->size++;
}


void SeqListPopBack(SeqList *seqlist)
{
    if(seqlist == NULL)
        return;                //非法输入

    if(seqlist->size == 0)
        return;                //顺序表为空
    --seqlist->size;
    return;
}

void SeqListPushFront(SeqList *seqlist,SeqListType value)
{
    if(seqlist == NULL)
        return;                //非法输入

    if(seqlist->size == SeqListMaxSize)
        return;                //顺序表已满

    ++seqlist->size;
    size_t i = seqlist->size -1;
    for( ;i > 0;i--)
    {
        seqlist->data[i] = seqlist->data[i-1];
    }
    seqlist->data[0] = value;
    return;
}


void SeqListPopFront(SeqList *seqlist)
{
    if(seqlist == NULL)
        return;                //非法输入

    if(seqlist->size == 0)
        return;                //顺序表为空
    
    size_t i = 0;
    for( ;i < seqlist->size;i++)
    {
        seqlist->data[i] = seqlist->data[i+1];
    }
    --seqlist->size;
    return;
}

void SeqListInsert(SeqList *seqlist,size_t pos,SeqListType value)
{
    if(seqlist == NULL)
        return;              //非法输入

    if(seqlist->size == SeqListMaxSize)
        return;             //顺序表已满

   ++seqlist->size;
   size_t i = seqlist->size - 1;
   for( ;i > pos;i--)
   {
       seqlist->data[i] = seqlist->data[i-1];
   }
   seqlist->data[pos] = value;
   return;
}

void SeqListErase(SeqList *seqlist,size_t pos)
{

    if(seqlist == NULL)
        return;                //非法输入

    if(seqlist->size == 0)
        return;                //顺序表为空

    size_t i = pos;
    for( ;i < seqlist->size;i++)
    {
        seqlist->data[i] = seqlist->data[i+1];
    }
    --seqlist->size;
    return;
}

int SeqListGet(SeqList *seqlist,size_t pos,SeqListType *value)
{
    if(seqlist == NULL)
        return 0;     //非法输入

    if(pos >= seqlist->size)
        return 0;    //非法输入

    *value = seqlist->data[pos];
    return 1;
}

void SeqListSet(SeqList *seqlist,size_t pos,SeqListType value)
{
    if(seqlist == NULL)
        return;       //非法输入
    if(pos >= seqlist->size)
        return;       //pos越界
    
    
    seqlist->data[pos] = value;
        return;
 }

int SeqListFind(SeqList *seqlist,SeqListType value)
{
    if(seqlist == NULL)
        return;          //非法输入
    
    size_t i = 0;
    for( ;i < seqlist->size;i++)
    {
        if(value == seqlist->data[i])
        {
            return i;
        }
    }
    return -1;
}

void SeqListRemove(SeqList *seqlist,SeqListType to_remove)
{
    if(seqlist == NULL)
        return;           //非法输入

    size_t pos = SeqListFind(seqlist,to_remove);
    if(pos == (size_t)-1)
        return;

    SeqListErase(seqlist,pos);
    return;
}

void SeqListRemoveAll(SeqList *seqlist,SeqListType to_remove)
{
    if(seqlist == NULL)
        return;          //非法输入
   while(1)
   {
         size_t pos = SeqListFind(seqlist,to_remove);
         if(pos == (size_t)-1)
               break;

          SeqListErase(seqlist,pos);
   }
   return;
}

void SeqListBubbleSort(SeqList *seqlist)
{
    if(seqlist == NULL)
        return;           //非法输入

    size_t count = 0;     //冒泡次数
    for( ;count < seqlist->size;++count)
    {
        size_t cur = 0;
        for( ;cur < seqlist->size-1-count;++cur)
        {
            if(seqlist->data[cur] > seqlist->data[cur+1])
                swap(&seqlist->data[cur],&seqlist->data[cur+1]);
        }
    }
    return;
}

void SeqListBubbleSortEx(SeqList *seqlist,Cmp cmp)
{
    if(seqlist == NULL)
        return;

    size_t count = 0;     //冒泡次数
    for( ;count < seqlist->size;++count)
    {
        size_t cur = 0;
        for( ;cur < seqlist->size-1-count;++cur)
        {
            if(!cmp(seqlist->data[cur], seqlist->data[cur+1]))
                swap(&seqlist->data[cur],&seqlist->data[cur+1]);
        }
    }
    return;
}

size_t SeqListSize(SeqList *seqlist)
{
    if(seqlist == NULL)
        return -1;      //非法输入
   
    return seqlist->size;
}

int SeqListEmpty(SeqList *seqlist)
{
    if(seqlist == NULL)
        return -1;      //非法输入

    if(seqlist->size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
///////////////////////////////////
//测试代码
//////////////////////////////////

#include<stdio.h>
#include<stdint.h>

#define TEST_HEADER printf("\n=================%s=================\n",__FUNCTION__)

void SeqListPrintChar(SeqList *seqlist,const char *msg)
{
    if(seqlist == NULL)
    {
        printf("非法输入");
      return;
    }
    printf("[%s]\n",msg);
     
    size_t i = 0;
    for( ;i < seqlist->size;i++)
    {
        printf("[%c] ",seqlist->data[i]);
    }
}





void TestInit()
{
    SeqList seqlist;
    SeqListInit(&seqlist);
    printf("seqlist.size expect 0,actual %lu\n",seqlist.size);
}

void TestPushBack()
{
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListPrintChar(&seqlist,"对顺序表进行尾插");
}

void TestPopBack()
{

    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListPopBack(&seqlist);
    SeqListPrintChar(&seqlist,"对顺序表进行尾删");
}

void TestPushFront()
{

    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListPushFront(&seqlist,'z');
    SeqListPrintChar(&seqlist,"对顺序表进行头插");
}

void TestPopFront()
{
    
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListPushFront(&seqlist,'z');
    SeqListPopFront(&seqlist);
    SeqListPrintChar(&seqlist,"将顺序表头部元素删除");

}

void TestInsert()
{

    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListInsert(&seqlist,2,'x');
    SeqListPrintChar(&seqlist,"给顺序表任意位置插入元素");
}

void TestErase()
{

    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListInsert(&seqlist,2,'x');
    SeqListErase(&seqlist,2);
    SeqListPrintChar(&seqlist,"删除顺序表任意位置元素");
}

void TestGet()
{

    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListType value;
    int ret= SeqListGet(&seqlist,2,&value);
    printf("value expected [c],actual [%c]",value);
}

void TestSet()
{

    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');
  
    SeqListSet(&seqlist,0,'x');
    SeqListPrintChar(&seqlist,"将0位置的[a]改成[x]");    
}

void TestFind()
{

    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    size_t pos = SeqListFind(&seqlist,'b');
    printf("pos expected 1,actual %ld",(int64_t)pos);

}

void TestRemove()
{

    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListRemove(&seqlist,'d');
    SeqListPrintChar(&seqlist,"移除顺序表中的元素");
}

void TestRemoveAll()
{
        
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');
    SeqListPushBack(&seqlist,'b');

    SeqListRemoveAll(&seqlist,'b');
    SeqListPrintChar(&seqlist,"移除顺序表中的元素'b'");
}

void TestBubbleSort()
{

    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'e');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'d');

    SeqListBubbleSort(&seqlist);
    SeqListPrintChar(&seqlist,"冒泡排序");
}

int Greater(SeqListType a,SeqListType b)
{
    return a > b? 1:0;       //降序
}

int Less(SeqListType a,SeqListType b)
{
    return a < b? 1:0;      //升序
}
void TestBubbleSortEx()
{

    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'e');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'d');

    SeqListBubbleSortEx(&seqlist,Less);
    SeqListPrintChar(&seqlist,"升序");
}

void TestSize()
{

    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'e');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'a');

    size_t count = SeqListSize(&seqlist);
    printf("count expected 4,actual %d",count);
}
void TestEmpty()
{
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist); 
    SeqListPushBack(&seqlist,'e');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
   
    size_t ret = SeqListEmpty(&seqlist);
    printf("ret expected 0,actual %d",ret);
}
int main()
{
    TestInit();
    TestPushBack();       
    TestPopBack();
    TestPushFront();
    TestPopFront();
    TestInsert();
    TestErase();
    TestGet();
    TestSet();
    TestFind();
    TestRemove();
    TestRemoveAll();
    TestBubbleSort();
    TestBubbleSortEx();
    TestSize();
    TestEmpty();
    printf("\n");
    return 0;
}

