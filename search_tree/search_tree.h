#pragma once

typedef char SearchNodeType;

typedef struct SearchNode
{
    SearchNodeType data;
    struct SearchNode* lchild;
    struct SearchNode* rchild;
}SearchNode;

void SeachTreeInit(SearchNode** pRoot);//初始化

void SearchTreeDestroy(SearchNode** pRoot);//销毁

void SearchTreeInsert(SearchNode** pRoot,SearchNodeType to_insert);//插入

//void SearchTreeErase(SearchNode* root);//删除

//查找一个元素在二叉搜索树中的位置
SearchNode* SearchTreeFind(SearchNode* root,SearchNodeType to_find);

void SearchTreeRemove(SearchNode** pRoot,SearchNodeType to_remove);//按照值来删除

