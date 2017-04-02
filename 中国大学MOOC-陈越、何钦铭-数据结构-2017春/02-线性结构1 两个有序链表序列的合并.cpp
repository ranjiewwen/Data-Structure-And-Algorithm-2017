/*!
 * \file 02-线性结构1 两个有序链表序列的合并.cpp
 *
 * \author ranjiewen
 * \date 2017/03/12 20:23
 *
 *
 */

#include<stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
	ElementType Data;
	PtrToNode Next;
}Node;

typedef PtrToNode List;  //定义单链表类型

List Read()
{
	printf("请输入一个链表的元素个数：\n");
	int n = 0;
	scanf("%d", &n);

	List pHead = (List)malloc(sizeof(Node));
	List pCur = pHead;
	pCur->Next = NULL;
	if (pHead == NULL)
	{
		printf("pHead malloc faied!");
		exit(-1);
	}

	printf("请依次输入元素：\n");
	int i, data = 0;
	for (i = 0; i < n; i++)
	{
		scanf("%d", &data);
		List pNode = (List)malloc(sizeof(Node));
		pNode->Data = data;
		pNode->Next = NULL;
		pCur->Next = pNode;
		//pCur++; 错误写法
		pCur = pNode; //移动当前节点到下一位置
	}
	return pHead;
}
void Print(List L) //空链表时输出null
{
	List pCur = L->Next;
	if (pCur == NULL)
	{
		printf("NULL");
	}
	while (pCur != NULL)//
	{
		printf("%d ", pCur->Data);
		pCur = pCur->Next;
	}
}

//L1和L2是给定的带头结点的单链表，其结点存储的数据是递增有序的；函数Merge要将L1和L2合并为一个非递减的整数序列。应直接使用原序列中的结点，返回归并后的链表头指针。
List Merge(List L1, List L2);
List Merge1(List L1, List L2);
List Merge_(List L1, List L2);

int main()
{
	List L1, L2, L;
	L1 = Read();
	L2 = Read();
	L = Merge(L1, L2);
	Print(L);
	printf("\n");
	L1->Next = NULL;
	L2->Next = NULL;
	Print(L1);
	printf("\n");
	Print(L2);
	printf("\n");
	return 0;
}

List Merge1(List L1, List L2){
	if (L1->Next == NULL){
		List temp, L;
		L = (List)malloc(sizeof(struct Node));
		temp = L2;
		L2 = L2->Next;
		L->Next = L2;
		while (L2){
			temp->Next = L2->Next;
			L2 = L2->Next;
		}
		return L;
	}
	else if (L2->Next == NULL){
		List temp, L;
		L = (List)malloc(sizeof(struct Node));
		temp = L1;
		L1 = L1->Next;
		L->Next = L1;
		while (L1){
			temp->Next = L1->Next;
			L1 = L1->Next;
		}
		return L;
	}
	else{
		List LL = (List)malloc(sizeof(struct Node));
		List LLL = LL;
		List temp1, temp2;
		temp1 = L1; 
		temp2 = L2;
		L1 = L1->Next; 
		L2 = L2->Next;
		while (L1 && L2){
			if (L1->Data < L2->Data){
				LL->Next = L1;
				LL = LL->Next;
				temp1->Next = L1->Next;
				L1 = L1->Next;
			}
			else{
				LL->Next = L2;
				LL = LL->Next;
				temp2->Next = L2->Next;
				L2 = L2->Next;
			}
		}
		while (L1){
			LL->Next = L1;
			LL = LL->Next;
			temp1->Next = L1->Next;
			L1 = L1->Next;
		}
		while (L2){
			LL->Next = L2;
			LL = LL->Next;
			temp2->Next = L2->Next;
			L2 = L2->Next;
		}
		return LLL;
	}
}
List Merge(List L1, List L2)
{
	List L;
	if (L1->Next == NULL)
	{
		L = L2;
		return L;
	}
	else if (L2->Next == NULL)
	{
		L = L1;
		return L;
	}

	List pCur1 = L1->Next;
	List pCur2 = L2->Next;

	while (pCur1 != NULL&&pCur2 != NULL) //
	{
		List pTemp, p1 = L1;
		while (pCur1->Data < pCur2->Data)
		{
			p1 = pCur1;   //记录当前结点之前的结点
			pCur1 = pCur1->Next;
			if (pCur1 == NULL || pCur2 == NULL)
			{
				break;
			}
		}
		pTemp = pCur2;
		pCur2 = pCur2->Next;
		pTemp->Next = pCur1;  //pTemp要插入pCur1之前
		p1->Next = pTemp;

		pCur1 = L1->Next; //回到链表头             
	}

	if (pCur2 != NULL)
	{
		while (pCur1->Next)
		{
			pCur1 = pCur1->Next;
		}
		pCur1->Next = pCur2;
	}
	L = L1;
	return L;
}

