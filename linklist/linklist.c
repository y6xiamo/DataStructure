#include"linklist.h"
#include<stdio.h>
#include<stdlib.h>

LinkNode* CreateNode(LinkNodeType value)
{
    LinkNode* new_node =(LinkNode *)malloc(sizeof(LinkNode));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void DestroyNode(LinkNode* node)
{
    free(node);
}
void LinkListInit(PLinkNode* node)
{
    *node = NULL;
}

void LinkListDestroy(LinkNode** phead)
{
    if(phead == NULL)
        return;          //非法输入

    if(phead == NULL)
        return;          //空链表

    LinkNode* cur =  *phead;
    while(cur != NULL)
    {
        LinkNode* to_delete = cur;
        cur = cur->next;
        DestroyNode(to_delete);
    }
    *phead = NULL;
}

void LinkListPushBack(LinkNode** phead,LinkNodeType value)
{
    if(phead == NULL)
        return;         //非法输入

    if(*phead == NULL)
    {
        //空链表
        *phead = CreateNode(value);
        return;
    }
    //链表非空
    LinkNode* cur = *phead;
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    LinkNode* new_node = CreateNode(value);
    cur->next = new_node;
}

void LinkListPopBack(LinkNode** phead)
{
    if(phead ==NULL) 
        return;        //非法输入

    if(*phead == NULL)
        return;        //单链表

    if((*phead)->next == NULL)
    {
        //链表只有一个元素
        DestroyNode(*phead);
        *phead = NULL;
        return;
    }
     LinkNode* cur = *phead;
     LinkNode* pre = NULL;
     while(cur->next != NULL)
     {
         pre = cur;
         cur = cur->next;
     }
     pre->next = NULL;
     DestroyNode(cur);
     return;
}

void LinkListPushFront(LinkNode** phead,LinkNodeType value)
{
    if(phead == NULL)
        return;                      //非法输入

    LinkNode* new_node = CreateNode(value);
    new_node->next = *phead;
    *phead = new_node;
}

void LinkListPopFront(LinkNode** phead)
{
    if(phead == NULL)
        return;              //非法输入
    if(*phead == NULL)
        return;              //空链表

    LinkNode* to_erase = *phead;
    *phead = (*phead)->next;
    DestroyNode(to_erase);
    return;
}

void LinkListInsert(LinkNode* pos,LinkNodeType value)
{
    if(pos == NULL)
        return;            
    //非法输入,pos表示一个节点的指针
    //如果pos为空，说明根本不存再这样的节点
    LinkNode* new_node = CreateNode(value);
    new_node->next = pos->next;
    pos->next = new_node;
    return;
}

void LinkListInsertBefore(LinkNode** phead,LinkNode* pos,LinkNodeType value)
{
    if(phead == NULL ||pos == NULL)
        return;                 //非法输入
  
    if(pos == *phead)
    {
        //要插的地方刚好是头节点
        LinkListPushFront(phead,value);
        return;
    }
    LinkNode* cur = *phead;
    for( ;cur != NULL;cur = cur->next)
    {
        if(cur->next == pos)
        {
            break;
        }
    }
    if(cur == NULL)
    {
        return;
    }
    LinkListInsert(cur,value);
}

void LinkListInsertBefore2(LinkNode* pos,LinkNodeType value)
{
    if(pos == NULL)
    {
        return;            //非法输入
    }
    LinkListInsert(pos,pos->data);
    pos->data = value;
    //交换新插入的节点和pos的位置
}

void LinkListErase(LinkNode** phead,LinkNode* pos)
{
    if((phead == NULL)||(pos == NULL))
       return;       //非法输入

    if(*phead == NULL)
       return;      //空链表

    if(*phead == pos)
        LinkListPopFront(phead);//如果pos是起始位置，调用头删

    LinkNode* cur = *phead;
    for( ;cur != NULL;cur = cur->next)
    {
         if(cur->next == pos)
         {
            cur->next = pos->next;
            pos->next = NULL;
            DestroyNode(pos);
            }
    }
     return;
}

void LinkListErase2(LinkNode** phead,LinkNode* pos)
{

    if((phead == NULL)||(pos == NULL))
       return;       //非法输入

    if(*phead == NULL)
       return;      //空链表

    if(pos->next == NULL)
    {
        //要删除的元素刚好是最后一个元素
        //用原来的尾删方法，仍然需要遍历链表
        LinkListPopBack(phead);
        return;
    }
    pos->data = pos->next->data;
    LinkNode* to_erase = pos->next;
    pos->next = to_erase->next;
    DestroyNode(to_erase);
    return;
}

LinkNode* LinkListFind(LinkNode* phead,LinkNodeType to_find)
{
    if(phead == NULL)
        return NULL;            //空链表

    LinkNode* cur = phead;
    while(cur != NULL)
    {
        if(cur->data == to_find)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

int  LinkListEmpty(LinkNode* phead)
{
    if(phead == NULL)
    {   
        return 1;           //空链表
    }
    else
    {
        return 0;
    }
}

int LinkListSize(LinkNode* phead)
{
    if(phead == NULL)
        return 0;             //空链表

    LinkNode* cur = phead;
    size_t count = 0;
    for( ;cur != NULL;cur = cur->next)
    {
         count++;
    }
    return count;
}

void LinkListRemove(LinkNode** phead,LinkNodeType value)
{
    if(phead == NULL)
        return;            //非法输入

    if(*phead == NULL)
        return;            //空链表

    LinkNode* cur = LinkListFind(*phead,value);
    if(cur == NULL)
    {
        return;
    }
    LinkListErase(phead,cur);
}

void LinkListRemoveAll(LinkNode** phead,LinkNodeType value)
{

    if(phead == NULL)
       return;            //非法输入

    if(*phead == NULL)
       return;            //空链表

    while(1)
    {
            LinkNode* cur = LinkListFind(*phead,value);
            if(cur == NULL)
            {
                 return;
            }
            LinkListErase(phead,cur);
    }
}

//////////////////////////
///////经典面试题////////
////////////////////////
void LinkListReversePrint(LinkNode* phead)
{
    if(phead != NULL)
    {
        if(phead->next != NULL)
        {
            LinkListReversePrint(phead->next); //递归打印
        }
        printf("%c ",phead->data);
    }
    return;
}

void LinkListReverse(LinkNode** phead)
{
    if(phead == NULL)
        return;                //非法输入

    if(*phead == NULL)
        return;                //空链表

    if((*phead)->next == NULL)
        return;                //只有一个元素的链表

    LinkNode* cur = *phead;
    while(cur->next != NULL)
    {
        LinkNode* to_delete = cur->next;
        //删除这个节点
        cur->next = to_delete->next;
        //把刚删除的元素插入到链表头部
        to_delete->next = *phead;
        *phead = to_delete;
    }
}

void LinkListReverse2(LinkNode** phead)
{

    if(phead == NULL)
        return;                //非法输入

    if(*phead == NULL)
        return;                //空链表

    if((*phead)->next == NULL)
        return;                //只有一个元素的链表

    LinkNode* cur = (*phead)->next;
    LinkNode* pre = (*phead);
    pre->next = NULL;
    while(cur != NULL)
    {
        LinkNode* next = cur->next;
        //修改cur->next的指向
        cur->next = pre;
        //更新pre cur
        pre = cur;
        cur = next;
    
    }
    *phead = pre;

}

LinkNode* JosephCircle(LinkNode* head,int M)
{
    if(head == NULL)
        return NULL;           //空链表

    LinkNode* cur = head;
    while(cur->next != cur)
    {
        int i = 1;
        for( ;i < M;i++)
        {
            cur = cur->next;
        }
        //cur指向的元素，就是倒霉的人
        printf("%c\n",cur->data);
        cur->data = cur->next->data;
        LinkNode* to_delete = cur->next;
        cur->next = to_delete->next;
        DestroyNode(to_delete);
    }
    return cur;
}

void Swap(LinkNodeType* a,LinkNodeType* b)
{
    LinkNodeType tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void LinkListBubbleSort(LinkNode* phead)
{
    if(phead == NULL)
        return;    //空链表

    LinkNode* count = phead;
    LinkNode* tail = NULL;
    for( ;count != NULL;count = count->next)
    {
        LinkNode* cur = phead;
        for( ;cur->next != tail;cur = cur->next)
        {
            if(cur->data > cur->next->data)
            {
                Swap(&cur->data,&cur->next->data);
            }
        }
        tail = cur;
    }
    return;
}
          
LinkNode* LinkListMerge(LinkNode* head1,LinkNode* head2)
{
	if(head1 == NULL)
		return head2;
	if(head2 == NULL)
		return head1;
	
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;
	//定义新链表的头节点和尾节点
	LinkNode* new_head = NULL;
	LinkNode* new_tail = NULL;
	while(cur1 != NULL && cur2 != NULL)
	{
		if(cur1->data < cur2->data)
		{
			if(new_tail == NULL)
			{
				new_head = new_tail = cur1;
			}
			else
			{
				new_tail->next = cur1;
				new_tail = new_tail->next;
			}
			cur1 = cur1->next;
		}
		else
		{

			if(new_tail == NULL)
			{
				new_head = new_tail = cur2;
			}
			else
			{
				new_tail->next = cur2;
				new_tail = new_tail->next;
			}
			cur2 = cur2->next;
		}
	}
	//有一方已经先到达末尾，需要把剩余的一方追加到新链表后面
	if(cur1 != NULL)
	{
		new_tail->next = cur1;
	}
	else
	{
		new_tail->next = cur2;
	}
	return new_head;
}

LinkNode* LinkListFindMidNode(LinkNode* phead)
{
	if(phead == NULL)
	{
		return NULL;
	}
	LinkNode* slow = phead;
	LinkNode* fast = phead;
	while(fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

LinkNode* LinkListFindLastKNode(LinkNode* phead,int k)
{
	if(phead == NULL)
		return NULL;           //空链表
	
    LinkNode* fast = phead;
	LinkNode* slow = phead;
	// 让快指针先走k步
	int i = 0;
	for( ;i < k;i++)
	{
		if(fast == NULL)
		{
			break;
		}
		fast = fast->next;
	}
	if(i != k)
	{
		//没走完,k的长度超过了链表长度
		return NULL;
	}
	while(fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}

void LinkListEraseLastKNode(LinkNode** phead,int k)
{
	if(phead == NULL)
		return;             //非法输入
	if(*phead == NULL)
		return;             //空链表

	int len = LinkListSize(*phead);
	if(k == len)
	{
		//要删除的元素，刚好是第一个元素
		LinkNode* to_delete = *phead;
		*phead = (*phead)->next;
		DestroyNode(to_delete);
		return;
	}
	LinkNode* pre = *phead;
	int i = 0;
	for(;i < len-k-1;i++)
	{
		pre = pre->next;
	}
	//循环结束后，表明pre节点已经指向了要删除元素的前一个节点
	LinkNode* to_delete = pre->next;
	pre->next = to_delete->next;
	DestroyNode(to_delete);
	return;
}

LinkNode* LinkListHasCycle(LinkNode* phead)
{
	if(phead == NULL)
		return NULL;

	LinkNode* slow = phead;
	LinkNode* fast = phead;
	while(fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if(fast == slow)
		{
			return slow;
		}
	}
	return NULL;
}

int LinkListCycleLen(LinkNode* phead)
{
	if(phead == NULL)
	{
		return 0;
	}
	
	LinkNode* meet_node = LinkListHasCycle(phead);
	if(meet_node == NULL)
	{
		return 0;
	}
	LinkNode* cur = meet_node->next;
	int Len = 1;
	while(cur != meet_node)
	{
		cur = cur->next;
		++Len;
	}
	return Len;
}

LinkNode* LinkListCycleEntry(LinkNode* phead)
{
	if(phead == NULL)
	{
		return NULL;
	}

	LinkNode* meet_node = LinkListHasCycle(phead);
	if(meet_node == NULL)
	{
		return NULL;
	}

	LinkNode* cur1 = phead;
	LinkNode* cur2 = meet_node;
	while(cur1 != cur2)
	{
        cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return cur1;
}

int LinkListCross(LinkNode* head1,LinkNode* head2)
{
	if(head1 == NULL||head2 == NULL)
	{
		return 0;
	}
	//1.定义cur1指向head1;
	LinkNode* cur1 = head1;
	//2.让cur1遍历链表head1,走到最后一个节点
	while(cur1->next != NULL)
	{
		cur1 = cur1->next;
	}
	//3.定义cur2指向head2;
	LinkNode* cur2 = head2;
	//4.让cur2遍历链表head2，走到最后一个节点
	while(cur2->next != NULL)
	{
		cur2 = cur2->next;
	}
	//5.判断，如果此时cur1和cur2相等，则相交；否则，不相交
	if(cur1 == cur2)
	{
		return 1;
	}
	else
	{

		return 0;
	}
}

LinkNode* LinkListHasCross(LinkNode* head1,LinkNode* head2)
{
	if(head1 == NULL||head2 == NULL)
	{
		return NULL;
	}
	//1.分别计算两个链表的长度
	int len1 = LinkListSize(head1);
	int len2 = LinkListSize(head2);
	//2.定义两个指针分别指向两个链表的头部
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;
	//3.让比较长的链表先走长度之差步（让两个指针在统一起跑线）
	if(len1 > len2)
	{
		size_t i = 0;
		for( ;i < len1-len2;++i)
		{
			cur1 = cur1->next;
		}
	}
	else
	{
		size_t i = 0;
		for( ;i < len2-len1;++i)
		{
			cur2 = cur2->next;
		}
	}
	//4.让两个指针同时开始走，一次走一步
	//5.如果两指针重合，则说明此位置就是交点
	while(cur1 != NULL && cur2 != NULL)
	{
		if(cur1 == cur2)
		{
			return cur1;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return NULL;

}

int LinkListCrossWithCycle(LinkNode* head1,LinkNode* head2)
{
	//1.分别求两个链表的环的入口点
	LinkNode* entry1 = LinkListCycleEntry(head1);
	LinkNode* entry2 = LinkListCycleEntry(head2);
	//2.如果两个链表都不带环，直接用前面的方式判定相交
	if(entry1 == NULL && entry2 == NULL)
	{
		return LinkListCross(head1,head2);
	}
	//3.如果一个带环，一个不带环，那么直接返回不相交
	if((entry1 == NULL && entry2 != NULL)||(entry1 != NULL && entry2 == NULL))
	{
		return 0;
	}
	//4.如果两个链表都带环
	//   a)如果这两个入口点重合，说明相交，并且是环外相交
	if(entry1 == entry2)
	{
		return 1;
	}
	//   b)如果从一个入口点出发，绕环一周，能到达第二个入口点，说明是环上相交
	LinkNode* cur = entry1->next;
	while(cur != entry1)
	{
		if(cur == entry2)
		{
			return 1;
		}
		cur = cur->next;
	}
	//   c)如果不是上面这两种情况，说明不相交
	return 0;
}

LinkNode* LinkListHasCrossWithCycle(LinkNode* head1,LinkNode* head2)
{
	if(head1 == NULL||head2 == NULL)
	{
		return NULL;
	}
	int i = LinkListCrossWithCycle(head1,head2);
	if(i == 0)
	{
	   return NULL;
	}
    //1.求环的入口点
	LinkNode* entry1 = LinkListCycleEntry(head1);
	LinkNode* entry2 = LinkListCycleEntry(head2);
	//2.判断是那种情况相交
	if(entry1 != entry2)//环上相交
	{
        return entry2;
	}
	//3.标记入口点
	LinkNode* end = entry1;
	//4.另一种情况，环外相交，分别计算两个链表头到入口点的长度
	//5.定义两个指针分别指向两个链表的头部
	int len1 = 0;
	int len2 = 0;
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;
    for( ;cur1 != end;cur1 = cur1->next)
    {
         len1++;
    }
    for( ;cur2 != end;cur2 = cur2->next)
    {
         len2++;
    }
	//6.让比较长的链表先走长度之差步（让两个指针在统一起跑线）
	if(len1 > len2)
	{
		size_t i = 0;
		for( ;i < len1-len2;++i)
		{
			cur1 = cur1->next;
		}
	}
	else
	{
		size_t i = 0;
		for( ;i < len2-len1;++i)
		{
			cur2 = cur2->next;
		}
	}
	//7.让两个指针同时开始走，一次走一步
	//8.如果两指针重合，则说明此位置就是交点
	while(cur1 != end->next && cur2 != end->next)
	{
		if(cur1 == cur2)
		{
			return cur1;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return NULL;
	
}

LinkNode* LinkListUnionSet(LinkNode* head1,LinkNode* head2)
{
	if(head1 == NULL || head2  == NULL)
	{
		return NULL;
	}
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;

	LinkNode* new_head = NULL;
	LinkNode* new_tail = NULL;
	while(cur1 != NULL && cur2 != NULL)
	{
		if(cur1->data < cur2->data)
		{
			cur1 = cur1->next;
		}
		else if(cur1->data > cur2->data)
		{
            cur2 = cur2->next;
		}
		else
		{
			if(new_head == NULL)
			{
				new_head = new_tail = CreateNode(cur1->data);
			}
			else
			{
				new_tail->next = CreateNode(cur1->data);
				new_tail =new_tail->next;
			}

	      	cur1 = cur1->next;
	    	cur2 = cur2->next;
		}
	}
	return new_head;
}


typedef struct ComplexNode
{
	LinkNodeType data;
	struct ComplexNode* next;
	struct ComplexNode* random;
}ComplexNode;

ComplexNode* CreateComplexNode(LinkNodeType value)
{
	ComplexNode* new_node = (ComplexNode*)malloc(sizeof(ComplexNode));
	new_node->data = value;
	new_node->next = NULL;
	new_node->random = NULL;
	return new_node;
}

size_t Diff(ComplexNode* src,ComplexNode* dest)
{
	size_t offset = 0;
    while(src != NULL)
	{
		if(src == dest)
		{
			break;
		}
		offset++;
		src = src->next;
	}
	if(src == NULL)
	{
		return (size_t)-1;
	}
	return offset;

}

ComplexNode* Step(ComplexNode* head,size_t offset)
{
	ComplexNode* cur = head;
	size_t i = 0;
	while(1)
	{
		if(cur == NULL)
		{
			return NULL;
		}
		if(i >= offset)
		{
			return cur;
		}
		++i;
		cur = cur->next;	
	}
	return cur;
}
ComplexNode* CopyComplexList(ComplexNode* head)
{
	//1.先按照简单链表的方式进行复制
	ComplexNode* new_head = NULL;
	ComplexNode* new_tail = NULL;
	ComplexNode* cur = head;
	for( ;cur != NULL;cur = cur->next)
	{
		ComplexNode* new_node = CreateComplexNode(cur->data);
		if(new_head == NULL)
		{
			new_head = new_tail = new_node;
		}
		else
		{
			new_tail->next = new_node;
			new_tail = new_tail->next;
		}
	}
	//2.遍历旧链表，找到每个链表节点的random指针相对于链表头节点的偏移量
	//3.遍历新链表，根据偏移量，设置新链表的random指针
	ComplexNode* new_cur = new_head;
	for(cur = head;cur != NULL;cur = cur->next,new_cur = new_cur->next)
	{
		if(cur->random == NULL)
		{
			new_cur->random = NULL;
				continue;
		}
		//通过Diff函数找到random的偏移量
		size_t offset = Diff(head,cur->random);
		//通过Step函数设置新链表的Random指针
		new_cur->random = Step(new_head,offset);
	}
	return new_head;
}

ComplexNode* CopyComplexList2(ComplexNode* head)
{
	//1.遍历链表，给每个结点之后插入新结点
	ComplexNode* cur = head;
	for( ;cur != NULL;cur = cur->next->next)
	{
		ComplexNode* new_node = CreateComplexNode(cur->data);
		new_node->next = cur->next;
		cur->next = new_node;
	}
	//2.维护新结点的randon指针
	for(cur = head;cur != NULL;cur = cur->next->next)
	{
		ComplexNode* new_cur = cur->next;
		if(cur->random == NULL)
		{
			new_cur->random = NULL;
			continue;
		}
		new_cur->random = cur->random->next;
	}
	//3.将新结点拆除
	ComplexNode* new_head = NULL;
	ComplexNode* new_tail = NULL;
	for(cur = head;cur != NULL;cur = cur->next)
	{
		ComplexNode* new_cur = cur->next;
		cur->next = new_cur->next;
        if(new_head == NULL)
		{
			new_head = new_tail = new_cur;
		}
		else
		{
		    new_tail->next = new_cur;
		    new_tail = new_tail->next;
		}
	}
	
	return new_head;
}

/*#include<unordered_map>
ComplexNode* CopyComplexList3(ComplexNode* head)
{
     std::unordered_map<ComplexNode*,ComplexNode*>table;
	 for(ComplexNode* cur = head;cur != NULL;cur = cur->next)
	 {
		 table[cur] = CreateComplexNode(cur->data);
	 }
	 for(ComplexNode* cur = head;cur != NULL;cur =  cur->next)
	 {
		 table[cur]->random = table[cur->random];
	 }
	 return table[head];
}
*/
/////////////////////////////////////////////////////////
///////////////////以下为测试代码///////////////////////
///////////////////////////////////////////////////////

#define TEST_HEADER printf("\n=====================%s====================\n",__FUNCTION__)

void LinkListPrintChar(LinkNode* head,const char* msg)
{
    printf("[%s]\n",msg);
    LinkNode* cur = head;
    for( ;cur != NULL;cur = cur->next)
    {
        printf("[%c|%p] ",cur->data,cur);
    }
    printf("\n");
    
}

void TestInit()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);

}

void TestPushBack()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPrintChar(head,"尾插四个元素");
}

void TestPopBack()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPopBack(&head);
    LinkListPrintChar(head," 对空链表尾删");

    LinkListPushBack(&head,'a');
    LinkListPopBack(&head);
    LinkListPrintChar(head,"对只有一个元素的链表尾删");

    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPopBack(&head);
    LinkListPopBack(&head);
    LinkListPrintChar(head,"尾删两个元素");
    LinkListPopBack(&head);
    LinkListPopBack(&head);
    LinkListPrintChar(head,"再尾删两个元素");
}

void TestPushFront()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d');
    LinkListPrintChar(head,"头插四个元素");
}

void TestPopFront()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPopFront(&head);
    LinkListPrintChar(head,"对空链表头删");

    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d');
    LinkListPrintChar(head,"头插四个元素");

    LinkListPopFront(&head);
    LinkListPopFront(&head);
    LinkListPrintChar(head,"头删两个元素");
    LinkListPopFront(&head);
    LinkListPopFront(&head);
    LinkListPrintChar(head,"再头删两个元素");
}

void TestInsert()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');

    LinkNode* pos = head->next;
    LinkListInsert(pos,'x');
    LinkListPrintChar(head,"插入'x'元素");
}

void TestInsertBefore()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');

    LinkNode* pos1 = head;
    LinkListInsertBefore(&head,pos1,'x');
    LinkListPrintChar(head,"向头节点之前插入'x'元素");

    LinkNode* pos2 = head->next->next;
    LinkListInsertBefore(&head,pos2,'y');
    LinkListPrintChar(head,"向'b'之前插入'y'元素");
}

void TestInsertBefore2()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');

    LinkNode* pos1 = head;
    LinkListInsertBefore(&head,pos1,'x');
    LinkListPrintChar(head,"向头节点之前插入'x'元素");

    LinkNode* pos2 = head->next->next;
    LinkListInsertBefore(&head,pos2,'y');
    LinkListPrintChar(head,"向'b'之前插入'y'元素");
}

void TestErase()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);

    LinkListErase(&head,(LinkNode*)0x11);
    LinkListPrintChar(head,"尝试对空链表删除");

    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');

    LinkNode* pos= head;
    LinkListErase(&head,pos);
    LinkListPrintChar(head,"删除元素'a'");

    LinkNode* pos2 = (LinkNode*)0x10;
    LinkListErase(&head,pos2);
    LinkListPrintChar(head,"尝试对一个不存在的位置删除");
}

void TestErase2()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);

    LinkListErase(&head,(LinkNode*)0x11);
    LinkListPrintChar(head,"尝试对空链表删除");

    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');

    LinkNode* pos = head->next;
    LinkListErase(&head,pos);
    LinkListPrintChar(head,"删除元素'b'");

    LinkNode* pos2 = (LinkNode*)0x10;
    LinkListErase(&head,pos2);
    LinkListPrintChar(head,"尝试对一个不存在的位置删除");
}

