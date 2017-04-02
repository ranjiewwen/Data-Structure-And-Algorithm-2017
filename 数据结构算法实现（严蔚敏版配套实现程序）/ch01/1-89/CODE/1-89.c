#include<stdio.h>
#define N 8
#define MAXSIZE 20 /* 一个用作示例的小顺序表的最大长度 */
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
#define LT(a,b) ((a)<(b))
typedef SqList HeapType; /* 堆采用顺序表存储表示 */
void HeapAdjust(HeapType *H,int s,int m) 
{ /* 已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数 */
  /* 调整H.r[s]的关键字,使H.r[s..m]成为一个大顶堆(对其中记录的关键字而言) */
  RedType rc;
  int j;
  rc=(*H).r[s];
  for(j=2*s;j<=m;j*=2)
  { /* 沿key较大的孩子结点向下筛选 */
    if(j<m&&LT((*H).r[j].key,(*H).r[j+1].key))
      ++j; /* j为key较大的记录的下标 */
    if(!LT(rc.key,(*H).r[j].key))
      break; /* rc应插入在位置s上 */
    (*H).r[s]=(*H).r[j];
    s=j;
  }
  (*H).r[s]=rc; /* 插入 */
}
void HeapSort(HeapType *H)
{ /* 对顺序表H进行堆排序。*/
  RedType t;
  int i;
  for(i=(*H).length/2;i>0;--i) /* 把H.r[1..H.length]建成大顶堆 */
    HeapAdjust(H,i,(*H).length);
  for(i=(*H).length;i>1;--i)
  { /* 将堆顶记录和当前未经排序子序列H.r[1..i]中最后一个记录相互交换 */
    t=(*H).r[1];
    (*H).r[1]=(*H).r[i];
    (*H).r[i]=t;
    HeapAdjust(H,1,i-1); /* 将H.r[1..i-1]重新调整为大顶堆 */
  }
}
void print(HeapType H)
{
  int i;
  for(i=1;i<=H.length;i++)
    printf("(%d,%d)",H.r[i].key,H.r[i].otherinfo);
  printf("\n");
}
void main()
{
  RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
  HeapType h;
  int i;
  for(i=0;i<N;i++)
    h.r[i+1]=d[i];
  h.length=N;
  printf("排序前:\n");
  print(h);
  HeapSort(&h);
  printf("排序后:\n");
  print(h);
}