List Merge_(List L1, List L2)
{
	List L = NULL;
	if (L1->Next == NULL)
	{
		return L2;
	}
	if (L2->Next == NULL)
	{
		return L1;
	}
	List pCur1 = L1->Next;
	List pCur2 = L2->Next;
	if (pCur1->Data < pCur2->Data)
	{
		L = pCur1;
		pCur1 = pCur1->Next;
	}
	else
	{
		L = pCur2;
		pCur2 = pCur2->Next;
	}

	List temp = L;
	while (pCur1&&pCur2)
	{
		if (pCur1->Data < pCur2->Data)
		{
			temp->Next = pCur1;
			pCur1 = pCur1->Next;
		}
		else
		{
			temp->Next = pCur2;
			pCur2 = pCur2->Next;
		}
		temp = temp->Next;
	}
	if (pCur1)
	{
		temp->Next = pCur1;
	}
	if (pCur2)
	{
		temp->Next = pCur2;
	}
	return L;
}



#include<stdio.h>
#include<stdlib.h>
typedef struct node *ptrNode;
typedef ptrNode LinkList;
//头结点
typedef ptrNode Position;
//中间节点
typedef int ElementType;
struct node
{
	ElementType Element;
	Position next;
};
int IsEmpty(LinkList L)
{
	return L->next == NULL;
}
LinkList creatList(void)
{
	LinkList head, r, p;
	int x;
	head = (struct node*)malloc(sizeof(struct node));   //生成新结点
	r = head;
	scanf("%d", &x);
	while (x != -1)
	{
		p = (struct node*)malloc(sizeof(struct node));
		p->Element = x;
		r->next = p;
		r = p;
		scanf("%d", &x);
	}
	r->next = NULL;
	return head;
}
LinkList mergeList(LinkList a, LinkList b)
{
	Position ha, hb, hc;
	LinkList c, r, p;
	ha = a->next;
	hb = b->next;
	c = (struct node*)malloc(sizeof(struct node));
	r = c;
	while ((ha != NULL) && (hb != NULL))
	{
		p = (struct node*)malloc(sizeof(struct node));
		if (ha->Element <= hb->Element)
		{
			p->Element = ha->Element;
			ha = ha->next;
		}
		else{
			p->Element = hb->Element;
			hb = hb->next;
		}		
		r->next = p;
		r = p;
	}
	if (ha == NULL){
		while (hb != NULL)
		{
			p = (struct node*)malloc(sizeof(struct node));
			p->Element = hb->Element;
			hb = hb->next;
			r->next = p;
			r = p;
		}
	}
	if (hb == NULL){
		while (ha != NULL){
			p = (struct node*)malloc(sizeof(struct node));
			p->Element = ha->Element;
			ha = ha->next;
			r->next = p;
			r = p;
		}
	}
	r->next = NULL;
	return c;
}
void printList(LinkList L){
	LinkList hc;
	int flag = 0;
	hc = L->next;
	if (hc == NULL)
		printf("NULL");
	while (hc != NULL){
		if (flag)
			printf(" ");
		else
			flag = 1;
		printf("%d", hc->Element);
		hc = hc->next;
	}
}

int main(void){
	LinkList L1, L2, L3;
	L1 = creatList();
	L2 = creatList();
	L3 = mergeList(L1, L2);
	printList(L3);
	return 0;
}