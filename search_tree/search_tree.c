#include <stdio.h>
#include<stdlib.h>
#include"search_tree.h"

void SearchTreeInit(SearchNode** pRoot)
{
    if(pRoot == NULL)
    {
        return;//非法输入
    }
    *pRoot = NULL;
    return;
}

SearchNode* CreateSearchNode(SearchNodeType value)
{
    SearchNode* new_node = (SearchNode*)malloc(sizeof(SearchNodeType));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
     return new_node;
}

void DestroySearchNode(SearchNode* root)
{
    free(root);
}
void SearchTreeDestroy(SearchNode** pRoot)
{
    if(pRoot == NULL)
    {
        return;//非法输入
    }
    if(*pRoot == NULL)
    {
        return;//空树
    }
    SearchNode* root = *pRoot;
    SearchTreeDestroy(&root->lchild);
    SearchTreeDestroy(&root->rchild);
    DestroySearchNode(root);
    *pRoot = NULL;
    return;
}

#if 0
void SearchTreeInsert(SearchNode** pRoot,SearchNodeType to_insert)
{
    if(pRoot == NULL)
    {
        return;//非法输入
    }
    if(*pRoot == NULL)
    {
        //空树，直接插入
        SearchNode* new_node = CreateSearchNode(to_insert);
        *pRoot = new_node;
        return;
    }
    //对于不是空树的情况，非递归的插入
    SearchNode* cur = *pRoot;
    if(to_insert < cur->data)
    {
        //递归的往左子树插入
        SearchTreeInsert(&cur->lchild,to_insert);
    }
    else if(to_insert > cur->data)
    {
        //递归的往右子树插
        SearchTreeInsert(&cur->rchild,to_insert);
    }
    else
    {
        //对于相当的情况，直接返回
        //此时不允许树中有重复的元素
        return;
    }
}

//递归的查找
SearchNode* SearchTreeFind(SearchNode* root,SearchNodeType to_find)
{
    if(root == NULL)
    {
        return NULL;//空树
    }
    if(to_find < root->data)
    {
        //递归的在左子树中查找
       return  SearchTreeFind(root->lchild,to_find);
    }
    else if(to_find > root->data)
    {
        //递归的在右子树中查找
       return  SearchTreeFind(root->rchild,to_find);
    }
    else
    {
        //相等，直接返回
        return root;
    }
}


void SearchTreeRemove(SearchNode** pRoot,SearchNodeType to_remove)
{
    if(pRoot == NULL)
    {
        return;//非法输入
    }
    if(*pRoot == NULL)
    {
        return;//空树
    }
    //1.先找到要删除节点所在的位置
    SearchNode* root = *pRoot;
    //2.如果没找到，直接返回；
    if(to_remove < root->data)
    {
        SearchTreeRemove(&root->lchild,to_remove);
        return;
    }
    else if(to_remove > root->data)
    {
        SearchTreeRemove(&root->rchild,to_remove);
        return;
    }
    else
    {
        //3.如果找到了，分情况讨论
        SearchNode* to_remove_node = root;
        //  a)该节点没有子树；
        if(root->lchild == NULL && root->rchild == NULL) 
        {
            DestroySearchNode(to_remove_node);
            *pRoot = NULL;
            return;
        }
        //  b)该节点只有左子树；
        else if(root->lchild != NULL && root->rchild == NULL)
        {
            *pRoot = to_remove_node->lchild;
            DestroySearchNode(to_remove_node);
            return;
        }
        //  c)该节点只有右子树；
        else if(root->lchild == NULL && root->rchild != NULL)
        {
            *pRoot = to_remove_node->rchild;
            DestroySearchNode(to_remove_node);
            return;
        }
        //  d)该节点有左右子树。
        else
        {
            //先找到右子树中的最小值；
            //然后将要删除的节点和最小节点交换；
            //最后从右子树出发，尝试递归的删除刚刚交换的值。
            SearchNode* min = to_remove_node->rchild;
            if(min->lchild != NULL)
            {
                min = min->lchild;
            }
            //min此时已将指向了要删除节点右子树中的最小节点
            //这里我们可以不用交换，直接将最小节点的值赋给要删除节点
            to_remove_node->data = min->data;
            //然后尝试递归的删除min->data
            SearchTreeRemove(&to_remove_node,min->data);
            //return;
        }

    }
    return;
}
#endif

#if 1
//非递归的实现二叉搜索树的插入、查找和删除操作
void SearchTreeInsert(SearchNode** pRoot,SearchNodeType to_insert)
{
    if(pRoot == NULL)
    {
        return;//非法输入
    }
    if(*pRoot == NULL)
    {
        //空树，直接插入
        *pRoot = CreateSearchNode(to_insert);
        return;
    }
    //表示新元素要插入的位置
    SearchNode* cur = *pRoot;
    //代表新元素的父节点
    SearchNode* pre = NULL;
   //借助下面这个循环帮我们找到要插入的位置
    while(1)
    {
        if(cur == NULL)
        {
            //找到要插入的地方了，跳出循环
            break;
        }
        if(to_insert < cur->data)
        {
            pre = cur;
            cur = cur->lchild;
        }
        else if(to_insert > cur->data)
        {
            pre = cur;
            cur = cur->rchild;
        }
        else
        {
            //不允许有重复的元素，直接返回
            return;
        }
    }
    //这里pre不可能为空，因为如果pre为空，
    //说明刚一进循环就满足cur == NULL，
    //而cur为空的情况在前面已经讨论过了
    SearchNode* new_node = CreateSearchNode(to_insert);
    if(new_node->data < pre->data)
    {
        pre->lchild = new_node;
    
    }
    else
    {
        pre->rchild = new_node;
    }
    return;
}

