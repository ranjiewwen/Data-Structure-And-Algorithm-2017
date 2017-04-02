#include "stdio.h"
#define MEMORY_SIZE  100  /* 内存大小 */
#define MAX_STACKS 10      /* 栈的个数加1*/
typedef char element;
element memory [MEMORY_SIZE];
int top[MAX_STACKS-1];
int boundary[MAX_STACKS];
/* 置栈空*/
void Initial(int n)
{/*将各个顺序栈置空*/
	int i;
	top [0] = boundary [0] = -1;
	for ( i =1;  i<n;  i ++ )
		top[i]=boundary[i]= (MEMORY_SIZE/n)*i;
	boundary[n]=MEMORY_SIZE-1;
}
/*进栈*/
void Push(int i, element item)
{
	if (top[i] == boundary[i+1] )
	{
		printf("第%d个栈已满。",i);
		exit(1);
	}
	memory[++top[i]] = item;
}
/*退栈*/
element Pop(int i)
{
	if ( top[i] == boundary[i] )
	{
		printf("第%d个栈已空。",i);
		exit(1);
	}
	return memory[top[i]--];
}
void main()
{
	int  n=2;      /* 使用的栈的个数 */
	element first,sec;
	Initial(n);
	Push(1,'a');
	Push(0,'b');
	sec=Pop(1);
	first=Pop(0);
}

