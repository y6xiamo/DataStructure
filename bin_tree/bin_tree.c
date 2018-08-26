#include"bin_tree.h"
#include"seqqueue.h"
#include"seqstack.h"
#include<stdio.h>
#include<stdlib.h>
void TreeInit(TreeNode** pRoot)
{
	if(pRoot == NULL)
	{
		return;//非法输入
	}
	(*pRoot) = NULL;
	
}

TreeNode* CreateTreeNode(TreeNodeType value)
{
	TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
	new_node->data = value;
	new_node->lchild = NULL;
	new_node->rchild = NULL;
	return new_node;
}

void DestroyTreeNode(TreeNode* node)
{
	free(node);
}

//前序遍历树
void TreePreOrder(TreeNode* root)
{
	if(root == NULL)
	{
		return;//空树
	}
	//先访问根节点
	printf("%c ",root->data);
	//然后递归的遍历左子树
	TreePreOrder(root->lchild);
	//最后递归的遍历右子树
	TreePreOrder(root->rchild);
	return;
}

//中序遍历树
void TreeInOrder(TreeNode* root)
{
	if(root == NULL)
	{
		return;//空树
	}
	//先递归的访问左子树
	TreeInOrder(root->lchild);
	//然后访问根节点
	printf("%c ",root->data);
	//最后递归的访问右子树
	TreeInOrder(root->rchild);
	return;
}

//后序遍历树
void TreePostOrder(TreeNode* root)
{
	if(root == NULL)
	{
		return;//空树
	}
	//先递归访问左子树
	TreePostOrder(root->lchild);
	//再递归的访问右子树
	TreePostOrder(root->rchild);
	//最后访问根节点
	printf("%c ",root->data);
	return;
}
//层序遍历，借助队列来实现
//循环的取队首元素，访问并出栈，然后将其左右子树入队列
//循环上述过程，直到队列为空，说明访问完了
void TreeLevelOrder(TreeNode* root)
{
	if(root == NULL)
	{
		return;//空树
	}
	SeqQueue queue;
	SeqQueueInit(&queue);
	SeqQueuePush(&queue,root);
	while(1)
	{
		SeqQueueType front;
		size_t ret = SeqQueueFront(&queue,&front);
		if(ret == 0)
		{
			break;//队列为空
		}
		printf("%c ",front->data);
		SeqQueuePop(&queue);
		if(front->lchild != NULL)
		{
		    SeqQueuePush(&queue,front->lchild);
		}
		if(front->rchild != NULL)
		{
		    SeqQueuePush(&queue,front->rchild);
		}
	}
	printf("\n");
	return;

}

TreeNode* _CreateTree(TreeNodeType data[],size_t size,size_t* index,TreeNodeType null_node)
{
	if(index == NULL)
	{
		return NULL;//非法输入
	}
	if(*index >= size)
	{
		return NULL;//指针越界
	}
	
	if(data[*index] == null_node)
	{
		return NULL;
	}
	//根据index指向的内容，创建一个节点
	TreeNode* root = CreateTreeNode(data[*index]);
	//先++index,然后递归构建新节点的左子树
	++(*index);
	root->lchild = _CreateTree(data,size,index,null_node);
	//再++index，然后递归的构建新节点的右子树·
    ++(*index);
	root->rchild = _CreateTree(data,size,index,null_node);
	return root;
}
//借用先序遍历的规则和用#表示一个空子树
TreeNode* CreateTree(TreeNodeType data[],size_t size,TreeNodeType null_node)
{
	//每次指向的元素
	size_t index = 0;
	//借助下面这个函数完成每次的递归调用
	return _CreateTree(data,size,&index,null_node);
}
TreeNode* CloneTree(TreeNode* root)
{
	if(root == NULL)
	{
		return NULL;//空树
	}
	//按照先序方法来遍历
	TreeNode* new_node = CreateTreeNode(root->data);
	new_node->lchild = CloneTree(root->lchild);
	new_node->rchild = CloneTree(root->rchild);
	return new_node;
}

void TreeDestroy(TreeNode* root)
{
	if(root == NULL)
	{
		return;//空树
	}
	//按照后序的顺序销毁树
	TreeDestroy(root->lchild);
	TreeDestroy(root->rchild);
	DestroyTreeNode(root);

}

