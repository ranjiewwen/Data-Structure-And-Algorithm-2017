#include<limits.h> /* INT_MAX等 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<stdlib.h> /* atoi() */
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
void Arrange(SLinkListType *SL)
{ /* 根据静态链表SL中各结点的指针值调整记录位置，使得SL中记录按关键字 */
  /* 非递减有序顺序排列*/
  int i,p,q;
  SLNode t;
  p=(*SL).r[0].next; /* p指示第一个记录的当前位置 */
  for(i=1;i<(*SL).length;++i)
  { /* (*SL).r[1..i-1]中记录已按关键字有序排列,第i个记录在SL中的当前位置应不小于i */
    while(p<i)
      p=(*SL).r[p].next; /* 找到第i个记录，并用p指示其在SL中当前位置 */
    q=(*SL).r[p].next; /* q指示尚未调整的表尾 */
    if(p!=i)
    {
      t=(*SL).r[p]; /* 交换记录，使第i个记录到位 */
      (*SL).r[p]=(*SL).r[i];
      (*SL).r[i]=t;
      (*SL).r[i].next=p; /* 指向被移走的记录，使得以后可由while循环找回 */
    }
    p=q; /* p指示尚未调整的表尾，为找第i+1个记录作准备 */
  }
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
  Arrange(&l1);
  printf("l1排序后:\n");
  print(l1);
}
