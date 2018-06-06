#pragma once

#include<stddef.h>

typedef char TreeNodeType;

typedef struct TreeNode
{
	TreeNodeType data;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
}TreeNode;


void TreeInit(TreeNode** pRoot);//初始化


void TreePreOrder(TreeNode* root);//先序遍历

void TreeInOrder(TreeNode* root);//中序遍历

void TreePostOrder(TreeNode* root);//后序遍历

void TreeLevelOrder(TreeNode* root);// 层序遍历


TreeNode* CloneTree(TreeNode* root);//克隆树

void TreeDestroy(TreeNode* root);//销毁树

size_t TreeSize(TreeNode* root);//求树的节点个数

size_t TreeLeafSize(TreeNode* root);//求叶子节点个数

size_t TreeKLevelSize(TreeNode* root,size_t k);//求第k层节点个数

size_t TreeHeight(TreeNode* root);//求树的高度

TreeNode* TreeFind(TreeNode* root,TreeNodeType to_find);//在于一个树中找某个值的位置

TreeNode* ParentTree(TreeNode* root,TreeNode* child);//找一个节点的父节点

TreeNode* LChildNode(TreeNode* root,TreeNode* lchild);//找一个节点的左节点

TreeNode* RChildNode(TreeNode* root,TreeNode* rchild);//找一个节点的右节点

//面试题
void TreePreOrderByLoop(TreeNode* root);//通过循环实现树的先序遍历

void TreeInOrderByLoop(TreeNode* root);//通过循环实现树的中序遍历

void TreePostOrderByLoop(TreeNode* root);//通过循环后序遍历树

int IsCompleteTree(TreeNode* root);//判断一个树是否是完全二叉树

TreeNode*  TreeReBuild(TreeNodeType pre_order[],TreeNodeType in_order[],size_t size);//给先序和中序遍历结果，还原这个二叉树