/*size_t _TreeSize(TreeNode* root,size_t* size)
{
	if(size == NULL)
	{
		return 0;//非法输入
	}
	if(root == NULL)
	{
		return 0;//空树
	}
	size_t index = 0;
	TreePreOrder(root);
	if(data[*index] == )
    

}
size_t TreeSize(TreeNode* root)
{
	if(root == NULL)
	{
		return 0;//空树
	}

	size_t size = 0;
	return _TreeSize(root,&size);
}
*/
size_t TreeSize(TreeNode* root)
{
	if(root == NULL)
	{
		return 0;//空树
	}
	return 1+TreeSize(root->lchild)+TreeSize(root->rchild);
}

size_t TreeLeafSize(TreeNode* root)
{
	if(root == NULL)
	{
		return 0;//空树
	}
	if(root->lchild == NULL && root->rchild == NULL)
	{
		return 1;
	}
	return TreeLeafSize(root->lchild)+TreeLeafSize(root->rchild);
}

size_t TreeKLevelSize(TreeNode* root,size_t k)
{
	if(root == NULL || k < 1)
	{
		return 0;//空树
	}
	if(k == 1)
	{
		return 1;
	}
	return TreeKLevelSize(root->lchild,k-1)+TreeKLevelSize(root->rchild,k-1);
}

size_t TreeHeight(TreeNode* root)
{
	if(root == NULL)
	{
		return 0;//空树
	}
	if(root->lchild == NULL && root->rchild == NULL)
	{
		return 1;
	}
	size_t lheight = TreeHeight(root->lchild);
	size_t rheight = TreeHeight(root->rchild);
	return 1+(lheight > rheight ? lheight : rheight);
}

TreeNode* TreeFind(TreeNode* root,TreeNodeType to_find)
{
	if(root == NULL)
	{
		return NULL;
	}
	if(root->data == to_find)
	{
		return root;
	}
	TreeNode* lresult = TreeFind(root->lchild,to_find);
	TreeNode* rresult = TreeFind(root->rchild,to_find);
	return lresult != NULL ? lresult:rresult;

}

TreeNode* ParentTree(TreeNode* root,TreeNode* child)
{
	if(root == NULL || child == NULL)
	{
		return NULL;
	}
	if(root->lchild == child ||root->rchild == child)
	{
		return root;
	}
	TreeNode* lresult = ParentTree(root->lchild,child);
	TreeNode* rresult = ParentTree(root->rchild,child);
	return lresult != NULL ? lresult:rresult;
}

TreeNode* LChildNode(TreeNode* root,TreeNode* lchild)
{
	if(root == NULL)
	{
		return NULL;//空树
	}
	if(root == lchild)
	{
		return root->lchild;
	}
	return LChildNode(root->lchild,lchild);
}

TreeNode* RChildNode(TreeNode* root,TreeNode* rchild)
{
	if(root == NULL)
	{
		return NULL;//空树
	}
	if(root == rchild)
	{
		return root->rchild;
	}
	return RChildNode(root->rchild,rchild);
}
///////////////////////////////
////非递归的完成先序、中序、后序遍历

void TreePreOrderByLoop(TreeNode* root)
{
	if(root == NULL)
	{
		return;
	}
	//1.先把根节点入栈
	SeqStack stack;
	SeqStackInit(&stack);
	SeqStackPush(&stack,root);
	//2.循环的取栈顶元素,栈为空，说明循环结束
	TreeNode* cur;
	while(1)
	{
		int ret = SeqStackTop(&stack,&cur);
		if(ret == 0){
			break;
		}
		//a)取栈顶元素为当前元素；
		//b)出栈
		SeqStackPop(&stack);
		//c)访问当前元素
		printf("%c ",cur->data);
		//d)将当前点的右子树入栈
		if(cur->rchild != NULL)
		{
			SeqStackPush(&stack,cur->rchild);
		}
		//e)将当前点的左子树入栈
		if(cur->lchild != NULL)
		{
			SeqStackPush(&stack,cur->lchild);
		}
	}
	printf("\n");
	return;
}

void TreeInOrderByLoop(TreeNode* root)
{
	if(root == NULL)
	{
		return;//非法输入
	}
	SeqStack stack;
	SeqStackInit(&stack);
	//1.先将cur指向root 
	TreeNode* cur = root;
	//2.循环的判断cur是否为空,
	while(1){
	    while(cur != NULL)
		{
			//  如果不为空，入栈，然后让cur指向cur的lchild
			SeqStackPush(&stack,cur);
			cur = cur->lchild;
		}
		// 如果为空，取栈顶元素，访问出栈，cur指向cur的rchild
		TreeNode* top = NULL;
		int ret = SeqStackTop(&stack,&top);
		if(ret == 0)
		{
			return;//栈为空，遍历完成
		}
		printf("%c ",top->data);
		SeqStackPop(&stack);
		cur = top->rchild;
	}
}