void TestFind()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);

    LinkNode* pos =  LinkListFind(head,'a');
    printf("'a'的地址是：%p\n",pos);

    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');

    LinkNode* pos1 =  LinkListFind(head,'c');
    printf("'c'的地址是：%p\n",pos1);

    LinkNode* pos2 =  LinkListFind(head,'x');
    printf("'x'的地址是：%p",pos2);
}

void TestEmpty()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);

    size_t cur1 = LinkListEmpty(head);
    printf("%d\n",cur1);

    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');

    size_t cur2 = LinkListEmpty(head);
    printf("%d",cur2);
}

void TestSize()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);

    size_t cur1 = LinkListSize(head);
    printf("%d\n",cur1);

    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');

    size_t cur2 = LinkListSize(head);
    printf("%d",cur2);
}

void TestRemove()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);

    LinkListRemove(&head,'a');
    LinkListPrintChar(head,"尝试对空链表删除");

    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');

    LinkListRemove(&head,'a');
    LinkListPrintChar(head,"删除元素'a'");

    LinkListRemove(&head,'x');
    LinkListPrintChar(head,"尝试删除一个不存在的值");
}
void TestRemoveAll()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);

    LinkListRemoveAll(&head,'a');
    LinkListPrintChar(head,"尝试对空链表删除");

    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'a');

    LinkListRemoveAll(&head,'a');
    LinkListPrintChar(head,"删除元素'a'");

    LinkListRemoveAll(&head,'x');
    LinkListPrintChar(head,"尝试删除一个不存在的值");
}

