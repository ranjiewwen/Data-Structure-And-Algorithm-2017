#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;
/* c2-2.h 线性表的单链表存储结构 */
struct LNode
{
  ElemType data;
  struct LNode *next;
};
typedef struct LNode *LinkList; /* 另一种定义LinkList的方法 */
Status InitList_CL(LinkList *L)
{ /* 操作结果：构造一个空的线性表L */
  *L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
  if(!*L) /* 存储分配失败 */
    exit(OVERFLOW);
  (*L)->next=*L; /* 指针域指向头结点 */
  return OK;
}
Status ListEmpty_CL(LinkList L)
{ /* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
  if(L->next==L) /* 空 */
    return TRUE;
  else
    return FALSE;
}
int ListLength_CL(LinkList L)
{ /* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
  int i=0;
  LinkList p=L->next; /* p指向头结点 */
  while(p!=L) /* 没到表尾 */
  {
    i++;
    p=p->next;
  }
  return i;
}
Status GetElem_CL(LinkList L,int i,ElemType *e)
{ /* 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
  int j=1; /* 初始化,j为计数器 */
  LinkList p=L->next->next; /* p指向第一个结点 */
  if(i<=0||i>ListLength_CL(L)) /* 第i个元素不存在 */
    return ERROR;
  while(j<i)
  { /* 顺指针向后查找,直到p指向第i个元素 */
    p=p->next;
    j++;
  }
  *e=p->data; /* 取第i个元素 */
  return OK;
}
Status ListInsert_CL(LinkList *L,int i,ElemType e) /* 改变L */
{ /* 在L的第i个位置之前插入元素e */
  LinkList p=(*L)->next,s; /* p指向头结点 */
  int j=0;
  if(i<=0||i>ListLength_CL(*L)+1) /* 无法在第i个元素之前插入 */
    return ERROR;
  while(j<i-1) /* 寻找第i-1个结点 */
  {
    p=p->next;
    j++;
  }
  s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
  s->data=e; /* 插入L中 */
  s->next=p->next;
  p->next=s;
  if(p==*L) /* 改变尾结点 */
    *L=s;
  return OK;
}
Status ListTraverse_CL(LinkList L,void(*vi)(ElemType))
{ /* 初始条件:L已存在。操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
  LinkList p=L->next->next;
  while(p!=L->next)
  {
    vi(p->data);
    p=p->next;
  }
  printf("\n");
  return OK;
}
void visit(ElemType c)
{
  printf("%d ",c);
}
void main()
{
  LinkList L;
  ElemType e;
  int j;
  Status i;
  i=InitList_CL(&L); /* 初始化单循环链表L */
  printf("初始化单循环链表L i=%d (1:初始化成功)\n",i);
  i=ListEmpty_CL(L);
  printf("L是否空 i=%d(1:空 0:否)\n",i);
  ListInsert_CL(&L,1,3); /* 在L中依次插入3,5 */
  ListInsert_CL(&L,2,5);
  i=GetElem_CL(L,1,&e);
  j=ListLength_CL(L);
  printf("L中数据元素个数=%d,第1个元素的值为%d。\n",j,e);
  printf("L中的数据元素依次为：");
  ListTraverse_CL(L,visit);
}
