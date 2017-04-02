#include<stdio.h> /* EOF(=^Z或F6),NULL */
#define N 8
#define MAXSIZE 20 /* 一个用作示例的小顺序表的最大长度 */
#define LT(a,b) ((a)<(b))
typedef int InfoType; /* 定义其它数据项的类型 */
typedef int KeyType; /* 定义关键字类型为整型 */
typedef struct
{
  KeyType key; /* 关键字项 */
  InfoType otherinfo; /* 其它数据项，具体类型在主程中定义 */
}RedType; /* 记录类型 */

typedef struct
{
  RedType r[MAXSIZE+1]; /* r[0]闲置或用作哨兵单元 */
  int length; /* 顺序表长度 */
}SqList; /* 顺序表类型 */
 void BInsertSort(SqList *L)
{ /* 对顺序表L作折半插入排序。*/
  int i,j,m,low,high;
  for(i=2;i<=(*L).length;++i)
  {
    (*L).r[0]=(*L).r[i]; /* 将L.r[i]暂存到L.r[0] */
    low=1;
    high=i-1;
    while(low<=high)
    { /* 在r[low..high]中折半查找有序插入的位置 */
      m=(low+high)/2; /* 折半 */
      if LT((*L).r[0].key,(*L).r[m].key)
        high=m-1; /* 插入点在低半区 */
      else
        low=m+1; /* 插入点在高半区 */
    }
    for(j=i-1;j>=high+1;--j)
      (*L).r[j+1]=(*L).r[j]; /* 记录后移 */
    (*L).r[high+1]=(*L).r[0]; /* 插入 */
  }
}
void print(SqList L)
{
  int i;
  for(i=1;i<=L.length;i++)
    printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
  printf("\n");
}
void main()
{
  RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
  SqList l1;
  int i;
  for(i=0;i<N;i++) /* 给l1.r赋值 */
    l1.r[i+1]=d[i];
  l1.length=N;
  printf("排序前:\n");
  print(l1);
  BInsertSort(&l1);
  printf("折半插入排序后:\n");
  print(l1);
}
