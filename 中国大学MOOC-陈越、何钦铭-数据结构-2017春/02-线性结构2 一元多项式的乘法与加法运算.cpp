/*!
 * \file 02-线性结构2 一元多项式的乘法与加法运算.cpp
 *
 * \author ranjiewen
 * \date 2017/03/19 16:11
 *
 * 
 */
   

//动态数组实现较好

//用链表设计

#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode* Polynomial;

struct PolyNode{
	int coef;
	int expon;
	Polynomial next;
};

Polynomial ReadPoly();
Polynomial Mult(Polynomial P1,Polynomial P2);
void PrintPoly(Polynomial PP);
Polynomial Add(Polynomial P1,Polynomial P2);

int main() //程序框架搭建
{
	Polynomial P1, P2, PP, PS;
	P1 = ReadPoly();
	P2 = ReadPoly();

	PP = Mult(P1, P2);
	PrintPoly(PP);

	PS = Add(P1, P2);
	PrintPoly(PS);

	return 0;
}

//对Rear指针的处理：1.初值为NULL,根据是否为空做不同处理；2.指向一个空节点
//*pRear当前结果表达式尾项指针的指针
//函数实现在pRear后面插入节点
void Attach(int c, int e, Polynomial *pRear)  
{
	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->coef = c;
	P->expon = e;
	P->next = NULL;
	(*pRear)->next = P;
	*pRear = P;
}

Polynomial ReadPoly()
{
	Polynomial P, Rear, t;
	int c, e, N;
	scanf("%d", &N);
	P = (Polynomial)malloc(sizeof(struct PolyNode)); //链表头空节点
	P->next = NULL;
	Rear = P; 
	while (N--)
	{
		scanf("%d %d", &c, &e);
		if (c != 0)  
		   Attach(c, e, &Rear); //将当前项插入多项式尾部
	}
	t = P;
	P = P->next;
	free(t); //删除临时生成的头结点
	return P;
}

Polynomial Add(Polynomial P1, Polynomial P2)
{
	Polynomial t1, t2;
	t1 = P1;
	t2 = P2;
	//生成新的头结点
	Polynomial P,t;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->next = NULL;
	Polynomial Rear;
	Rear = P;
	while (t1&&t2)
	{
		if (t1->expon==t2->expon)
		{
			if (t1->coef+t2->coef)  //系数和为0时不添加到尾节点上  /*考虑周全*/
			{
				Attach(t1->coef + t2->coef, t1->expon, &Rear);
			}
			t1 = t1->next;
			t2 = t2->next;
		}
		else if (t1->expon>t2->expon)
		{
			Attach(t1->coef, t1->expon, &Rear);
			t1=t1->next;
		}else 
		{
			Attach(t2->coef, t2->expon, &Rear);
			t2 = t2->next;
		}
	}
	while (t1)
	{
		Attach(t1->coef, t1->expon, &Rear);
		t1 = t1->next;
	}
	while (t2)
	{
		Attach(t2->coef, t2->expon, &Rear);
		t2 = t2->next;
	}
	t = P;
	P = P->next;
	free(t);
	return P;
}

//多项式乘法方法：
//1. 将乘法运算转换为加法运算，让P1的每一项和P2相乘，在加到结果多项式中
//2. 逐项插入，将P1当前项乘P2当前项，在插入到结果表达式中，关键是要找到插入的位置

Polynomial Mult(Polynomial P1, Polynomial P2)
{
	Polynomial P, Rear;
	Polynomial t1, t2, t;
	if (!P1||!P2)
	{
		return NULL;
	}
	t1 = P1;
	t2 = P2;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	Rear = P;
	while (t2)
	{
		//先用P1的第一项乘以P2,得到初始结果多项式
		Attach(t1->coef*t2->coef, t1->expon + t2->expon, &Rear);
		t2 = t2->next;
	}
	t1 = t1->next;
	while (t1)
	{
		t2 = P2;
		Rear = P; //将尾节点置到头结点来
		while (t2)
		{
			int e = t1->expon + t2->expon;
			int c = t1->coef * t2->coef;   //以后的每一项相乘的结果
			while (Rear->next&&Rear->next->expon>e) //找插入位置
			{
				Rear = Rear->next;
			}
			if (Rear->next&&Rear->next->expon==e)
			{
				if (Rear->next->coef+c) //判系数是否为0
				{
					Rear->next->coef += c;
				}
				else  //为0删除节点
				{
					t = Rear->next;
					Rear->next = t->next;
					free(t);
				}
			}
			else  //插入位置
			{
				t = (Polynomial)malloc(sizeof(struct PolyNode));
				t->coef = c;
				t->expon = e;
				t->next = Rear->next;
				Rear->next = t;

				Rear = Rear->next;
			}
			t2 = t2->next;
		}
		t1 = t1->next;
	}
	t2 = P;
	P = P->next;
	free(t2);

	return P;
}

void PrintPoly(Polynomial P)
{
	int flag = 0;//辅助调整输出格式
	if (!P)
	{
		printf("0 0\n"); /*格式*/
		return;
	}
	while (P)
	{
		if (!flag) //第一次
		{
			flag = 1;
		}
		else
		{
			printf(" ");
		}
		printf("%d %d", P->coef, P->expon);
		P = P->next;
	}
	printf("\n");
}