void TestReversePrint()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);

    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    printf("[逆序打印链表]\n");
    LinkListReversePrint(head);
}

void TestReverse()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);

    LinkListReverse(&head);
    LinkListPrintChar(head,"尝试对空链表操作");

    LinkListPushBack(&head,'a');
    LinkListReverse(&head);
    LinkListPrintChar(head,"对只有一个元素的链表逆序");

    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListReverse(&head);
    LinkListPrintChar(head,"逆序链表");
}
void TestReverse2()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);

    LinkListReverse2(&head);
    LinkListPrintChar(head,"尝试对空链表操作");

    LinkListPushBack(&head,'a');
    LinkListReverse2(&head);
    LinkListPrintChar(head,"对只有一个元素的链表逆序");

    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListReverse2(&head);
    LinkListPrintChar(head,"逆序链表");
}

void TestJosephCircle()
{
    TEST_HEADER;
    LinkNode* a = CreateNode('a');
    LinkNode* b = CreateNode('b');
    LinkNode* c = CreateNode('c');
    LinkNode* d = CreateNode('d');
    LinkNode* e = CreateNode('e');
    LinkNode* f = CreateNode('f');
    LinkNode* g = CreateNode('g');
    LinkNode* h = CreateNode('h');
    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    e->next = f;
    f->next = g;
    g->next = h;
    h->next = a;

    LinkNode* survive = JosephCircle(a,5);
    printf("survive is %c\n",survive->data);
}

