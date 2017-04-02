#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
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
void MergeList_CL(LinkList *La,LinkList Lb)
{
  LinkList p=Lb->next;
  Lb->next=(*La)->next;
  (*La)->next=p->next;
  free(p);
  *La=Lb;
}
void visit(ElemType c)
{
  printf("%d ",c);
}
void main()
{
  int n=5,i;
  LinkList La,Lb;
  InitList_CL(&La);
  for(i=1;i<=n;i++)
    ListInsert_CL(&La,i,i);
  printf("La="); /* 输出链表La的内容 */
  ListTraverse_CL(La,visit);
  InitList_CL(&Lb);
  for(i=1;i<=n;i++)
    ListInsert_CL(&Lb,1,i*2);
  printf("Lb="); /* 输出链表Lb的内容 */
  ListTraverse_CL(Lb,visit);
  MergeList_CL(&La,Lb);
  printf("La+Lb="); /* 输出合并后的链表的内容 */
  ListTraverse_CL(La,visit);
}