void TreePostOrderByLoop(TreeNode* root)
{
	if(root == NULL)
	{
		return;//非法输入
	}
	SeqStack stack;
	SeqStackInit(&stack);
	//1.先让cur指向root
	TreeNode* cur = root;
	//pre保存上一个访问过的元素
	TreeNode* pre = NULL;
	//2.循环的判断cur是否为空
	while(1){
		while(cur != NULL)
		{
			//3.如果不为空，压栈
			SeqStackPush(&stack,cur);
			//让cur指向cur的左孩子结点
			pre = cur;
			cur = cur->lchild;
		}
		//4.如果为空，循环取栈顶元素，对栈顶元素进行判定，
		TreeNode* top;
		int ret = SeqStackTop(&stack,&top);
		if(ret == 0)
		{
			//栈为空，说明遍历完成
			return;
		}
		//  a)如果栈顶元素的右子树访问过了,和访问的上一个元素是同一个
		//  b)或者栈顶元素没有右子树
		//  就访问栈顶元素，然后出栈
		if(top->rchild == NULL || top->rchild == pre)
		{
			printf("%c ",top->data);
			SeqStackPop(&stack);
			pre = top;
		}
		else
		{
			//5.如果不满足以上条件，就让cur指向栈顶元素的右子树，重复循环
			cur = top->rchild;
		}
	}
	return;
}

void Swap(TreeNode** a,TreeNode** b)
{
	TreeNode* tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}
//二叉树的镜像将以前访问某个节点的动作变成了交换其左右子树的位置
void TreeMirror(TreeNode* root)
{
	if(root == NULL)
	{
		return;
	}
	Swap(&root->lchild,&root->rchild);
	TreeMirror(root->lchild);
	TreeMirror(root->rchild);
}

//借助层序实现非递归版本的镜像
void TreeMirrorByLoop(TreeNode* root)
{
	if(root == NULL)
	{
		return;//空树
	}
	SeqQueue queue;
	SeqQueueInit(&queue);
	SeqQueuePush(&queue,root);
	//循环的取队首元素
	TreeNode* front = NULL;
	while(SeqQueueFront(&queue,&front))
	{
		//printf("ret = %d",ret);
		//交换其左右子树的位置
		Swap(&front->lchild,&front->rchild);
		SeqQueuePop(&queue);
		if(front->lchild != NULL)
		{
			SeqQueuePush(&queue,front->lchild);
		}
		if(front->rchild != NULL)
		{
			SeqQueuePush(&queue,front->rchild);
		}
		//    return;
	}
}

int IsCompleteTree(TreeNode* root)
{
	if(root == NULL)
	{
		return 0;
	}
	SeqQueue queue;
	SeqQueueInit(&queue);
	SeqQueuePush(&queue,root);
	//两个阶段分别进行判定
	
	int if_start_two_step_flag = 0;//进入第二阶段的标志位
	TreeNode* cur = NULL;
	while(SeqQueueFront(&queue,&cur))
	{
		SeqQueuePop(&queue);
		//首先判断在哪个阶段
		if(if_start_two_step_flag == 0)
		{
			//阶段一
			if(cur->lchild != NULL && cur->rchild != NULL)
			{
				//当前节点同时具备左右子树
				SeqQueuePush(&queue,cur->lchild);
		        SeqQueuePush(&queue,cur->rchild);
			}
			else if(cur->lchild != NULL && cur->rchild == NULL)
			{
				// 当前节点只有左子树，没有右子树
				if_start_two_step_flag = 1;
				//进入第二阶段
			}
			else if(cur->lchild == NULL && cur->rchild != NULL)
			{
				//当前节点只有右子树，没有左子树
				return 0;
				//直接退出
			}
			else
			{
				//没有左右子树，进入第二阶段
				if_start_two_step_flag = 1;
			}
		}
		else
		{
			//进入第二阶段
			if(cur->lchild == NULL && cur->rchild == NULL)
				;
			else
			{
				return 0;
			}
		}
	}
	//循环结束，所有节点都判定过了，此时又没有return 0的情况发生
	return 1;
	
}