void TestBubbleSort()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
 
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'f');
    LinkListPushBack(&head,'e');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'g');
    LinkListPushBack(&head,'h');
    LinkListPushBack(&head,'d');

    LinkListBubbleSort(head);
    LinkListPrintChar(head,"冒泡排序");
}
void TestMerge()
{
    TEST_HEADER;
    LinkNode* head1;
	LinkNode* head2;
	LinkNode* head3;
    LinkListInit(&head1);
	LinkListInit(&head2);
	LinkListInit(&head3);
			
    LinkListPushBack(&head1,'a');
    LinkListPushBack(&head1,'b');
    LinkListPushBack(&head1,'c');
    LinkListPushBack(&head1,'d');
    LinkListPushBack(&head2,'e');
    LinkListPushBack(&head2,'f');
    LinkListPushBack(&head2,'g');
    LinkListPushBack(&head2,'h');

	head3 = LinkListMerge(head1,head2);
	LinkListPrintChar(head3,"将已经有序的两个链表合并成一个有序链表");
}

void TestFindMidNode()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    
	LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');

	LinkNode* Mid = LinkListFindMidNode(head);
	LinkListPrintChar(head,"查找链表的中间节点");
	printf("Mid expected is c,actual is %c\n ",Mid->data);
}

void TestFindLastKNode()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    
	LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');

	LinkNode* LastK = LinkListFindLastKNode(head,2);
	LinkListPrintChar(head,"查找链表的倒数第2个节点");
	printf("Mid expected is d,actual is %c\n ",LastK->data);
}

