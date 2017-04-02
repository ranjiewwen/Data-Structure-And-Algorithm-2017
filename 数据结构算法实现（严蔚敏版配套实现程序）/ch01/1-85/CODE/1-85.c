#include<stdio.h>
#define N 8
#define MAXSIZE 20 /* 一个用作示例的小顺序表的最大长度 */
typedef int KeyType; /* 定义关键字类型为整型 */
typedef int InfoType;
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
int Partition(SqList *L,int low,int high)
{ /* 交换顺序表L中子表r[low..high]的记录，枢轴记录到位，并返回其 */
  /* 所在位置，此时在它之前（后）的记录均不大（小）于它。*/
  KeyType pivotkey;
  (*L).r[0]=(*L).r[low]; /* 用子表的第一个记录作枢轴记录 */
  pivotkey=(*L).r[low].key; /* 枢轴记录关键字 */
  while(low< high)
  { /* 从表的两端交替地向中间扫描 */
    while(low<high&&(*L).r[high].key>=pivotkey)
      --high;
    (*L).r[low]=(*L).r[high]; /* 将比枢轴记录小的记录移到低端 */
    while(low<high&&(*L).r[low].key<=pivotkey)
      ++low;
    (*L).r[high]=(*L).r[low]; /* 将比枢轴记录大的记录移到高端 */
  }
  (*L).r[low]=(*L).r[0]; /* 枢轴记录到位 */
  return low; /* 返回枢轴位置 */
}
void QSort(SqList *L,int low,int high)
{ /* 对顺序表L中的子序列L.r[low..high]作快速排序。*/
  int pivotloc;
  if(low<high)
  { /* 长度大于1 */
    pivotloc=Partition(L,low,high); /* 将L.r[low..high]一分为二 */
    QSort(L,low,pivotloc-1); /* 对低子表递归排序，pivotloc是枢轴位置 */
    QSort(L,pivotloc+1,high); /* 对高子表递归排序 */
  }
}
void QuickSort(SqList *L)
{ /* 对顺序表L作快速排序。*/
  QSort(L,1,(*L).length);
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
  SqList l;
  int i;
  for(i=0;i<N;i++)
    l.r[i+1]=d[i];
  l.length=N;
  printf("排序前:\n");
  print(l);
  QuickSort(&l);
  printf("排序后:\n");
  print(l);
}