size_t Find(TreeNodeType to_find,TreeNodeType array[],size_t *left,size_t *right)
{
	size_t i = *left ;
	for( ;i < *right;i++)
	{
		if(array[i] == to_find)
		{
			return i;
		}
	}
	return (size_t)0;
}
TreeNode* _TreeReBuild(TreeNodeType pre_order[],size_t size,size_t* pre_order_index,TreeNodeType in_order[],size_t* in_order_left,size_t* in_order_right)
{
	if(pre_order_index == NULL)
	{
		return NULL;//非法输入
	}
	if(*pre_order_index >= size)
	{
		return NULL;//遍历完了
	}
	if(*in_order_left >= *in_order_right)
	{
		return NULL;//无效区间
	}
	//先拿当前点，即先序遍历的第一个值创建一个节点
	//此时这个节点就是根节点
	TreeNode* new_node = CreateTreeNode(pre_order[*pre_order_index]);
	//查找一下当前节点在中序遍历中的位置
	size_t cur_root_in_order_index = Find(new_node->data,in_order,in_order_left,in_order_right);
	++(*pre_order_index);
	new_node->lchild = _TreeReBuild(pre_order,size,pre_order_index,in_order,in_order_left,&cur_root_in_order_index);
	++cur_root_in_order_index;
	new_node->rchild = _TreeReBuild(pre_order,size,pre_order_index,in_order,&cur_root_in_order_index,in_order_right);
	return new_node;

}
TreeNode* TreeReBuild(TreeNodeType pre_order[],TreeNodeType in_order[],size_t size)
{
	size_t pre_order_index = 0;//定义一个指向pre_order的指针
	//区间为左闭右开[in_order_left,in_order_right)
	size_t in_order_left = 0;
	size_t in_order_right = size;
	return _TreeReBuild(pre_order,size,&pre_order_index,in_order,&in_order_left,&in_order_right);

}
///////////////////////////////////////////////
////////////////以下是测试代码////////////////
/////////////////////////////////////////////
#include<stdio.h>
//#ifdef
#define TEST_HEADER printf("\n====================%s==================\n",__FUNCTION__)
void TestInit()
{
	TEST_HEADER;
	TreeNode* root;
	TreeInit(&root);
	printf("root expected NULL,actual %p\n",root);
}

void TestPreOrder()
{
	TEST_HEADER;
	printf("[先序遍历树的节点]\n");
	TreeNode* root;
	TreeInit(&root);
	root = CreateTreeNode('A');
	root->lchild = CreateTreeNode('B');
	root->rchild = CreateTreeNode('C');
	root->lchild->lchild = CreateTreeNode('D');
	root->lchild->rchild = CreateTreeNode('E');
	root->lchild->rchild->lchild = CreateTreeNode('G');
	root->rchild->rchild = CreateTreeNode('F');
	TreePreOrder(root);
}

void TestInOrder()
{
	TEST_HEADER;
	printf("[中序遍历树的节点]\n");
	TreeNode* root;
	TreeInit(&root);
	root = CreateTreeNode('A');
	root->lchild = CreateTreeNode('B');
	root->rchild = CreateTreeNode('C');
	root->lchild->lchild = CreateTreeNode('D');
	root->lchild->rchild = CreateTreeNode('E');
	root->lchild->rchild->lchild = CreateTreeNode('G');
	root->rchild->rchild = CreateTreeNode('F');
	TreeInOrder(root);
}

void TestPostOrder()
{
	TEST_HEADER;
	printf("[后序遍历树的节点]\n");
	TreeNode* root;
	TreeInit(&root);
	root = CreateTreeNode('A');
	root->lchild = CreateTreeNode('B');
	root->rchild = CreateTreeNode('C');
	root->lchild->lchild = CreateTreeNode('D');
	root->lchild->rchild = CreateTreeNode('E');
	root->lchild->rchild->lchild = CreateTreeNode('G');
	root->rchild->rchild = CreateTreeNode('F');
	TreePostOrder(root);
}

void TestLevelOrder()
{
	TEST_HEADER;
	printf("[层序遍历树的节点]\n");
	TreeNode* root;
	TreeInit(&root);
	root = CreateTreeNode('A');
	root->lchild = CreateTreeNode('B');
	root->rchild = CreateTreeNode('C');
	root->lchild->lchild = CreateTreeNode('D');
	root->lchild->rchild = CreateTreeNode('E');
	root->lchild->rchild->lchild = CreateTreeNode('G');
	root->rchild->rchild = CreateTreeNode('F');
	TreeLevelOrder(root);
}
void TestCreate()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	size_t size = sizeof(data)/sizeof(data[0])-1;
	TreeNode* root = CreateTree(data,size,'#');
	printf("\n[先序遍历树]\n");
	TreePreOrder(root);
	printf("\n[中序遍历树]\n");
	TreeInOrder(root);
	printf("\n[后序遍历树]\n");
	TreePostOrder(root);
	printf("\n[层序遍历树]\n");
	TreeLevelOrder(root);
	printf("\n");
}

