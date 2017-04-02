#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
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
Status DestroyList_CL(LinkList *L)
{ /* 操作结果：销毁线性表L */
  LinkList q,p=(*L)->next; /* p指向头结点 */
  while(p!=*L) /* 没到表尾 */
  {
    q=p->next;
    free(p);
    p=q;
  }
  free(*L);
  *L=NULL;
  return OK;
}
Status ClearList_CL(LinkList *L) /* 改变L */
{ /* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
  LinkList p,q;
  *L=(*L)->next; /* L指向头结点 */
  p=(*L)->next; /* p指向第一个结点 */
  while(p!=*L) /* 没到表尾 */
  {
    q=p->next;
    free(p);
    p=q;
  }
  (*L)->next=*L; /* 头结点指针域指向自身 */
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
     printf("清空L：%d(1: 成功)\n",ClearList_CL(&L));
  printf("清空L后，L是否空：%d(1:空 0:否)\n",ListEmpty_CL(L));
  printf("销毁L：%d(1: 成功)\n",DestroyList_CL(&L));
}
