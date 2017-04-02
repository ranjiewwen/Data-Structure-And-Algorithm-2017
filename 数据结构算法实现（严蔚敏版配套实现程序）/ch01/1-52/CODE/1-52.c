#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;
typedef struct DuLNode
{
  ElemType data;
 struct DuLNode *prior,*next;
}DuLNode,*DuLinkList;
Status InitList(DuLinkList *L)
{ /* 产生空的双向循环链表L */
  *L=(DuLinkList)malloc(sizeof(DuLNode));
  if(*L)
  {
    (*L)->next=(*L)->prior=*L;
    return OK;
  }
  else
    return OVERFLOW;
}
Status ClearList(DuLinkList L) /* 不改变L */
{ /* 初始条件：L已存在。操作结果：将L重置为空表 */
  DuLinkList q,p=L->next; /* p指向第一个结点 */
  while(p!=L) /* p没到表头 */
  {
    q=p->next;
    free(p);
    p=q;
  }
  L->next=L->prior=L; /* 头结点的两个指针域均指向自身 */
  return OK;
}
int ListLength(DuLinkList L)
{ /* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
  int i=0;
  DuLinkList p=L->next; /* p指向第一个结点 */
  while(p!=L) /* p没到表头 */
  {
    i++;
    p=p->next;
  }
  return i;
}
Status GetElem(DuLinkList L,int i,ElemType *e)
{ /* 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
  int j=1; /* j为计数器 */
  DuLinkList p=L->next; /* p指向第一个结点 */
  while(p!=L&&j<i) /* 顺指针向后查找,直到p指向第i个元素或p指向头结点 */
  {
    p=p->next;
    j++;
  }
  if(p==L||j>i) /* 第i个元素不存在 */
    return ERROR;
  *e=p->data; /* 取第i个元素 */
  return OK;
}
DuLinkList GetElemP(DuLinkList L,int i) /* 另加 */
{ /* 在双向链表L中返回第i个元素的位置指针*/
  int j;
  DuLinkList p=L;
  for(j=1;j<=i;j++)
    p=p->next;
  return p;
}
Status ListInsert(DuLinkList L,int i,ElemType e)
{
  DuLinkList p,s;
  if(i<1||i>ListLength(L)+1) /* i值不合法 */
    return ERROR;
  p=GetElemP(L,i-1); /* 在L中确定第i-1个元素的位置指针p */
  if(!p) /* p=NULL,即第i-1个元素不存在 */
    return ERROR;
  s=(DuLinkList)malloc(sizeof(DuLNode));
  if(!s)
    return OVERFLOW;
  s->data=e; /* 在第i-1个元素之后插入 */
  s->prior=p;
  s->next=p->next;
  p->next->prior=s;
  p->next=s;
  return OK;
}
Status ListEmpty(DuLinkList L)
{ /* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
  if(L->next==L&&L->prior==L)
    return TRUE;
  else
    return FALSE;
}
void vd(ElemType c) /* ListTraverse()调用的函数(类型一致) */
{
  printf("%d ",c);
}
void main()
{
  DuLinkList L;
  int i,n,j;
  ElemType e;
  InitList(&L);
  printf("初始化链表依次输入1，2，3，4，5\n");
  for(i=1;i<=5;i++)
    ListInsert(L,i,i); /* 在第i个结点之前插入i */
  n=3;
  j=GetElem(L,n,&e); /* 将链表的第n个元素赋值给e */
  if(j)
    printf("链表的第%d个元素值为%d\n",n,e);
  else
    printf("不存在第%d个元素\n",n);
}
