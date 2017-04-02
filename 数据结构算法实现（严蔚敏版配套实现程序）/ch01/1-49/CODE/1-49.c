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
DuLinkList GetElemP(DuLinkList L,int i) /* 另加 */
{ /* 在双向链表L中返回第i个元素的位置指针*/
  int j;
  DuLinkList p=L;
  for(j=1;j<=i;j++)
    p=p->next;
  return p;
}
Status ListInsert(DuLinkList L,int i,ElemType e)
{ /* 在带头结点的双链循环线性表L中第i个位置之前插入元素e，i的合法值为1≤i≤表长+1 */
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
void ListTraverse(DuLinkList L,void(*visit)(ElemType))
{ /* 由双链循环线性表L的头结点出发,正序对每个数据元素调用函数visit() */
  DuLinkList p=L->next; /* p指向头结点 */
  while(p!=L)
  {
    visit(p->data);
    p=p->next;
  }
  printf("\n");
}
Status ListDelete(DuLinkList L,int i,ElemType *e)
{ /* 删除带头结点的双链循环线性表L的第i个元素,i的合法值为1≤i≤表长+1 */
  DuLinkList p;
  if(i<1||i>ListLength(L)) /* i值不合法 */
    return ERROR;
  p=GetElemP(L,i);  /* 在L中确定第i个元素的位置指针p */
  if(!p) /* p=NULL,即第i个元素不存在 */
    return ERROR;
  *e=p->data;
  p->prior->next=p->next;
  p->next->prior=p->prior;
  free(p);
  return OK;
}
void vd(ElemType c) /* ListTraverse()调用的函数(类型一致) */
{
  printf("%d ",c);
}
void main()
{
  DuLinkList L;
  int i,n=2;
  ElemType e;
  InitList(&L);
  printf("初始化链表依次输入1，2，3，4，5\n");
  for(i=1;i<=5;i++)
    ListInsert(L,i,i); /* 在第i个结点之前插入i */
  ListDelete(L,n,&e); /* 删除并释放第n个结点 */
  printf("删除第%d个结点，值为%d，其余结点为：",n,e);
  ListTraverse(L,vd); /* 正序输出 */
}
