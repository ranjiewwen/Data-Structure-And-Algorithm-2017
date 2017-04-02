#define CHAR /* 字符型 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 10 /* 存储空间初始分配量 */
#define STACKINCREMENT 2 /* 存储空间分配增量 */
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
typedef BiTree SElemType; /* 设栈元素为二叉树的指针类型 */

typedef struct SqStack
{
  SElemType *base; /* 在栈构造之前和销毁之后，base的值为NULL */
  SElemType *top; /* 栈顶指针 */
  int stacksize; /* 当前已分配的存储空间，以元素为单位 */
}SqStack; /* 顺序栈 */
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
Status InitStack(SqStack *S)
{ /* 构造一个空栈S */
  (*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
  if(!(*S).base)
    exit(OVERFLOW); /* 存储分配失败 */
  (*S).top=(*S).base;
  (*S).stacksize=STACK_INIT_SIZE;
  return OK;
}
Status StackEmpty(SqStack S)
{ /* 若栈S为空栈，则返回TRUE，否则返回FALSE */
  if(S.top==S.base)
    return TRUE;
  else
    return FALSE;
}
Status Push(SqStack *S,SElemType e)
{ /* 插入元素e为新的栈顶元素 */
  if((*S).top-(*S).base>=(*S).stacksize) /* 栈满，追加存储空间 */
  {
    (*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
    if(!(*S).base)
      exit(OVERFLOW); /* 存储分配失败 */
    (*S).top=(*S).base+(*S).stacksize;
    (*S).stacksize+=STACKINCREMENT;
  }
  *((*S).top)++=e;
  return OK;
}
Status Pop(SqStack *S,SElemType *e)
{ /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
  if((*S).top==(*S).base)
    return ERROR;
  *e=*--(*S).top;
  return OK;
}
Status InOrderTraverse1(BiTree T,Status(*Visit)(TElemType))
{ /* 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。*/
  /* 中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数Visit */
  SqStack S;
  InitStack(&S);
  while(T||!StackEmpty(S))
  {
    if(T)
    { /* 根指针进栈,遍历左子树 */
      Push(&S,T);
      T=T->lchild;
    }
    else
    { /* 根指针退栈,访问根结点,遍历右子树 */
      Pop(&S,&T);
      if(!Visit(T->data))
        return ERROR;
      T=T->rchild;
    }
  }
  printf("\n");
  return OK;
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
  BiTree T;
  InitBiTree(&T);
   #ifdef CHAR
  printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
#endif
#ifdef INT
  printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
#endif
  CreateBiTree(&T);
  printf("中序非递归遍历二叉树:\n");
  InOrderTraverse1(T,visitT);
}
