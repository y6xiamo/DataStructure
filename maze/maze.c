#include"seqstack.h"
#include<stdio.h>
#include<stdlib.h>

#define MAX_ROW 6
#define MAX_COL 6

typedef struct Maze
{
	int map[MAX_ROW][MAX_COL];
}Maze;

void MazeInit(Maze* maze)
{
	int map[MAX_ROW][MAX_COL] = {
		{0,1,0,0,0,0},
		{0,1,1,1,0,0},
		{0,1,0,1,0,0},
		{0,1,0,1,1,0},	
		{0,1,1,0,0,0},
		{0,0,1,0,0,0},
	};
	size_t i = 0;
	for( ;i < MAX_ROW;i++)
	{
		size_t j = 0;
		for( ;j < MAX_COL;j++)
		{
			maze->map[i][j] = map[i][j];
		}
	}
	return;
}

void MazePrint(Maze* maze)
{
	size_t i = 0;
	for( ;i < MAX_ROW;i++)
	{
		size_t j = 0;
		for( ;j < MAX_COL;j++)
		{
			printf("%2d ",maze->map[i][j]);
		}
		printf("\n");
	}
}
////////////////////////////////////////////////////
//Round1 使用递归的方式来解决迷宫问题（能否走出迷宫）
////////////////////////////////////////////////////

//判断pt这个点是否能落脚
//如果能落脚，返回1,不能落脚，返回0
int CanStay(Maze* maze,Point pt)
{
	//1.如果pt这个点在地图外，肯定不能落脚
	if(pt.ROW < 0||pt.COL < 0||pt.ROW >= MAX_ROW||pt.COL >= MAX_COL)
	{
		return 0;//不能落脚
	}
	//2.如果这个点在地图内，如果这个位置的值是1，就能落脚，如果是2或者0，就不能落脚
    int value = maze->map[pt.ROW][pt.COL];
	if(value == 1)
	{
		return 1;//能落脚，返回1
	}
	return 0;
}

//将当前能落脚的点赋值为2
void Mark(Maze* maze,Point cur)
{
	maze->map[cur.ROW][cur.COL] = 2;
}

//判断当前点是否是出口，是，返回1，否则，返回0
int IsExit(Maze* maze,Point cur,Point entry)
{
	(void)maze;
	//1.当前点如果是入口，肯定不是出口
	if(cur.ROW == entry.ROW && cur.COL == entry.COL)
	{
		return 0;
	}
	if(cur.ROW == 0||cur.COL == 0||cur.ROW == MAX_ROW-1||cur.COL == MAX_COL-1)
	{
		return 1;//当前点是边界点
	}
	return 0;
}
//每次走到下一个点，都会递归的调用下面这个函数
void _GetPath(Maze* maze,Point cur,Point entry)
{
	printf("cur:%d,%d\n",cur.ROW,cur.COL);
	if(maze == NULL)
	{
		return;//非法输入
	}
	//1.判定当前点，是否能落脚
	if(!CanStay(maze,cur))
	{
		return;//不能落脚
	}
	//2.如果能落脚，就给当前位置做一个标记
	Mark(maze,cur);
	//3.如果当前点是出口，说明找到了一跳出路，探测结束
	if(IsExit(maze,cur,entry))
	{
		//找到了出口点
		printf("找到了一条路径\n");
		return;
	}
	//4.如果当前点不是出口，寻找下一个落脚点,按顺时针探测四个相邻的点
	//  递归的调用函数自身，递归时，更新cur点（每次递归的时候，点都是下一次要走的点，这个点能不能走，交给递归函数作判断）
    Point up = cur;
	up.ROW -= 1;
	_GetPath(maze,up,entry);

	Point right = cur;
	right.COL += 1;
	_GetPath(maze,right,entry);

	Point down = cur;
	down.ROW += 1;
	_GetPath(maze,down,entry);

	Point left = cur;
	left.COL -= 1;
	_GetPath(maze,left,entry);

}
void GetPath(Maze* maze,Point entry)
{
	if(maze == NULL)
	{
		return;//非法输入
	}
	//使用下面的函数辅助我们完成递归
	_GetPath(maze,entry,entry);
}
//////////////////////////////////////////////////
//////////Round2 非递归版本实现迷宫求解//////////
/////////////////////////////////////////////////


