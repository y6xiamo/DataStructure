#pragma once
#include<stddef.h>
#include<stdint.h>

typedef uint64_t BitmapType;

typedef struct Bitmap
{
    uint64_t *data;
    size_t capacity;
}Bitmap;

void BitmapInit(Bitmap* bm,uint64_t capacity);//初始化

void BitmapDestroy(Bitmap* bm);//销毁

//测试某一位是否为1
int BitmapTest(Bitmap* bm,uint64_t index);

//给某一位设置为1
void BitmapSet(Bitmap* bm,uint64_t index);

//给所有位设置为1
void BitmapFill(Bitmap* bm);

//给所有位设置为0
void BitmapClear(Bitmap* bm);
