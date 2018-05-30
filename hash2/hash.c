#include <stdio.h>
#include"hash.h"
#include<stdlib.h>
size_t HashFuncDefault(KeyType key)
{
    return key % HashMaxSize;
}

HashElem* CreateElem(KeyType key,ValType value)
{
    HashElem* new_node = (HashElem*)malloc(sizeof(HashElem));
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void DestroyElem(HashElem* node)
{
    free(node);
    return;
}

void HashInit(HashTable* ht,HashFunc func)
{
    if(ht == NULL)
    {
        return;//非法输入
    }
    ht->size = 0;
    ht->func = func;
    int i = 0;
    for( ; i < HashMaxSize;i++)
    {
        ht->data[i] = NULL;
    }
    return;
}

void HashDestroy(HashTable* ht)
{
    if(ht == NULL)
    {
        return;
    }
    ht->size = 0;
    ht->func = NULL;
    //遍历整个哈希表，释放元素
    size_t i = 0;
    for( ;i < HashMaxSize;i++)
    {
        HashElem* cur = ht->data[i];
        while(cur != NULL)
        {
            HashElem* next = cur->next;
            DestroyElem(cur);
            cur = next;

        }
    }
    return;
}

HashElem* HashBucketFind(HashElem* head,KeyType to_find)
{
    HashElem* cur = head;
    while(cur != NULL)
    {
        if(cur->key == to_find)
        {
            break;
        }
         cur = cur->next;
    }
    return cur != NULL ? cur:NULL;
    
}

int HashBucketFindEx(HashElem* head,KeyType to_remove,HashElem** pre_node,HashElem** cur_node)
{
    if(head == NULL)
    {
        return 0;
    }
    HashElem* pre = NULL;
    HashElem* cur = head;
    while(cur != NULL)
    {
        if(to_remove == cur->key)
        {
            *pre_node = pre;
            *cur_node = cur;
            return 1;
        }
        pre = cur;
        cur = cur->next;
    }
    return 0;

}
void HashInsert(HashTable* ht,KeyType key,ValType value)
{
    if(ht == NULL)
    {
        return;//非法输入
    }
    //1.先根据key计算出offset
    size_t offset = ht->func(key);
    //2.在offset对应的链表里查找当前key是否存在
    HashElem* ret = HashBucketFind(ht->data[offset],key);
    if(ret != NULL)
    {
      //  a)如果存在，插入失败
        return;
    }

    //  b)如果不存在，直接插入,采用头插
    HashElem* new_node = CreateElem(key,value);
    new_node->next = ht->data[offset];
    ht->data[offset] = new_node;
    ++ht->size;
    return;
}

int HashFind(HashTable* ht,KeyType key,ValType* value)
{
    if(ht == NULL)
    {
        return 0;//非法输入
    }
    //1.先找到要查找元素的下标
    size_t offset = ht->func(key);
    //2.根据下标找到对应的链表
    //  在链表中查找该值是否存在
    HashElem* ret = HashBucketFind(ht->data[offset],key);
    if(ret == NULL)
    {
        return 0;
    }
    *value = ret->value;
    return 1;

}
void HashRemove(HashTable* ht,KeyType to_remove)
{
    if(ht == NULL)
    {
        return;
    }
    //1.先找到要删除元素的下标
    size_t offset = ht->func(to_remove);
    //2.查找该下标对应的链表中是否存在该元素
    HashElem* cur = NULL;
    HashElem* pre = NULL;
    int ret = HashBucketFindEx(ht->data[offset],to_remove,&pre,&cur);
    if(ret == 0)
    {
        return;//没找到
    }
    if(pre == NULL)
    {
        //要删除的元素是链表头结点
        ht->data[offset] = cur->next;
    }
    else
    {//要删除的元素不是头结点
        pre->next = cur->next;
    }
    DestroyElem(cur);
    --ht->size;
    return;

}



//////////////////////////////////////////
/////////////以下为测试代码//////////////
/////////////////////////////////////////

#define TEST_HEADER printf("\n===================%s==================\n",__FUNCTION__)
#if 1
#include<stdio.h>

void HashPrint(HashTable* ht,char* msg)
{
    printf("[%s]\n",msg);
    size_t i = 0;
    for( ;i< HashMaxSize;i++)
    {
        if(ht->data[i] == NULL)
        {
            continue;
        }
        printf("i = %lu\n",i);
        HashElem* cur = ht->data[i];
        while(cur != NULL)
        {
            printf("[%d:%d]\n",cur->key,cur->value);
            cur = cur->next;
        }
    }
    printf("\n");
}

void TestInit()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    printf("size expected 0,actual is %d\n",ht.size);
    printf("func expected %p,actual is %p\n",HashFuncDefault,ht.func);
}

void TestInsert()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,12);
    HashInsert(&ht,2,34);
    HashInsert(&ht,1001,3);
    HashInsert(&ht,1002,42);
    HashInsert(&ht,4,6);
    HashPrint(&ht,"往哈希表里插入五条数据");
}

void TestFind()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,12);
    HashInsert(&ht,2,34);
    HashInsert(&ht,1001,3);
    HashInsert(&ht,1002,42);
    HashInsert(&ht,4,6);

    KeyType value;
    int ret = HashFind(&ht,1001,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected 3,actual %d\n",value);

    ret = HashFind(&ht,5,&value);
    printf("ret expected 0,actual is %d\n",ret);
}
void TestRemove()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,12);
    HashInsert(&ht,2,34);
    HashInsert(&ht,1001,3);
    HashInsert(&ht,1002,42);
    HashInsert(&ht,4,6);

    HashRemove(&ht,2);
    HashPrint(&ht,"删除key为2的元素");

}
int main()
{
    TestInit();
    TestInsert();
    TestFind();
    TestRemove();
    printf("\n");
    return 0;
}
#endif
