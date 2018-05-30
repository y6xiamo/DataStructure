#include <stdio.h>
#include<stdlib.h>
#include"hash.h"


//////////////////////////////////////////////////
/////该哈希表基于哈希函数，存储的是健值对类型/////
/////////////////////////////////////////////////
size_t HashFuncDefault(KeyType key)
{
    return key % HashMaxSize;
}
void HashInit(HashTable* ht,HashFunc hash_func)
{
    ht->size = 0;
    ht->func = hash_func;
    size_t i = 0;
    for( ;i < HashMaxSize;i++)
    {
        ht->data[i].stat = Empty;
    }
    return;
}

void HashDestroy(HashTable* ht)
{
    ht->size = 0;
    ht->func = NULL;
    size_t i = 0;
    for( ;i < HashMaxSize; i++)
    {
        ht->data[i].stat = Empty;
    }
    return;
}

void HashInsert(HashTable* ht,KeyType key,ValType value)
{
    if(ht == NULL)
    {
        return;//非法输入
    }
    //1.判定hash表是否能继续插入（根据负载因子来判断）
    //这里我们把负载因子定为0.8
    if(ht->size >=0.8 * HashMaxSize)
    {
        //当前的哈希表已经达到负载因子的上限了
        return;//插入失败
    }
    //2.如果能继续插入，根据key来计算offset
    size_t offset = ht->func(key);
    //3.从offet位置开始向后线性探测，找到第一个状态为Empty的元素进行插入
    while(1)
    {
        if(ht->data[offset].stat != Valid)
        {
            //找到了一个合适位置插入元素
            ht->data[offset].stat = Valid;
            ht->data[offset].key = key;
            ht->data[offset].value = value;
           //5.++size;
            ++ht->size;
            return;
        }
        else if(ht->data[offset].key == key && ht->data[offset].stat == Valid)
        {
          //4.如果发现了key相同的元素，插入失败
            return;
        }
        else
        {
            ++offset;
            if(offset >= HashMaxSize)
            {
                offset = 0;
            }
        }
    
    }
    return;
}

int HashFind(HashTable* ht,KeyType key,ValType* value)
{
    if(ht == NULL || value == NULL)
    {
        return 0;
    }
    //1.根据key计算出offse
    size_t offset = ht->func(key);
    //2.从offset开始向后查找，每找到一个元素，比较其key值和要查找的key是否相同
    while(1)
    {
        if(ht->data[offset].key == key && ht->data[offset].stat == Valid)
        {
           //3.如果相同，返回其value，查找成功
            *value = ht->data[offset].value;
            return 1;
        }
        else if(ht->data[offset].stat == Empty)
        {
            //4.如果当前是一个空元素，则查找失败
            return 0;
        }
        else
        {
          //4.如果不相同，继续向后进行查找
            offset++;
            if(offset >= HashMaxSize)
            {
                offset = 0;
            }
        }

    }
}

void HashRemove(HashTable* ht,KeyType key)
{
    if(ht == NULL)
    {
        return;//非法输入
    }
    if(ht->size == 0)
    {
        return;//哈希表为空
    }
    //1.根据key确定offset
    size_t offset = ht->func(key);
    //2.从offset开始，判断当前元素的key是否和要删除元素的Key值相同
    while(1)
    {
         //   a)如果相同，直接删除
        if(ht->data[offset].key == key && ht->data[offset].stat == Valid)
        {
            ht->data[offset].stat = Deleted;
            --ht->size;
            return;

        }
        //   b)如果当前元素状态为空，说明没找到，直接返回
        else if(ht->data[offset].stat == Empty)
        {
            return;//该元素没有在哈希表中
        }
        else
        {
        //   c)如果不同，线性地继续向后查找
            offset++;
            if(offset > HashMaxSize)
            {
                offset = 0;
            }
        }
    }//循环结束
    return;
}
/////////////////////////////////////////
///////////以下是测试代码////////////////
/////////////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n====================%s====================\n",__FUNCTION__)

void HashPrint(HashTable* ht,char* msg)
{
    if(ht == NULL)
    {
        return;
    }
    printf("[%s]\n",msg);
    int i = 0;
    for( ;i < HashMaxSize;i++)
    {
        if(ht->data[i].stat != Valid)
        {
            continue;
        }
        printf("[%lu   %d:%d]\n",i,ht->data[i].key,ht->data[i].value);
    }
    printf("\n");
}
void TestInit()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    printf("size expected 0.actual is %lu\n",ht.size);
    printf("func expected %p,actual is %p\n",HashFuncDefault,ht.func);
}

void TestInsert()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,12);
    HashInsert(&ht,2,26);
    HashInsert(&ht,3,32);
    HashInsert(&ht,1001,2);
    HashInsert(&ht,1002,74);
    HashPrint(&ht,"往哈希表里插五组数据");
}


void TestFind()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,12);
    HashInsert(&ht,2,26);
    HashInsert(&ht,3,32);
    HashInsert(&ht,1001,2);
    HashInsert(&ht,1002,74);

    ValType value;
    int ret = HashFind(&ht,1002,&value);
    printf("ret expected 1,actual is %d\n",ret);
    printf("value expected 74,actual is %d\n",value);

    ret = HashFind(&ht,50,&value);
    printf("ret expected 0,actual is %d\n",ret);

}

void TestRemove()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,12);
    HashInsert(&ht,2,26);
    HashInsert(&ht,3,32);
    HashInsert(&ht,1001,2);
    HashInsert(&ht,1002,74);

    HashRemove(&ht,1001);
    HashPrint(&ht,"在哈希表中删除key为1001,value为2的键值对");
}
int main()
{
    TestInit();
    TestInsert();
    TestFind();
    TestRemove();
    return 0;
}

#endif
