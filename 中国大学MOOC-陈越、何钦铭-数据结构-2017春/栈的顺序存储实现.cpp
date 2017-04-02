/*!
 * \file 栈的顺序存储实现.cpp
 *
 * \author ranjiewen
 * \date 2017/03/17 11:13
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef int Position;
typedef int ElemType;
#define  ERROR NULL
#define  MAXSIVE 100

struct SNode
{
	ElemType *Data; /*存储元素的数组，动态分配内存*/
	Position Top; /*栈顶元素数组下标*/
	int MaxSize; // 堆栈最大容量
};

typedef struct SNode* Stack;

Stack CreateStack(int MaxSize)
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElemType*)malloc(MaxSize*sizeof(ElemType));
	S->Top = -1; //顺序存储结构时，表示空
	S->MaxSize = MaxSize;
	return S;
}

bool IsFull(Stack S)
{
	return (S->Top == S->MaxSize - 1);
}

bool Push(Stack S, ElemType x)
{
	if (IsFull(S))
	{
		printf("堆栈满.\n");
		return false;
	}
	else
	{
		S->Data[++(S->Top)] = x;
		return true;
	}
}

bool IsEmpty(Stack S)
{
	return (S->Top == -1);
}

ElemType Pop(Stack S)
{
	if (IsEmpty(S))
	{
		printf("堆栈为空。\n");
		return ERROR;
	}
	else
	{
		return S->Data[(S->Top)--];
	}
}

int main()
{
	struct SNode *S = CreateStack(MAXSIVE);
	for (int i = 9; i >= 0;i--)
	{
		Push(S,i);
	}
	for (int i = 0; i < S->Top;i++)
	{
		printf("%d ", S->Data[i]);
	}
	printf("\n");
	Pop(S);
	Pop(S);
	for (int i = 0; i < S->Top; i++)
	{
		printf("%d ", S->Data[i]);
	}
	printf("\n");
	return 0;
}