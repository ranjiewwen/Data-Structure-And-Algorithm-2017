#include<stdio.h>
void main()
{
    int i,j,n=13;
    printf("N=");
    while(n>12)
    scanf("%d",&n); /*控制输入正确的值以保证屏幕显示的图形正确*/
    for(i=0;i<=n;i++) /*控制输出N行*/
    {
        for(j=0;j<24-2*i;j++)
            printf(" "); /*控制输出第i行前面的空格*/
        for(j=1;j<i+2;j++)
            printf("%4d",c(i,j)); /*输出第i行的第j个值*/
        printf("\n");
    }
}
int c(int x,int y) /*求杨辉三角形中第x行第y列的值*/
{
    int z;
    if((y==1)||(y==x+1))
    return 1; /*若为x行的第1或第x+1列，则输出1*/
    z=c(x-1,y-1)+c(x-1,y); /*否则，其值为前一行中第y-1列与第y列值之和*/
    return z;
}
