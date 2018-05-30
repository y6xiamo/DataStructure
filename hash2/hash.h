#pragma once
#include<stddef.h>

#define HashMaxSize 1000

typedef size_t KeyType;
typedef size_t ValType;

typedef size_t (*HashFunc)(KeyType key);
typedef struct HashElem
{
    KeyType key;
    ValType value;
    struct HashElem* next;
}HashElem;

typedef struct HashTable
{
    //我们这里定义的哈希桶上的链表是一个不带头结点的链表
    HashElem* data[HashMaxSize];
    size_t size;
    HashFunc func;
}HashTable;

void HashInit(HashTable* ht,HashFunc func);//初始哈

void HashDestroy(HashTable* ht);//哈希表的销毁

void HashInsert(HashTable* ht,KeyType key,ValType value);//插入

HashElem*  HashBucketFind(HashElem* head,KeyType to_find);//在哈希桶里查找一个元素

int HashFind(HashTable* ht,KeyType key,ValType* value);//查找一个元素

void HashRemove(HashTable* ht,KeyType to_remove);//删除哈希表里的某一个元素