void TestEraseLastKNode()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    
	LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');

    LinkListEraseLastKNode(&head,2);
	LinkListPrintChar(head,"删除链表的倒数第2个节点");
}

void TestHasCycle()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    
	LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');
	
	LinkNode* pos_e = LinkListFind(head,'e');
	pos_e->next =head->next->next;

	LinkNode* meet_node= LinkListHasCycle(head);

	printf("meet_node expected is d,actual is %c\n",meet_node->data);
}

void TestCycleLen()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    
	LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');
	
	LinkNode* pos_e = LinkListFind(head,'e');
	pos_e->next =head->next->next;

	int len= LinkListCycleLen(head);
	printf("len expected is 3,actual is %d\n",len);
}

void TestCycleEntry()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    
	LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');
	
	LinkNode* pos_e = LinkListFind(head,'e');
	pos_e->next =head->next->next;

	LinkNode* entry_node = LinkListCycleEntry(head);
	printf("entry_node expected is c,actual is %c\n",entry_node->data);
}

void TestCross()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
	LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');
    
	LinkNode* head2;
    LinkListInit(&head2);
	LinkListPushBack(&head2,'a');
    LinkListPushBack(&head2,'b');
    LinkListPushBack(&head2,'c');
	LinkNode* pos_c = LinkListFind(head2,'c');
	pos_c->next = head->next;

	int ret = LinkListCross(head,head2);
	printf("ret excepted is 1,actual is %d\n",ret);
}

