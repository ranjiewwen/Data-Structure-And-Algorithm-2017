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
 TElemType Value(BiTree p)
{ /* 初始条件: 二叉树T存在，p指向T中某个结点 */
  /* 操作结果: 返回p所指结点的值 */
  return p->data;
}

void Assign(BiTree p,TElemType value)
{ /* 给p所指结点赋值为value */
  p->data=value;
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
Status InitQueue(LinkQueue *Q)
{ /* 构造一个空队列Q */
  (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
  if(!(*Q).front)
    exit(OVERFLOW);
  (*Q).front->next=NULL;
  return OK;
}
 Status QueueEmpty(LinkQueue Q)
{ /* 若Q为空队列,则返回TRUE,否则返回FALSE */
  if(Q.front==Q.rear)
    return TRUE;
  else
    return FALSE;
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

void LevelOrderTraverse(BiTree T,Status(*Visit)(TElemType))
{ /* 初始条件：二叉树T存在,Visit是对结点操作的应用函数 */
  /* 操作结果：层序递归遍历T(利用队列),对每个结点调用函数Visit一次且仅一次 */
  LinkQueue q;
  QElemType a;
  if(T)
  {
    InitQueue(&q);
    EnQueue(&q,T);
    while(!QueueEmpty(q))
    {
      DeQueue(&q,&a);
      Visit(a->data);
      if(a->lchild!=NULL)
        EnQueue(&q,a->lchild);
      if(a->rchild!=NULL)
        EnQueue(&q,a->rchild);
    }
    printf("\n");
  }
}
 Status visitT(TElemType e)
{
#ifdef CHAR
  printf("%c ",e);
#endif
#ifdef INT
  printf("%d ",e);
#endif
  return OK;
}
void main()
{
  BiTree T,p;
  TElemType e1,e2;
  InitBiTree(&T);
   #ifdef CHAR
  printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
#endif
#ifdef INT
  printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
#endif
  CreateBiTree(&T);
  printf("请输入一个结点的值: ");
#ifdef CHAR
  scanf("%*c%c",&e1);
#endif
#ifdef INT
  scanf("%d",&e1);
#endif
  p=Point(T,e1); /* p为e1的指针 */
#ifdef CHAR
  printf("结点的值为%c\n",Value(p));
#endif
#ifdef INT
  printf("结点的值为%d\n",Value(p));
#endif
  printf("欲改变此结点的值，请输入新值: ");
#ifdef CHAR
  scanf("%*c%c%*c",&e2);
#endif
#ifdef INT
  scanf("%d",&e2);
#endif
  Assign(p,e2);
  printf("层次遍历二叉树:\n");
  LevelOrderTraverse(T,visitT);
}
