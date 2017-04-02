#include <stdio.h>
#include <math.h>
void main()
{
    int a[16][16],i,j,n,k;
    printf("Please input  n(1~15,it must be odd.): ");
    scanf("%d",&n);
    while(!(n>=1&&n<=15)||n%2==0)
    {
        printf("The number is invalid.Please insert again:");
        scanf("%d",&n);
    }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            a[i][j]=0;
    j=n/2+1;
    a[1][j]=1;
    i=1;
    for(k=2;k<=n*n;k++)
    {
         i=i-1;j=j+1;
    if(i==0&&j==n+1)
    {
    i=i+2;j=j-1;
    }
    else
    {
        if(i==0)
        {
            i=n;
        }
        if(j==n+1)
        {
              j=1;
        }
    }
    if(a[i][j]==0)
    {
        a[i][j]=k;
    }
    else
    {
        i=i+2;
        j=j-1;
        a[i][j]=k;
    }
  }
  for(i=1;i<=n;i++)
  {
    for(j=1;j<=n;j++)
        printf("%3d",a[i][j]);
    printf("\n");
  }
}
