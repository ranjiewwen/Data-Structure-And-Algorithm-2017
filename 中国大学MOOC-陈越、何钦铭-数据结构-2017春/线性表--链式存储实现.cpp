
/*!
 * \file 线性表的链式存储实现.cpp
 *
 * \author ranjiewen
 * \date 三月 2017
 *
 * 
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode *PtrToNode;
typedef int ElemType;
struct LNode
{
	ElemType Data;
	PtrToNode Next;
};

typedef PtrToNode Position;
typedef PtrToNode List;

#define  ERROR NULL

int Length(List ptrL)
{
	List p = ptrL;
	int j = 0;
	while (p)
	{
		p = p->Next;
		j++;
	}
	return j;
}

/*查找*/
Position Find(List L, ElemType x)  //按值查找
{
	Position p = L;/*p指向L的第1个结点*/
	while (p&&p->Data!=x)
	{
		p = p->Next;
	}
	if (p)
	{
		return p;
	}
	else
	{
		return ERROR;
	}
}

List FindKth(int K, List ptrL)//按序号查找
{
	List p = ptrL;
	int i = 1;
	while (p!=NULL&&i<K)
	{
		p = p->Next;
		i++;
	}
	if (i==K)
	{
		return p;
	}
	else
	{
		return NULL;
	}
}

/*插入*/
bool Insert(List L, ElemType x, Position p) //在p的前一节点插入
{
	Position temp, pre;
	for (pre = L; pre&&pre->Next != p; pre = pre->Next); //找到p的前一个结点
	if (pre == NULL)
	{
		printf("插入位置参数错误。\n");
		return false;
	}
	else
	{
		temp = (Position)malloc(sizeof(struct LNode));
		temp->Data = x;
		temp->Next = p;
		pre->Next = temp;
		return true;
	}
}

List Insert(ElemType x, int i, List ptrL) //按序号位置插入
{
	List p, s;
	if (i == 1) //新节点插入在表头
	{
		s = (List)malloc(sizeof(struct LNode));
		s->Data = x;
		s->Next = NULL;
		return s;
	}
	p = FindKth(i - 1, ptrL);
	if (p==NULL)
	{
		printf("参数i错误");
		return NULL;
	}
	else
	{
		s = (List)malloc(sizeof(struct LNode));
		s->Data = x;
		s->Next = p->Next;
		p->Next = s;
		return ptrL;
	}
}

bool Delete(List L, Position p)
{
	Position temp, pre;
	for (pre = L; pre&&pre->Next != p; pre = pre->Next);
	if (pre==NULL||p==NULL)
	{
		printf("删除位置参数错误！\n");
		return false;
	}
	else
	{
		pre->Next = p->Next;
		free(p);
		return true;
	}
}

int main()
{
	List L=NULL;
	for (int i = 1; i < 10;i++)
	{
		L=Insert(9 - i, i, L);
	}
	//Delete(L, );
	printf("链表长度：%d", Length(L));
	return 0;
}