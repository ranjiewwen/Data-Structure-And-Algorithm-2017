#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
/* #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3,故去掉此行 */
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
typedef int ElemType;
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
int LocateElem_CL(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
{ /* 初始条件：线性表L已存在，compare()是数据元素判定函数 */
  /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
  /*           若这样的数据元素不存在，则返回值为0 */
  int i=0;
  LinkList p=L->next->next; /* p指向第一个结点 */
  while(p!=L->next)
  {
    i++;
    if(compare(p->data,e)) /* 满足关系 */
      return i;
    p=p->next;
  }
  return 0;
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
Status ListDelete_CL(LinkList *L,int i,ElemType *e) /* 改变L */
{ /* 删除L的第i个元素,并由e返回其值 */
  LinkList p=(*L)->next,q; /* p指向头结点 */
  int j=0;
  if(i<=0||i>ListLength_CL(*L)) /* 第i个元素不存在 */
    return ERROR;
  while(j<i-1) /* 寻找第i-1个结点 */
  {
    p=p->next;
    j++;
  }
  q=p->next; /* q指向待删除结点 */
  p->next=q->next;
  *e=q->data;
  if(*L==q) /* 删除的是表尾元素 */
    *L=p;
  free(q); /* 释放待删除结点 */
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
Status compare(ElemType c1,ElemType c2)
{
  if(c1==c2)
    return TRUE;
  else
    return FALSE;
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
  printf("依次在单循环链表中插入3,5\n");
  ListInsert_CL(&L,1,3); /* 在L中依次插入3,5 */
  ListInsert_CL(&L,2,5);
  j=LocateElem_CL(L,5,compare);
  if(j)
    printf("L的第%d个元素为5。\n",j);
  else
    printf("不存在值为5的元素\n");
  i=ListDelete_CL(&L,2,&e);
  printf("删除L的第2个元素：\n");
  if(i)
  {
    printf("删除的元素值为%d,现在L中的数据元素依次为：",e);
    ListTraverse_CL(L,visit);
  }
  else
    printf("删除不成功！\n");
}
