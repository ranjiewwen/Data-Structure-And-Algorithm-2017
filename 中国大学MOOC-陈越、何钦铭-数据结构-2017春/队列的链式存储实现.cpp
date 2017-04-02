
/*!
 * \file 队列的链式存储实现.cpp
 *
 * \author ranjiewen
 * \date 2017/03/19 15:18
 *
 * 
 */
#include<stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct Node *PtrToNode;

struct Node { /* 队列中的结点 */
	ElementType Data;
	PtrToNode Next;
};
typedef PtrToNode Position;

struct QNode {
	Position Front, Rear;  /* 队列的头、尾指针 */
	int MaxSize;           /* 队列最大容量 */
};
typedef struct QNode *Queue;

bool IsEmpty(Queue Q)
{
	return (Q->Front->Next == NULL);
}

Queue CreateListQueque()  //带头结点的操作
{
	Queue Q;
	Node *p;
	p = (PtrToNode)malloc(sizeof(struct Node)); //开辟新节点
	p->Next = NULL;

	Q = (Queue)malloc(sizeof(struct QNode));
	Q->Front = Q->Rear = p;
	return Q;
}

bool InsertQ(Queue Q, ElementType x)  
{
	Node *p;
	p = (Node*)malloc(sizeof(struct Node));
	if (!p)
	{
		return -1;
	}
	p->Data = x;
	p->Next = NULL;

	Q->Rear->Next = p;
	Q->Rear = p;
	return true;
}

ElementType DeleteQ(Queue Q) //带头结点的链式出队列操作
{
	Position FrontCell;
	ElementType FrontElem;

	if (IsEmpty(Q)) {
		printf("队列空");
		return NULL;
	}
	else {
		FrontCell = Q->Front->Next;
		if (Q->Front->Next == Q->Rear) /* 若队列只有一个元素 */
			Q->Front = Q->Rear = NULL; /* 删除后队列置为空 */
		else
			Q->Front->Next = Q->Front->Next->Next;
		FrontElem = FrontCell->Data;

		free(FrontCell);  /* 释放被删除结点空间  */
		return  FrontElem;
	}
}

void Destroy_Queque(Queue Q)
{
	while (Q->Front!=NULL)
	{
		Q->Rear = Q->Front->Next;
		free(Q->Front);
		Q->Front = Q->Rear;
	}
}

int main()
{
	Queue Q;
	Q = CreateListQueque();

	for (int i = 9; i > 0;i--)
	{
		InsertQ(Q, i);
	}

	Position temp = Q->Front->Next;
	while (temp != Q->Rear->Next)
	{
		printf("%d ", temp->Data);
		temp = temp->Next;
	}
	printf("\n");
	DeleteQ(Q);
	DeleteQ(Q);

	while (Q->Front->Next != Q->Rear->Next)
	{
		printf("%d ", Q->Front->Next->Data);
		Q->Front->Next = Q->Front->Next->Next;
	}
	printf("\n");
	return 0;
}