void TestClone()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	size_t size = sizeof(data)/sizeof(data[0])-1;
	TreeNode* new_node = CreateTree(data,size,'#');
	TreeNode* root = CloneTree(new_node);
	printf("\n[先序遍历树]\n");
	TreePreOrder(root);
	printf("\n[中序遍历树]\n");
	TreeInOrder(root);
	printf("\n[后序遍历树]\n");
	TreePostOrder(root);
	printf("\n[层序遍历树]\n");
	TreeLevelOrder(root);
	printf("\n");
}

void TestSize()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	size_t size =TreeSize(root);
	printf("size expected 7,actual %d\n",size);
}

void TestLeafSize()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	size_t size =TreeLeafSize(root);
}

void TestKLevelSize()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	size_t k = 2;
	size_t size =TreeKLevelSize(root,k);
	printf("size expected 2,actual %d\n",size);
}
void TestHeight()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	size_t size =TreeHeight(root);
	printf("size expected 4,actual %d\n",size);
}

void TestFind()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	TreeNode* find_node = TreeFind(root,'E');
	printf("find_bode expected %p,actual %p",root->lchild->rchild,find_node);
}

void TestParent()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	TreeNode* parent_node = ParentTree(root,root->lchild->rchild);
	printf("parent_bode expected %p,actual %p",root->lchild,parent_node);
}

void TestLChild()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	TreeNode* lchild_node = LChildNode(root,root->lchild);
	printf("lchild_node_bode expected %c,actual %c",root->lchild->lchild->data,lchild_node->data);
}
void TestRChild()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	TreeNode* rchild_node = RChildNode(root,root->rchild);
	printf("rchild_node expected %c,actual %c",root->rchild->rchild->data,rchild_node->data);
}

void TestPreOrderByLoop()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	printf("[先序遍历树]\n");
	TreePreOrderByLoop(root);
}

void TestInOrderByLoop()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	printf("[中序遍历树]\n");
	TreeInOrderByLoop(root);
}

void TestPostOrderByLoop()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	printf("[后序遍历树]\n");
	TreePostOrderByLoop(root);
}
//
void TestMirror()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');

	TreeMirror(root);
	printf("\n[先序遍历树]\n");
	TreePreOrder(root);
	printf("\n[中序遍历树]\n");
	TreeInOrder(root);
	printf("\n[后序遍历树]\n");
	TreePostOrder(root);
}

void TestIsCompleteTree()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');
	int ret = IsCompleteTree(root);
	printf("ret expected 0,actual is %d\n",ret);

}
void TestMirrorByLoop()
{
	TEST_HEADER;
	TreeNodeType data[]= "ABD##EG###C#F##";
	TreeNode* root = CreateTree(data,sizeof(data)/sizeof(data[0])-1,'#');

	TreeMirrorByLoop(root);
	printf("\n[先序遍历树]\n");
	TreePreOrder(root);
	printf("\n[中序遍历树]\n");
	TreeInOrder(root);
	printf("\n[后序遍历树]\n");
	TreePostOrder(root);
}

void TestTreeReBuild()
{
	TEST_HEADER;
	TreeNodeType pre_order[] = "ABDEGCF";
	TreeNodeType in_order[] = "DBGEACF";
	TreeNode* root = TreeReBuild(pre_order,in_order,sizeof(pre_order)/sizeof(pre_order[0])-1);
	printf("\n[先序遍历树]\n");
	TreePreOrder(root);
	printf("\n[中序遍历树]\n");
	TreeInOrder(root);
	printf("\n[后序遍历树]\n");
	TreePostOrder(root);
}

int main()
{
	TestInit();
	TestPreOrder();
	TestInOrder();
	TestPostOrder();
	TestLevelOrder();
	TestCreate();
	TestClone();
	TestSize();
	TestLeafSize();
	TestKLevelSize();
	TestHeight();
	TestFind();
	TestParent();
	TestLChild();
	TestRChild();
	TestPreOrderByLoop();
	TestInOrderByLoop();
	TestPostOrderByLoop();
	TestMirror();
	TestMirrorByLoop();
	TestIsCompleteTree();
	TestTreeReBuild();
	printf("\n");
	return 0;
}
//#endif