void TestHasCross()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
	LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');
    
	LinkNode* head2;
    LinkListInit(&head2);
	LinkListPushBack(&head2,'a');
    LinkListPushBack(&head2,'b');
    LinkListPushBack(&head2,'c');
	LinkNode* pos_c = LinkListFind(head2,'c');
	pos_c->next = head->next;

	LinkNode* cross = LinkListHasCross(head,head2);
	printf("cross expected is b,actual is %c\n",cross->data);
}

void TestCrossWithCycle()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
	LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');
	
    LinkNode* head1;
    LinkListInit(&head1);
	LinkListPushBack(&head1,'a');
    LinkListPushBack(&head1,'b');
    LinkListPushBack(&head1,'c');
    LinkListPushBack(&head1,'d');

	int ret1 = LinkListCrossWithCycle(head,head1);
	printf("[两个链表都不带环]\n");
	printf("ret1 expected is 0,actual is %d\n",ret1);

    LinkNode* head2;
    LinkListInit(&head2);   
	LinkListPushBack(&head2,'a');
    LinkListPushBack(&head2,'b');
    LinkListPushBack(&head2,'c');
    LinkListPushBack(&head2,'d');
    LinkListPushBack(&head2,'e');
	LinkNode* pos_e = LinkListFind(head2,'e');
	pos_e->next =head2->next->next;

    LinkNode* head3;
    LinkListInit(&head3);   
	LinkListPushBack(&head3,'a');
    LinkListPushBack(&head3,'b');
    LinkListPushBack(&head3,'c');
    LinkListPushBack(&head3,'d');
    LinkListPushBack(&head3,'e');
	LinkNode* pos_2e = LinkListFind(head3,'e');
	pos_2e->next =head3->next;

	int ret2 = LinkListCrossWithCycle(head2,head3);
	printf("[两个链表都带环]\n");
	printf("ret2 expected is 0,actual is %d\n",ret2);

	LinkNode* head4;
    LinkListInit(&head4);
	LinkListPushBack(&head4,'a');
    LinkListPushBack(&head4,'b');
    LinkListPushBack(&head4,'c');
	LinkNode* pos_c = LinkListFind(head4,'c');
	pos_c->next = head2->next;

	int ret3 = LinkListCrossWithCycle(head2,head4);
	printf("[两个链表都带环，满足a情况]\n");
	printf("ret3 expected is 1,actual is %d\n",ret3);

    LinkNode* head5;
    LinkListInit(&head5);
	LinkListPushBack(&head5,'a');
    LinkListPushBack(&head5,'b');
    LinkListPushBack(&head5,'c');
    LinkListPushBack(&head5,'d');
	LinkNode* pos_d = LinkListFind(head5,'d');
	pos_d->next =head2->next->next->next;

	int ret4 = LinkListCrossWithCycle(head2,head5);
	printf("[两个链表都带环，满足b情况]\n");
	printf("ret4 expected is 1,actual id %d\n",ret4);
}

