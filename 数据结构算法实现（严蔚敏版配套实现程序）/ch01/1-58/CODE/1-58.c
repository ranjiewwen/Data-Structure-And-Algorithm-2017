#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
#if CHAR
  typedef char TElemType;
  TElemType Nil=' '; /* 设字符型以空格符为空 */
#else
  typedef int TElemType;
  TElemType Nil=0; /* 设整型以0为空 */
#endif
#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */
typedef TElemType SqBiTree[MAX_TREE_SIZE]; /* 0号单元存储根结点 */
typedef struct
{
  int level,order; /* 结点的层,本层序号(按满二叉树计算) */
}position;
/* bo6-1.c 二叉树的顺序存储(存储结构由c6-1.h定义)的基本操作(23个) */
Status InitBiTree(SqBiTree T)
{ /* 构造空二叉树T。因为T是固定数组，不会改变，故不需要& */
  int i;
  for(i=0;i<MAX_TREE_SIZE;i++)
    T[i]=Nil; /* 初值为空 */
  return OK;
}
Status CreateBiTree(SqBiTree T)
{ /* 按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T */
  int i=0;
#if CHAR
  int l;
  char s[MAX_TREE_SIZE];
  printf("请按层序输入结点的值(字符)，空格表示空结点，结点数≤%d:\n",MAX_TREE_SIZE);
  gets(s); /* 输入字符串 */
  l=strlen(s); /* 求字符串的长度 */
  for(;i<l;i++) /* 将字符串赋值给T */
  {
    T[i]=s[i];
    if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil) /* 此结点(不空)无双亲且不是根 */
    {
      printf("出现无双亲的非根结点%c\n",T[i]);
      exit(ERROR);
    }
  }
  for(i=l;i<MAX_TREE_SIZE;i++) /* 将空赋值给T的后面的结点 */
    T[i]=Nil;
#else
  printf("请按层序输入结点的值(整型)，0表示空结点，输999结束。结点数≤%d:\n",MAX_TREE_SIZE);
  while(1)
  {
    scanf("%d",&T[i]);
    if(T[i]==999)
      break;
    if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil) /* 此结点(不空)无双亲且不是根 */
    {
      printf("出现无双亲的非根结点%d\n",T[i]);
      exit(ERROR);
    }
    i++;
  }
  while(i<MAX_TREE_SIZE)
  {
    T[i]=Nil; /* 将空赋值给T的后面的结点 */
    i++;
  }
#endif
  return OK;
}
Status BiTreeEmpty(SqBiTree T)
{ /* 初始条件: 二叉树T存在 */
  /* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
  if(T[0]==Nil) /* 根结点为空,则树空 */
    return TRUE;
  else
    return FALSE;
}
TElemType Value(SqBiTree T,position e)
{ /* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
  /* 操作结果: 返回处于位置e(层,本层序号)的结点的值 */
  return T[(int)pow(2,e.level-1)+e.order-2];
}
Status Assign(SqBiTree T,position e,TElemType value)
{ /* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
  /* 操作结果: 给处于位置e(层,本层序号)的结点赋新值value */
  int i=(int)pow(2,e.level-1)+e.order-2; /* 将层、本层序号转为矩阵的序号 */
  if(value!=Nil&&T[(i+1)/2-1]==Nil) /* 给叶子赋非空值但双亲为空 */
    return ERROR;
  else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil)) /*  给双亲赋空值但有叶子（不空） */
    return ERROR;
  T[i]=value;
  return OK;
}
Status(*VisitFunc)(TElemType); /* 函数变量 */
void PreTraverse(SqBiTree T,int e)
{ /* PreOrderTraverse()调用 */
  VisitFunc(T[e]);
  if(T[2*e+1]!=Nil) /* 左子树不空 */
    PreTraverse(T,2*e+1);
  if(T[2*e+2]!=Nil) /* 右子树不空 */
    PreTraverse(T,2*e+2);
}
Status PreOrderTraverse(SqBiTree T,Status(*Visit)(TElemType))
{ /* 初始条件: 二叉树存在,Visit是对结点操作的应用函数 */
  /* 操作结果: 先序遍历T,对每个结点调用函数Visit一次且仅一次。 */
  /*           一旦Visit()失败,则操作失败 */
  VisitFunc=Visit;
  if(!BiTreeEmpty(T)) /* 树不空 */
    PreTraverse(T,0);
  printf("\n");
  return OK;
}
Status visit(TElemType e)
{
  printf("%d ",e);
  return OK;
}
void main()
{
  Status i;
  position p;
  TElemType e;
  SqBiTree T;
  InitBiTree(T);
  CreateBiTree(T);
  printf("请输入待修改结点的层号 本层序号: ");
  scanf("%d%d",&p.level,&p.order);
  e=Value(T,p);
  printf("待修改结点的原值为%d请输入新值: ",e);
  scanf("%d",&e);
  Assign(T,p,e);
  printf("先序遍历二叉树:\n");
  PreOrderTraverse(T,visit);
}
