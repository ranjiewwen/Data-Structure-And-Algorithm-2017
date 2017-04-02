#include"stdio.h"
#define n 4
int t[n*(n+1)/2];
void Store(int x,int i,int j)
{
    if(x<0||j<0||i>=n||j>=n)
    {
        printf("数组出界！");
        exit(1);
    }
    else if(i>=j)
        t[i*(i+1)/2+j]=x;
}
void main()
{
    int i,j;
    int D[n][n]={2,4,6,0,4,1,9,5,6,9,4,7,0,5,7,0};
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            Store(D[i][j],i,j);
    for(i=0;i<=n*n/2+1;i++)
	   printf("%d  ",t[i]);
    printf("\n");
}
