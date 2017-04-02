
/*!
 * \file 队列的顺序存储实现.cpp
 *
 * \author ranjiewen
 * \date 2017/03/19 14:30
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef int Position;
typedef int ElementType;
#define  MAXSIZE 10
struct QNode 
{
	ElementType *Data;
	Position front, rear;
	int  MaxSize;
};

typedef struct QNode *Queque;

Queque CreateQueqe(int maxsize)
{
	Queque Q = (Queque)malloc(sizeof(struct QNode));
	Q->Data = (ElementType *)malloc(sizeof(ElementType)*maxsize);
	Q->front = Q->rear = 0;
	Q->MaxSize = maxsize;

	return Q;
}

bool IsFull(Queque Q)
{
	return (Q->rear + 1) % Q->MaxSize == Q->front;
}

bool AddQ(Queque Q,ElementType x)
{
	if (IsFull(Q))
	{
		printf("队列满！");
		return false;
	}
	else
	{	
		Q->Data[Q->rear] = x;
		Q->rear = (Q->rear + 1) % Q->MaxSize;
	}
}

bool IsEmpty(Queque Q)
{
	return Q->rear == Q->front;
}

ElementType Delete(Queque Q)
{
	ElementType ret = 0;
	if (IsEmpty(Q))
	{
		printf("队列空！");
		return NULL;
	}
	else
	{
		ret = Q->Data[Q->front];
		Q->front = (Q->front + 1) % Q->MaxSize;
		return ret ;
	}
}

int main()
{
	Queque Q = CreateQueqe(MAXSIZE);	

	for (int i = 9; i > 0;i--)
	{
		AddQ(Q, i);
	}

	int i = (Q->front);
	while ( i %Q->MaxSize!=Q->rear)
	{
		printf("%d ", Q->Data[i]);
		i = (i + 1) % Q->MaxSize;
	}
	printf("\n");

	Delete(Q);
	Delete(Q);

	i = (Q->front);
	while (i %Q->MaxSize != Q->rear)
	{
		printf("%d ", Q->Data[i]);
		i = (i + 1) % Q->MaxSize;
	}
	printf("\n");

	return 0;
}