//通过循环获得路径
void GetPathByLoop(Maze* maze,Point entry)
{
	//1.创建一个栈，并且初始化，这个栈保存走过的路径
	SeqStack stack;
	SeqStackInit(&stack);
	//2.判定入口能不能落脚，如果不能，说明参数非法
	if(!CanStay(maze,entry))
	{
		return;
	}
	//3.标记入口点，并且将入口点入栈
	Mark(maze,entry);
	SeqStackPush(&stack,entry);
	//4.进入循环，获取当前的栈顶元素（栈顶元素一定能落脚）
	while(1)
	{
		SeqStackType cur;
		int ret = SeqStackTop(&stack,&cur);
		if(ret == 0)
		{
			return;//栈为空说明回溯结束
		}
		//5.判定这个点是不是出口，是直接将函数返回
		if(IsExit(maze,cur,entry))
		{
			printf("找到了一条路径\n");
	      	return;
		}
     	//6.不是按照顺时针方向取相邻点，判断相邻点能否落脚，
    	//  如果能，标记并入栈，立刻进入下一次循环
        Point up = cur;
		up.ROW -= 1;
		if(CanStay(maze,up))
		{
			Mark(maze,up);
			SeqStackPush(&stack,up);
			continue;
		}

		Point right = cur;
		right.COL += 1;
		if(CanStay(maze,right))
		{
			Mark(maze,right);
			SeqStackPush(&stack,right);
			continue;
		}

		Point down = cur;
        down.ROW += 1;
		if(CanStay(maze,down))
		{
			Mark(maze,down);
			SeqStackPush(&stack,down);
			continue;
		}

		Point left = cur;
		left.COL -= 1;
		if(CanStay(maze,left))
		{
			Mark(maze,left);
			SeqStackPush(&stack,left);
			continue;
		}
	    //7.如果四个相邻点都不能落脚，就出栈当前点，相当于进行回溯
		SeqStackPop(&stack);       
	}
	return;
}
 
////////////////////////////////////////////////////
/////// Round3 如果迷宫有多路经，找出其中最短的路径////////
//////////////////////////////////////////////////

void MazeShortPathInit(Maze* maze)
{
	int map[MAX_ROW][MAX_COL] = {
		{0,1,0,0,0,0},
		{0,1,1,1,0,0},
		{0,1,0,1,0,0},
		{1,1,0,1,1,1},	
		{0,1,1,0,0,0},
		{0,0,1,0,0,0},
	};
	size_t i = 0;
	for( ;i < MAX_ROW;i++)
	{
		size_t j = 0;
		for( ;j < MAX_COL;j++)
		{
			maze->map[i][j] = map[i][j];
		}
	}
	return;
}

void _GetShortPath(Maze* maze,Point cur,Point entry,SeqStack* cur_path,SeqStack* short_path)
{
	//1.判断当前点是否能落脚
	if( !CanStay(maze,cur))
	{
		return;
	}
	//2.如果能落脚，标记当前点并且入栈到cur_path
	Mark(maze,cur);
	SeqStackPush(cur_path,cur);
	//3.判断当前点是否为出口
	if(IsExit(maze,cur,entry))
	{
	//  如果是出口，说明找到了一条路径，拿当前路径和short_path中的路径比较
	//  a)如果当前路径比short_path中路径短或者short_path为空，就用当前路径替换short_path
	//  b)如果当前路径没有short_path中路径短，尝试去找其他的路经（进行回溯），出栈cur_path的栈顶元素
		printf("找到了一条路径\n");
		if(cur_path->size < short_path->size || short_path->size == 0)
		{
			SeqStackAssgin(cur_path,short_path);
		}
		SeqStackPop(cur_path);
		return;
	}
	//4.如果当前点不是出口，尝试顺时针去探测其他四个方向
	Point up = cur;
	up.ROW -= 1;
	_GetShortPath(maze,up,entry,cur_path,short_path);
	
	Point right = cur;
	right.COL += 1;
	_GetShortPath(maze,right,entry,cur_path,short_path);
	
	Point down = cur;
	down.ROW += 1;
	_GetShortPath(maze,down,entry,cur_path,short_path);
	
	Point left = cur;
	left.COL -= 1;
	_GetShortPath(maze,left,entry,cur_path,short_path);
	//5.如果四个方向都递归的探测完了，就可以进行出栈(cur_path)，回溯到上一个点
	SeqStackPop(cur_path);
}
//遍历所有的路径，然后从其中找出一条最短路径
//实现递归版本
void GetShortPath(Maze* maze,Point entry)
{
	//保存着当前路径
	SeqStack cur_path;
	//保存最短路径
	SeqStack short_path;

	SeqStackInit(&cur_path);
	SeqStackInit(&short_path);
	_GetShortPath(maze,entry,entry,&cur_path,&short_path);
	//打印栈里面的内容（通常意义下，栈是不允许遍历的，但是这里仅仅用于调试）
	SeqStackPrintDebug(&short_path,"最短路径是：");
}

//////////////////////////////////////////////////////////////////////////////
///////  Round4 针对一个复杂（带环，多出口）的迷宫地图，找出其中的最短路径////
//////////////////////////////////////////////////////////////////////////////
//判断当前点是否能落脚
void MazeInitShortPathWithCycle(Maze* maze)
{
	int map[MAX_ROW][MAX_COL] = {
		{0,1,0,0,0,0},
		{0,1,1,1,0,0},
		{0,1,0,1,0,0},
		{1,1,0,1,1,1},	
		{0,1,1,1,0,0},
		{0,0,1,0,0,0},
	};
	size_t i = 0;
	for( ;i < MAX_ROW;i++)
	{
		size_t j = 0;
		for( ;j < MAX_COL;j++)
		{
			maze->map[i][j] = map[i][j];
		}
	}
	return;
}
int CanStayWithCycle(Maze* maze,Point cur,Point pre)
{
	//1.如果在地图外，不能落脚
	if(cur.ROW < 0 || cur.COL < 0 ||cur.ROW > MAX_ROW||cur.COL > MAX_COL)
	{
		return 0;
	}
	//2.如果是墙，不能落脚
	int cur_value = maze->map[cur.ROW][cur.COL];
	if(cur_value == 0)
	{
		return 0;
	}
	//3.如果当前点是1，可以直接落脚
	if(cur_value == 1)
	{
		return 1;
	}
	//3.判断是否已经走过，拿当前点和他的前一个点比较
	//pre 6, cur 5 不能落脚
	//pre 5, cur 5 不能落脚
	//pre 4, cur 5 不能落脚
	//pre 3, cur 5 可以落脚
	int pre_value = maze->map[pre.ROW][pre.COL];
	if(pre_value + 1 < cur_value)
	{
		return 1;
	}
	return 0;

}

