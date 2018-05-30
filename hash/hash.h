#pragma once
#include<stddef.h>

#define HashMaxSize 1000
typedef size_t KeyType;
typedef size_t ValType;

typedef enum
{
    Empty, //空状态
    Deleted, //删除状态
    Valid,  //有效状态
}Stat;

typedef size_t (*HashFunc)(KeyType key);

//这个结构体代表哈希表中的一个元素
//这个元素中同时也包含了键值对
typedef struct HashElem
{
    KeyType key;
    ValType value;
    Stat stat;
}HashElem;

typedef struct HashTable
{
    HashElem data[HashMaxSize];
    size_t size;
    HashFunc func;//函数指针，指向了hash函数
}HashTable;

void HashInit(HashTable* ht,HashFunc hash_fun);//初始化

void HashDestroy(HashTable* ht);//销毁

void HashInsert(HashTable* ht,KeyType key,ValType value);//插入

int  HashFind(HashTable* ht,KeyType key,ValType* value);//查找

void HashRemove(HashTable* ht,KeyType key);//删除元素
