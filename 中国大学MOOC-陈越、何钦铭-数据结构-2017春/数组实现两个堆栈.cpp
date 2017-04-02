/*****************************************************
* \file 数组实现两个堆栈.cpp
* \date 2017/03/17 23:02
* \author ranjiewen
* \contact: ranjiewen@outlook.com 
* \问题描述：
用一个数组实现两个堆栈，要求最大利用数组空间，使数组只要有空间
入栈操作就可以成功。
* \问题分析：
两个栈分别从数组的两头开始向中间生长，当两个栈的栈顶指针相遇时，表示两个栈都满了

*****************************************************/

#include<stdio.h>
#include <stdlib.h>

#define MAXSIVE 20
typedef int ElementType;
typedef struct DStack *DStack_;
struct DStack
{
	ElementType Data[MAXSIVE];
	int top1;  //栈1的栈顶指针
	int top2;  //栈2的栈顶指针
};

void Push(struct DStack *ptrs, ElementType item, int Tag)
{
	/*Tag作为区分两个堆栈的标志，取值为1/2*/
	if (ptrs->top2-ptrs->top1==1)
	{
		printf("栈满！"); return;
	}
	if (Tag==1)
	{
		ptrs->Data[++(ptrs->top1)] = item;
	}
	else
	{
		ptrs->Data[--(ptrs->top2)] = item;
	}
}

ElementType Pop(struct DStack *ptrs,int Tag)
{
	if (Tag==1)
	{
		if (ptrs->top1==-1)
		{
			printf("栈1空！");
			return NULL;
		}
		else
		{
			return ptrs->Data[(ptrs->top1)--];
		}
	}
	else
	{
		if (ptrs->top2==MAXSIVE)
		{
			printf("栈2空！");
			return NULL;
		}
		else
		{
			return ptrs->Data[(ptrs->top2)++];
		}
	}
}

int main()
{
	//struct DStack *S=(DStack_)malloc(sizeof(struct DStack));
	struct DStack stack;
	DStack_ S = &stack;
	S->top1 = -1;
	S->top2 = MAXSIVE;

	for (int i = 0; i < 8;i++)
	{
		Push(S, i, 1);
		Push(S, 8 - i, 2);
	}

	for (int i = 0; i <= S->top1;i++)
	{
		printf("%d ",S->Data[i]);
	}
	printf("\n");
	for (int i = MAXSIVE-1; i >= S->top2; i--)
	{
		printf("%d ", S->Data[i]);
	}
	printf("\n");
	return 0;
}
