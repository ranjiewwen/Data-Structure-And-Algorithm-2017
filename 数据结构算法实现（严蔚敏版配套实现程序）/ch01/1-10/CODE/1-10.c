#include "stdio.h"
#define n 4
int t[3*n];
void	Store(int x, int i, int j)
{
	if ( i < 0 || j <0 ||i >=n || j >=n)
	{
		printf("数组出界！");
		exit(1);
	}
	switch (i - j) {
		case 1: /* 低对角线*/ 
			t[i - 1] = x; break;
		case 0: /* 主对角线*/ 
			t[n + i - 1] = x; break;
		case -1: /*  高对角线*/ 
			t[2 *n + i - 1] = x; break;
		default:
			if(x != 0)
			{
				printf("非对角线上元素值必须为零");
				exit(1);
			}
	}
}
void main()
{
	int i,j;
	int D[n][n]={{2,1,0,0},{3,1,3,0},{0,5,2,7},{0,0,9,0}};
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			Store(D[i][j],i,j);
	for(i=0;i<3*n-2;i++)
	   printf("%d  ",t[i]);
    printf("\n");
}

