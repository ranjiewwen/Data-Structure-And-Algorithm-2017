
/*!
 * \file 线性表的顺序存储实现.cpp
 *
 * \author ranjiewen
 * \date 三月 2017
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef int Position;
typedef struct LNode *List;
#define  MAXSIVE 100

struct LNode
{
	ElemType Data[MAXSIVE];
	Position Last;  //数组的下标
};

/*初始化*/
List MakeEmpty()
{
	List L; 
	L = (List)malloc(sizeof(struct LNode));
	L->Last = -1; //初始元素位置为0
	return L;
}

#define ERROR -1
Position Find(List L, ElemType x)
{
	Position i = 0;
	while (i<=L->Last&&L->Data[i]!=x)
	{
		i++;
	}
	if (i>L->Last)
	{
		return ERROR;  //如果没有找到，返回错误信息
	}
	else
	{
		return i; //找到了返回存储位置
	}
}

/*插入*/
bool Insert(List L, ElemType X, Position P)
{ /* 在L的指定位置P前插入一个新元素X */
	Position i;

	if (L->Last == MAXSIVE - 1) {
		/* 表空间已满，不能插入 */
		printf("表满");
		return false;
	}
	if (P<0 || P>L->Last + 1) { /* 检查插入位置的合法性 */
		printf("位置不合法");
		return false;
	}
	for (i = L->Last; i >= P; i--)
		L->Data[i + 1] = L->Data[i]; /* 将位置P及以后的元素顺序向后移动 */
	L->Data[P] = X;  /* 新元素插入 */
	L->Last++;       /* Last仍指向最后元素 */
	return true;
}

/* 删除 */
bool Delete(List L, Position P)
{ /* 从L中删除指定位置P的元素 */
	Position i;

	if (P<0 || P>L->Last) { /* 检查空表及删除位置的合法性 */
		printf("位置%d不存在元素", P);
		return false;
	}
	for (i = P + 1; i <= L->Last; i++)
		L->Data[i - 1] = L->Data[i]; /* 将位置P+1及以后的元素顺序向前移动 */
	L->Last--; /* Last仍指向最后元素 */
	return true;
}

//表长操作顺序存储即数组大小

int main()
{
	//List L = MakeEmpty(); //正确的初始化

	//List L = NULL;//不合理的初始化

	struct LNode list_; //合理的初始化
	list_.Last = -1; //必须赋值；
	for (int i = 0; i<4;i++)
	{
		list_.Data[i] = 10 + i;
		list_.Last++;
	}
	List L = &list_; 

	for (int i = 9; i > 0; i--)
	{
		Insert(L, i, 9 - i);
	}

	for (int i = 0; i <= L->Last;i++)
	{
		printf("%d ", L->Data[i]);
	}
	printf("\n");
	return 0;
}