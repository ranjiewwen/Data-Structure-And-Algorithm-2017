#define CHAR /* 字符型 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
#ifdef CHAR
  typedef char TElemType;
  TElemType Nil=' '; /* 字符型以空格符为空 */
#endif
#ifdef INT
  typedef int TElemType;
  TElemType Nil=0; /* 整型以0为空 */
#endif
typedef struct BiTNode
{
  TElemType data;
  struct BiTNode *lchild,*rchild; /* 左右孩子指针 */
}BiTNode,*BiTree;
 typedef BiTree QElemType; /* 设队列元素为二叉树的指针类型 */
  typedef struct QNode
{
  QElemType data;
  struct QNode *next;
}QNode,*QueuePtr;
 typedef struct
{
  QueuePtr front,rear; /* 队头、队尾指针 */
}LinkQueue;
Status InitBiTree(BiTree *T)
{ /* 操作结果: 构造空二叉树T */
  *T=NULL;
  return OK;
}
void CreateBiTree(BiTree *T)
{
  TElemType ch;
#ifdef CHAR
  scanf("%c",&ch);
#endif
#ifdef INT
  scanf("%d",&ch);
#endif
  if(ch==Nil) /* 空 */
    *T=NULL;
  else
  {
    *T=(BiTree)malloc(sizeof(BiTNode));
    if(!*T)
      exit(OVERFLOW);
    (*T)->data=ch; /* 生成根结点 */
    CreateBiTree(&(*T)->lchild); /* 构造左子树 */
    CreateBiTree(&(*T)->rchild); /* 构造右子树 */
  }
}
 Status InitQueue(LinkQueue *Q)
{ /* 构造一个空队列Q */
  (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
  if(!(*Q).front)
    exit(OVERFLOW);
  (*Q).front->next=NULL;
  return OK;
}
 Status EnQueue(LinkQueue *Q,QElemType e)
{ /* 插入元素e为Q的新的队尾元素 */
  QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
  if(!p) /* 存储分配失败 */
    exit(OVERFLOW);
  p->data=e;
  p->next=NULL;
  (*Q).rear->next=p;
  (*Q).rear=p;
  return OK;
}
 Status QueueEmpty(LinkQueue Q)
{ /* 若Q为空队列,则返回TRUE,否则返回FALSE */
  if(Q.front==Q.rear)
    return TRUE;
  else
    return FALSE;
}
 Status DeQueue(LinkQueue *Q,QElemType *e)
{ /* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
  QueuePtr p;
  if((*Q).front==(*Q).rear)
    return ERROR;
  p=(*Q).front->next;
  *e=p->data;
  (*Q).front->next=p->next;
  if((*Q).rear==p)
    (*Q).rear=(*Q).front;
  free(p);
  return OK;
}
TElemType Parent(BiTree T,TElemType e)
{ /* 初始条件: 二叉树T存在,e是T中某个结点 */
  /* 操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂ */
  LinkQueue q;
  QElemType a;
  if(T) /* 非空树 */
  {
    InitQueue(&q); /* 初始化队列 */
    EnQueue(&q,T); /* 树根入队 */
    while(!QueueEmpty(q)) /* 队不空 */
    {
      DeQueue(&q,&a); /* 出队,队列元素赋给a */
      if(a->lchild&&a->lchild->data==e||a->rchild&&a->rchild->data==e)
      /* 找到e(是其左或右孩子) */
        return a->data; /* 返回e的双亲的值 */
      else /* 没找到e,则入队其左右孩子指针(如果非空) */
      {
        if(a->lchild)
          EnQueue(&q,a->lchild);
        if(a->rchild)
          EnQueue(&q,a->rchild);
      }
    }
  }
  return Nil; /* 树空或没找到e */
}
 BiTree Point(BiTree T,TElemType s)
{ /* 返回二叉树T中指向元素值为s的结点的指针。另加 */
  LinkQueue q;
  QElemType a;
  if(T) /* 非空树 */
  {
    InitQueue(&q); /* 初始化队列 */
    EnQueue(&q,T); /* 根结点入队 */
    while(!QueueEmpty(q)) /* 队不空 */
    {
      DeQueue(&q,&a); /* 出队,队列元素赋给a */
      if(a->data==s)
        return a;
      if(a->lchild) /* 有左孩子 */
        EnQueue(&q,a->lchild); /* 入队左孩子 */
      if(a->rchild) /* 有右孩子 */
        EnQueue(&q,a->rchild); /* 入队右孩子 */
    }
  }
  return NULL;
}
 TElemType LeftChild(BiTree T,TElemType e)
{ /* 初始条件: 二叉树T存在,e是T中某个结点 */
  /* 操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂ */
  BiTree a;
  if(T) /* 非空树 */
  {
    a=Point(T,e); /* a是结点e的指针 */
    if(a&&a->lchild) /* T中存在结点e且e存在左孩子 */
      return a->lchild->data; /* 返回e的左孩子的值 */
  }
  return Nil; /* 其余情况返回空 */
}
TElemType RightChild(BiTree T,TElemType e)
{ /* 初始条件: 二叉树T存在,e是T中某个结点 */
  /* 操作结果: 返回e的右孩子。若e无右孩子,则返回＂空＂ */
  BiTree a;
  if(T) /* 非空树 */
  {
    a=Point(T,e); /* a是结点e的指针 */
    if(a&&a->rchild) /* T中存在结点e且e存在右孩子 */
      return a->rchild->data; /* 返回e的右孩子的值 */
  }
  return Nil; /* 其余情况返回空 */
}
 TElemType LeftSibling(BiTree T,TElemType e)
{ /* 初始条件: 二叉树T存在,e是T中某个结点 */
  /* 操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂ */
  TElemType a;
  BiTree p;
  if(T) /* 非空树 */
  {
    a=Parent(T,e); /* a为e的双亲 */
    p=Point(T,a); /* p为指向结点a的指针 */
    if(p->lchild&&p->rchild&&p->rchild->data==e) /* p存在左右孩子且右孩子是e */
      return p->lchild->data; /* 返回p的左孩子(e的左兄弟) */
  }
  return Nil; /* 树空或没找到e的左兄弟 */
}

TElemType RightSibling(BiTree T,TElemType e)
{ /* 初始条件: 二叉树T存在,e是T中某个结点 */
  /* 操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂ */
  TElemType a;
  BiTree p;
  if(T) /* 非空树 */
  {
    a=Parent(T,e); /* a为e的双亲 */
    p=Point(T,a); /* p为指向结点a的指针 */
    if(p->lchild&&p->rchild&&p->lchild->data==e) /* p存在左右孩子且左孩子是e */
      return p->rchild->data; /* 返回p的右孩子(e的右兄弟) */
  }
  return Nil; /* 树空或没找到e的右兄弟 */
}

void main()
{
  BiTree T;
  TElemType e1,e2;
  InitBiTree(&T);
#ifdef CHAR
  printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
#endif
#ifdef INT
  printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
#endif
  CreateBiTree(&T);
printf("请输入要查询结点的值：");
 #ifdef CHAR
  scanf("%*c%c%*c",&e2);
#endif
#ifdef INT
  scanf("%d",&e2);
#endif
e1=Parent(T,e2);
if(e1!=Nil)
#ifdef CHAR
    printf("%c的双亲是%c\n",e2,e1);
#endif
#ifdef INT
    printf("%d的双亲是%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%c没有双亲\n",e2);
#endif
#ifdef INT
    printf("%d没有双亲\n",e2);
#endif
  e1=LeftChild(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c的左孩子是%c\n",e2,e1);
#endif
#ifdef INT
    printf("%d的左孩子是%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%c没有左孩子\n",e2);
#endif
#ifdef INT
    printf("%d没有左孩子\n",e2);
#endif
  e1=RightChild(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c的右孩子是%c\n",e2,e1);
#endif
#ifdef INT
    printf("%d的右孩子是%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%c没有右孩子\n",e2);
#endif
#ifdef INT
    printf("%d没有右孩子\n",e2);
#endif
  e1=LeftSibling(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c的左兄弟是%c\n",e2,e1);
#endif
#ifdef INT
    printf("%d的左兄弟是%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%c没有左兄弟\n",e2);
#endif
#ifdef INT
    printf("%d没有左兄弟\n",e2);
#endif
  e1=RightSibling(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c的右兄弟是%c\n",e2,e1);
#endif
#ifdef INT
    printf("%d的右兄弟是%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%c没有右兄弟\n",e2);
#endif
#ifdef INT
    printf("%d没有右兄弟\n",e2);
#endif
}
