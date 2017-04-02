#include<stdio.h>
#define M 20
void fun(int *x,int n)
{
    int *p,m=n/2,*i,*j;
    i=x;
    j=x+n-1;
    p=x+m;
    for(;i<p;i++,j--)
    {
        int t=*i;
        *i=*j;
        *j=t;
    }
}
void main()
{
    int i,a[M],n;
    printf("\nEnter n:\n");
    scanf("%d",&n);
    printf("The original array:\n");
    for(i=0;i<n;i++)
        scanf("%d",a+i);
    fun(a,i);
    printf("\nThe array inverted:\n");
    for(i=0;i<n;i++)
        printf("%d  ",*(a+i));
}
