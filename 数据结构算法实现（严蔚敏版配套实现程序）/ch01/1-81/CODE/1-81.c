#include<limits.h> /* INT_MAX等 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#define N 8
#define SIZE 100 /* 静态链表容量 */
typedef int KeyType; /* 定义关键字类型为整型 */
typedef int InfoType; /* 定义其它数据项的类型 */
typedef struct
{
  KeyType key; /* 关键字项 */
  InfoType otherinfo; /* 其它数据项，具体类型在主程中定义 */
}RedType; /* 记录类型 */

typedef struct
{
  RedType rc; /* 记录项 */
  int next; /* 指针项 */
}SLNode; /* 表结点类型 */
typedef struct
{
  SLNode r[SIZE]; /* 0号单元为表头结点 */
  int length; /* 链表当前长度 */
}SLinkListType; /* 静态链表类型 */
void TableInsert(SLinkListType *SL,RedType D[],int n)
{ /* 由数组D建立n个元素的表插入排序的静态链表SL */
  int i,p,q;
  (*SL).r[0].rc.key=INT_MAX; /* 表头结点记录的关键字取最大整数(非降序链表的表尾) */
  (*SL).r[0].next=0; /* next域为0表示表尾(现为空表，初始化) */
  for(i=0;i<n;i++)
  {
    (*SL).r[i+1].rc=D[i]; /* 将数组D的值赋给静态链表SL */
    q=0;
    p=(*SL).r[0].next;
    while((*SL).r[p].rc.key<=(*SL).r[i+1].rc.key)
    { /* 静态链表向后移 */
      q=p;
      p=(*SL).r[p].next;
    }
    (*SL).r[i+1].next=p; /* 将当前记录插入静态链表 */
    (*SL).r[q].next=i+1;
  }
  (*SL).length=n;
}
void Sort(SLinkListType L,int adr[])
{ /* 求得adr[1..L.length]，adr[i]为静态链表L的第i个最小记录的序号 */
  int i=1,p=L.r[0].next;
  while(p)
  {
    adr[i++]=p;
    p=L.r[p].next;
  }
}
void Rearrange(SLinkListType *L,int adr[])
{ /* adr给出静态链表L的有序次序，即L.r[adr[i]]是第i小的记录。 */
  int i,j,k;
  for(i=1;i<(*L).length;++i)
    if(adr[i]!=i)
    {
      j=i;
      (*L).r[0]=(*L).r[i]; /* 暂存记录(*L).r[i] */
      while(adr[j]!=i)
      { /* 调整(*L).r[adr[j]]的记录到位直到adr[j]=i为止 */
        k=adr[j];
        (*L).r[j]=(*L).r[k];
        adr[j]=j;
        j=k; /* 记录按序到位 */
      }
      (*L).r[j]=(*L).r[0];
      adr[j]=j;
    }
}
void print(SLinkListType L)
{
  int i;
  for(i=1;i<=L.length;i++)
    printf("key=%d ord=%d next=%d\n",L.r[i].rc.key,L.r[i].rc.otherinfo,L.r[i].next);
}
void main()
{
  RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
  SLinkListType l1;
  int *adr,i;
  TableInsert(&l1,d,N);
  printf("排序前:\n");
  print(l1);
  adr=(int*)malloc((l1.length+1)*sizeof(int));
  Sort(l1,adr);
  for(i=1;i<=l1.length;i++)
    printf("adr[%d]=%d ",i,adr[i]);
  printf("\n");
  Rearrange(&l1,adr);
  printf("l1排序后:\n");
  print(l1);
}
