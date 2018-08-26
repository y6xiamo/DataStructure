#include <stdio.h>
BitmapType GetSize(BitmapType capacity)
{
    uint64_t size = capacity / (sizeof(BitmapType)*8) + 1;
    return size;
}
void BitmapInit(Bitmap* bm,uint64_t capacity)
{
    if(bm == NULL)
    {
        return;
    }
    //capacity表示能表示的最大的数
    //capacity = 100  2个数
    //capacity = 200  4个数
    //capacity = 300  5个数
    //capacity = N    N/(sizeof(BitmapType)) + 1
    bm->capacity = capacity;
    BitmapType size = GetSize(capacity);
    bm->data = (BitmapType*)malloc(sizeof(BitmapType) * size);
    memset(bm->data,0,sizeof(BitmapType)*size);
}
int main()
{
    return 0;
}