void TestHasCrossWithCycle()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
	LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');	
	LinkNode* pos_e = LinkListFind(head,'e');
	pos_e->next =head->next->next;

    LinkNode* head1;
    LinkListInit(&head1);
	LinkListPushBack(&head1,'a');
    LinkListPushBack(&head1,'b');
    LinkListPushBack(&head1,'c');
    LinkListPushBack(&head1,'d');
	LinkNode* pos_d = LinkListFind(head1,'d');
	pos_d->next = head->next;

	LinkNode* cross = LinkListHasCrossWithCycle(head,head1);
	printf("[两个链表都带环，环外相交]\n");
	printf("cross expected c,actual %c\n",cross->data);

	LinkNode* head2;
	LinkListPushBack(&head2,'a');
    LinkListPushBack(&head2,'b');
	LinkListPushBack(&head2,'c');
    LinkListPushBack(&head2,'d');
	LinkNode* pos_d2 = LinkListFind(head2,'d');
	pos_d2->next =head->next->next->next;

	LinkNode* cross2 = LinkListHasCrossWithCycle(head,head2);
	printf("[两个链表都带环，环上相交，入口点就是交点]\n");
	printf("cross2 expected c或者d,actual %c\n",cross2->data);
}
void TestUnionSet()
{

    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
	LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');
   
    LinkNode* head1;
    LinkListInit(&head1);
	LinkListPushBack(&head1,'a');
    LinkListPushBack(&head1,'c');
    LinkListPushBack(&head1,'e');
    LinkListPushBack(&head1,'f');
    LinkListPushBack(&head1,'h');
	LinkNode* union_set = LinkListUnionSet(head,head1);
	LinkListPrintChar(union_set,"链表的交集是：");
}

