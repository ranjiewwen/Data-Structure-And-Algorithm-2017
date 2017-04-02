#include "stdio.h"
#define MAX_PARENT 100
int 	parent[MAX_PARENT];
void Initialize(int n)
{/* 初始化，每个类/树有一个元素*/
	int e ;
	for (e=1; e <= n&&n<MAX_PARENT; e++)
		parent[e] = 0;
}
int Find(int e)
{ /*返回包含e的树的根节点*/
	while (parent[e]&&e<MAX_PARENT)
		e = parent[e]; /* 上移一层*/
	return e;
}
void Union(int i, int j)
{/* 将根为i 和j的两棵树进行合并*/
	if(j<MAX_PARENT)
		parent[j]=i;
}
void Combine(int a,int b)
{
	int i = Find(a); 
	int j = Find(b);
	if(i!= j) 
		Union(i, j);
}
void main()
{
	Combine(1,2);
}
