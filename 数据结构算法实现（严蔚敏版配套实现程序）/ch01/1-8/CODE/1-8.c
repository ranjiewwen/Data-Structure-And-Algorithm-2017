#include "stdio.h"
#define n 3
#define m 3
void Get_Saddle(int A[m][n])/*求矩阵A中的马鞍点*/
{
  	int i,j,flag,min,k;
	for(i=0;i<m;i++)
  	{
    		for(min=A[i][0],j=0;j<n;j++)
      		if(A[i][j]<min) min=A[i][j]; /*求一行中的最小值*/
    			for(j=0;j<n;j++)
      		if(A[i][j]==min) /*判断这个(些)最小值是否鞍点*/
      		{
        		for(flag=1,k=0;k<m;k++)
         			 if(min<A[k][j]) flag=0;
       		 if(flag)
         			 printf("Found a saddle element!\nA[%d][%d]=%d",i,j,A[i][j]);
      		}
 	 }
   printf("\n");
}/*Get_Saddle*/
void main()
{
	int A[m][n]={1,2,3,4,5,6,7,8,9};
	/*初始化A[n] */
	Get_Saddle(A);
}