SearchNode* SearchTreeFind(SearchNode* root,SearchNodeType to_find)
{
    if(root == NULL)
    {
        return NULL;//空树
    }
    //cur用于树的遍历
    SearchNode* cur = root;
    while(1)
    {
        //遍历结束
        if(cur == NULL)
        {
            break;
        }
        //在左子树中寻找
        if(to_find < cur->data)
        {
            cur = cur->lchild;
        }
        else if(to_find > cur->data)
        {
            //在右子树中找
            cur = cur->rchild;
        }
        else
        {
            //相等，直接返回当前位置
            return cur;
        }
    }
    //遍历结束，还没有找到，说明不存在，返回空
    return NULL;
}

void SearchTreeRemove(SearchNode** pRoot,SearchNodeType to_remove)
{
    if(pRoot == NULL)
    {
        return;//非法输入
    }
    if(*pRoot == NULL)
    {
        return;//空树
    }
    //1.先找到要删除节点所在的位置
    SearchNode* to_remove_node = *pRoot;
    SearchNode* parent = NULL;
    while(1)
    {
        if(to_remove_node == NULL)
        {
            //2.如果没找到要删除的元素，直接返回
            return;
        }
        if(to_remove < to_remove_node->data)
        {
            parent = to_remove_node;
            to_remove_node = to_remove_node->lchild;
        }
        else if(to_remove > to_remove_node->data)
        {
            parent = to_remove_node;
            to_remove_node = to_remove_node->rchild;
        }
        else
        {
            //找到要删除元素所在的位置，直接返回
            break;
        }
    }
        //3.找到要删除元素所在的位置，分情况讨论
        // a)要删除的元素没有左右子树
        if(to_remove_node->lchild == NULL && to_remove_node->rchild == NULL)
        {
            //此处我们要先判断要删除的节点是否是根结点
            if(to_remove_node == *pRoot)
            {
                //要删除的节点是根结点
                *pRoot = NULL;
            }
            else
            {
                //要删除的节点不是根结点
                //这里我们需要知道要删除的节点是其父节点parent的左子树还是右子树
                if(to_remove_node->data < parent->data)
                {
                    parent->lchild = NULL;
                }
                else
                {
                    parent->rchild = NULL;
                }
            }
            //统一释放节点
            DestroySearchNode(to_remove_node);
            return;
        }
        // b)只有左子树
        else if(to_remove_node->lchild != NULL && to_remove_node->rchild == NULL)
        {
            if(to_remove_node == *pRoot)
            {
                //要删除节点是根结点
                *pRoot = to_remove_node->lchild;
            }
            else
            {
                if(to_remove_node->data < parent->data)
                {
                    parent->lchild = to_remove_node->lchild;
                }
                else
                {
                    parent->rchild = to_remove_node->lchild;
                }
            }
            //统一释放节点
            DestroySearchNode(to_remove_node);
            return;
        }
        // c)只有右子树
       else  if(to_remove_node->lchild == NULL && to_remove_node->rchild != NULL)
        {
            if(to_remove_node == *pRoot)
            {
                *pRoot = to_remove_node->rchild;
            }
            else
            {
                if(to_remove_node->data < parent->data)
                {
                    parent->lchild = to_remove_node->rchild;
                }
                else
                {
                    parent->rchild = to_remove_node->rchild;
                }
            }
            //统一释放节点
            DestroySearchNode(to_remove_node);
        }
        // d)有左右子树
        else
        {
            //这块和递归的一样
            //先找到要删除节点右子树中的最小值
            //然后将其值赋给要删除元素。最后删除这个最小值
            //min用于遍历要删除节点的右子树，从其右子树出发，来找到最小值
            SearchNode* min = to_remove_node->rchild;
            //min_parent用于标记最小值的父节点 
            SearchNode* min_parent = to_remove_node;
            while(min->lchild == NULL)
            {
                min_parent = min;
                min = min->lchild;
            }
            //循环结束，此时min指向了右子树中的最小值
            to_remove_node->data = min->data;
            if(min->data < min_parent->data)
            {
                //min是min_parent的左子树
                //min一定没有左子树
                min_parent->lchild = min->rchild;
            }
            else
            {
                //通常情况下，min是min_parent的左子树
                //但是初始情况例外
                min_parent->rchild = min->rchild;
            }
        }
    
}
#endif
///////////////////////////////////////
////////////以下是测试代码////////////
/////////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n==============%s==============\n",__FUNCTION__)

void PreOrder(SearchNode* root)
{
    if(root == NULL)
    {
        return;//空树
    }
    printf("%c ",root->data);
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}

void InOrder(SearchNode* root)
{
    if(root == NULL)
    {
        return;//空树
    }
    InOrder(root->lchild);
    printf("%c ",root->data);
    InOrder(root->rchild);
}
void SearchTreePrint(SearchNode* root,char* msg)
{
    if(root == NULL)
    {
        return;//空树
    }
    printf("[%s]\n",msg);

    printf("[先序遍历]\n");
    PreOrder(root);
    printf("\n");

    printf("[中序遍历]\n");
    InOrder(root);
    printf("\n");
}
void TestInit()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    printf("root expected NULL,actual is %p",root);
}

void TestInsert()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'d');
    SearchTreePrint(root,"插入五个元素");
}

void TestFind()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'d');

    SearchNode* result = SearchTreeFind(root,'b');
    printf("result expected b,actual is %c\n",result->data);

    result = SearchTreeFind(root,'f');
    printf("result expected null,actual is %p\n",result);

}

void TestRemove()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'d');

    SearchTreeRemove(&root,'e');
    SearchTreePrint(root,"删除元素e");
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