void PrintComplexList(ComplexNode* head,const char* msg)
{
	printf("[%s]\n",msg);
	ComplexNode* cur = head;
	for( ;cur != NULL;cur = cur->next)
	{
		printf("[%c]",cur->data);
	}
	printf("\n");
	for(cur = head ;cur != NULL;cur = cur->next)
	{
		if(cur->random == NULL)
		{
			printf("[NULL]");
			continue;
		}
		printf("[%c]",cur->random->data);
	}
	printf("\n");
}
void TestCopyComplexList()
{
	TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
	ComplexNode* a = CreateComplexNode('a');
	ComplexNode* b = CreateComplexNode('b');
	ComplexNode* c = CreateComplexNode('c');
	ComplexNode* d = CreateComplexNode('d');
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = NULL;
	a->random = c;
	b->random = a;
	c->random = NULL;
	d->random = d;

    ComplexNode*  new_head= CopyComplexList(a);
	PrintComplexList(new_head,"复杂链表的复制");
}

void TestCopyComplexList2()
{
	TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
	ComplexNode* a = CreateComplexNode('a');
	ComplexNode* b = CreateComplexNode('b');
	ComplexNode* c = CreateComplexNode('c');
	ComplexNode* d = CreateComplexNode('d');
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = NULL;
	a->random = c;
	b->random = a;
	c->random = NULL;
	d->random = d;

	ComplexNode*  new_head = CopyComplexList2(a);
	PrintComplexList(new_head,"复杂链表的复制");
}

/*void TestCopyComplexList3()
{
	TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
	ComplexNode* a = CreateComplexNode('a');
	ComplexNode* b = CreateComplexNode('b');
	ComplexNode* c = CreateComplexNode('c');
	ComplexNode* d = CreateComplexNode('d');
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = NULL;
	a->random = c;
	b->random = a;
	c->random = NULL;
	d->random = d;

	ComplexNode*  new_head = CopyComplexList3(a);
	PrintComplexList(new_head,"复杂链表的复制");
}
*/
int main()
{

	TestInit();
	TestPushBack();
	TestPopBack();
	TestPushFront();
	TestPopFront();
    TestInsert();
	TestInsertBefore();
	TestInsertBefore2();
	TestErase();
	TestErase2();
	TestFind();
	TestEmpty();
	TestSize();
	TestRemove();
	TestRemoveAll();
	TestReversePrint();
	TestReverse();
	TestReverse2();
	TestJosephCircle();
	TestBubbleSort();
	TestMerge();
	TestFindMidNode();
	TestFindLastKNode();
	TestEraseLastKNode();
	TestHasCycle();
	TestCycleLen();
	TestCycleEntry();
	TestCross();
	TestHasCross();
	TestCrossWithCycle();
    TestHasCrossWithCycle();
	TestUnionSet();
	TestCopyComplexList();
	TestCopyComplexList2();
//	TestCopyComplexList3();
    printf("\n");
	return 0;
}