void MarkWithCycle(Maze* maze,Point cur,Point pre)
{
//	if(maze == NULL)
//	{
//		return;
//	}
//   if(cur.ROW < 0 ||cur.ROW >= MAX_ROW ||cur.COL < 0 ||cur.COL >= MAX_COL)
//   {
// 	    return;
//   }
	if(pre.ROW == -1 && pre.COL == 0)
	{
	     maze->map[cur.ROW][cur.COL]  = 2;
		 return;
	}
	int pre_value = maze->map[pre.ROW][pre.COL];
	maze->map[cur.ROW][cur.COL]  = pre_value + 1;
}
void _GetShortPathWithCycle(Maze* maze,Point cur,Point pre,Point entry,SeqStack* cur_path,SeqStack* short_path)
{
   // printf("cur: (%d,%d)\n",cur.ROW,cur.COL);
	//1.判断当前点是否能落脚
	if(!CanStayWithCycle(maze,cur,pre))
	{
		return;
	}
	//2.如果能落脚，标记当前点并且入栈到cur_path
	MarkWithCycle(maze,cur,pre);
	SeqStackPush(cur_path,cur);
	//3.判断是否是出口
	if(IsExit(maze,cur,entry))
	{
        printf("找到了一条路径\n");
     	//  如果是出口,拿cur_path和short_path比较，将比较短的路径保存到short_path中
         if(cur_path->size < short_path->size || short_path->size == 0)     
		 {
			 printf("找到了一条比较短的路径\n");
			 SeqStackAssgin(cur_path,short_path);
		 }
		 //进行回溯，寻找另外的路径
		 SeqStackPop(cur_path);
		 return;
	}
	//4.如果不是出口，以当前点为基准，顺时针的探测四个方向
	Point up = cur;
	up.ROW -= 1;
	_GetShortPathWithCycle(maze,up,cur,entry,cur_path,short_path);
	
	Point right = cur;
	right.COL += 1;
	_GetShortPathWithCycle(maze,right,cur,entry,cur_path,short_path);
	
	Point down = cur;
	down.ROW += 1;
	_GetShortPathWithCycle(maze,down,cur,entry,cur_path,short_path);
	
	Point left = cur;
	left.COL -= 1;
	_GetShortPathWithCycle(maze,left,cur,entry,cur_path,short_path);
	//5.如果四个方向都递归的探测完了，就可以进行出栈(cur_path)，回溯到上一个点
	SeqStackPop(cur_path);
}
//实现一个递归版本的
void GetShortPathWithCycle(Maze* maze,Point entry)
{
	SeqStack cur_path;
	SeqStack short_path;
	SeqStackInit(&cur_path);
	SeqStackInit(&short_path);
    Point pre = {-1,0};
	_GetShortPathWithCycle(maze,entry,pre,entry,&cur_path,&short_path);
	SeqStackPrintDebug(&short_path,"最短路径为：");
}

/////////////////////////////////////////////////
/////////////////以下是测试代码//////////////////
/////////////////////////////////////////////////
#if 1
#include<stdio.h>
#define TEST_HEADER printf("\n====================%s===================\n",__FUNCTION__)

void TestInit()
{
	TEST_HEADER;
	Maze maze;
	MazeInit(&maze);
	MazePrint(&maze);
}

void Test1()
{

	TEST_HEADER;
	Maze maze;
	MazeInit(&maze);
	Point entry = {0,1};
	GetPath(&maze,entry);
	MazePrint(&maze);
}

void TestByLoop()
{
	TEST_HEADER;
	Maze maze;
	MazeInit(&maze);
	Point entry = {0,1};
	GetPathByLoop(&maze,entry);
	MazePrint(&maze);
}

void TestShortPath()
{

	TEST_HEADER;
	Maze maze;
	MazeShortPathInit(&maze);
	Point entry = {0,1};
	GetShortPath(&maze,entry);
	MazePrint(&maze);
}

void TestWithCycle()
{
	TEST_HEADER;
	Maze maze;
	MazeInitShortPathWithCycle(&maze);
	Point entry = {0,1};
	GetShortPathWithCycle(&maze,entry);
	MazePrint(&maze);
}
int main()
{
	TestInit();
	Test1();
	TestByLoop();
	TestShortPath();
	TestWithCycle();
	printf("\n");
	return 0;
}
#endif
