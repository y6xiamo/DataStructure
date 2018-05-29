//单向的不带环不带头节点的链表

#pragma once 

typedef char LinkNodeType;

typedef struct LinkNode
{
    LinkNodeType data;
    struct LinkNode *next;
}LinkNode;


typedef LinkNode* PLinkNode;

void LinkListInit(PLinkNode*);                                //初始化

void LinkListDestroy(PLinkNode*);                             //销毁

void LinkListPushBack(LinkNode** head,LinkNodeType value);    //尾插

void LinkListPopBack(LinkNode** head);                        //尾删

void LinkListPushFront(LinkNode** head,LinkNodeType value);   //头插

void LinkListPopFront(LinkNode** head);                       //头删

//将一个元素插入到pos之后
void LinkListInsert(LinkNode* pos,LinkNodeType value);

//将一个元素插入到pos之前
void LinkListInsertBefore(LinkNode** head,LinkNode* pos,LinkNodeType value);

//优化后将元素插入到pos之前
void LinkListInsertBefore2(LinkNode* pos,LinkNodeType value);

//删除元素
void LinkListErase(LinkNode** head,LinkNode* pos);

//优化后的删除
void LinkListErase2(LinkNode** head,LinkNode* pos);

//给一个元素找位置
LinkNode* LinkListFind(LinkNode* head,LinkNodeType to_find);

//判断链表是否为空，链表为空返回1，否则，返回0
int LinkListEmpty(LinkNode* head);

//求链表元素隔个数
int LinkListSize(LinkNode* head);

//删除指定值的元素
void LinkListRemove(LinkNode** head,LinkNodeType value);

//删除指定值的所有元素
void LinkListRemoveAll(LinkNode** head,LinkNodeType value);

//逆序打印链表
void LinkListReversePrint(LinkNode* head);

//链表逆序（先删除节点再头插）
void LinkListReverse(LinkNode** head);

//链表逆序（用三个指针）		
void LinkListReverse2(LinkNode** head);

//约瑟夫环
LinkNode* JosephCircle(LinkNode* head,int M);

//冒泡排序
void LinkListBubbleSort(LinkNode* head);

//将两个有序链表合并成一个有序链表
LinkNode* LinkListMerge(LinkNode* head1,LinkNode* head2);

//找一个链表的中间节点
LinkNode* LinkListFindMidNode(LinkNode* head);

//查找链表的倒数第k个节点
//LinkNode* LinkListFindLastKNode(LinkNode* head,int k)

//删除链表的第倒数k个节点
void LinkListEraseLastKNode(LinkNode** head,int k);

//判断链表是否有环
LinkNode* LinkListHasCycle(LinkNode* head);

//判断环的长度
int  LinkListCycleLen(LinkNode* head);

//判断环的入口点
LinkNode* LinkListCycleEntry(LinkNode* head);

//判断两个链表是否相交
int LinkListCross(LinkNode* head1,LinkNode* head2);

//链表相交，求交点
LinkNode* LinkListHasCross(LinkNode* head1,LinkNode* head2);

//判断两个链表是否相交（链表可能带环）
int LinkListCrossWithCycle(LinkNode* head1,LinkNode* head2);

//链表相交，求交点
LinkNode* LinkListHasCrossWithCycle(LinkNode* heda1,LinkNode* head2);

//求两个已排序单链表中相同的数据
LinkNode* LinkListUnionSet(LinkNode* head1,LinkNode* head2);


