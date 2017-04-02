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
void P2_InsertSort(SqList *L)
{ /* 2_路插入排序 */
  int i,j,first,final;
  RedType *d;
  d=(RedType*)malloc((*L).length*sizeof(RedType)); /* 生成L.length个记录的临时空间 */
  d[0]=(*L).r[1]; /* 设L的第1个记录为d中排好序的记录(在位置[0]) */
  first=final=0; /* first、final分别指示d中排好序的记录的第1个和最后1个记录的位置 */
  for(i=2;i<=(*L).length;++i)
  { /* 依次将L的第2个～最后1个记录插入d中 */
    if((*L).r[i].key<d[first].key)
    { /* 待插记录小于d中最小值，插到d[first]之前(不需移动d数组的元素) */
      first=(first-1+(*L).length)%(*L).length; /* 设d为循环向量 */
      d[first]=(*L).r[i];
    }
    else if((*L).r[i].key>d[final].key)
    { /* 待插记录大于d中最大值，插到d[final]之后(不需移动d数组的元素) */
      final=final+1;
      d[final]=(*L).r[i];
    }
    else
    { /* 待插记录大于d中最小值，小于d中最大值，插到d的中间(需要移动d数组的元素) */
      j=final++; /* 移动d的尾部元素以便按序插入记录 */
      while((*L).r[i].key<d[j].key)
      {
        d[(j+1)%(*L).length]=d[j];
        j=(j-1+(*L).length)%(*L).length;
      }
      d[j+1]=(*L).r[i];
    }
  }
  for(i=1;i<=(*L).length;i++) /* 把d赋给L.r */
    (*L).r[i]=d[(i+first-1)%(*L).length]; /* 线性关系 */
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
  P2_InsertSort(&l1);
  printf("2_路插入排序后:\n");
  print(l1);
}
