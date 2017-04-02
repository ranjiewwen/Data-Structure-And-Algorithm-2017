#include<stdio.h> /* EOF(=^Z或F6),NULL */
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
 int BiTreeDepth(SqBiTree T)
{ /* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
  int i,j=-1;
  for(i=MAX_TREE_SIZE-1;i>=0;i--) /* 找到最后一个结点 */
    if(T[i]!=Nil)
      break;
  i++; /* 为了便于计算 */
  do
    j++;
  while(i>=pow(2,j));
  return j;
}
 TElemType Value(SqBiTree T,position e)
{ /* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
  /* 操作结果: 返回处于位置e(层,本层序号)的结点的值 */
  return T[(int)pow(2,e.level-1)+e.order-2];
}
 void Move(SqBiTree q,int j,SqBiTree T,int i) /* InsertChild()用到。加 */
{ /* 把从q的j结点开始的子树移为从T的i结点开始的子树 */
  if(q[2*j+1]!=Nil) /* q的左子树不空 */
    Move(q,(2*j+1),T,(2*i+1)); /* 把q的j结点的左子树移为T的i结点的左子树 */
  if(q[2*j+2]!=Nil) /* q的右子树不空 */
    Move(q,(2*j+2),T,(2*i+2)); /* 把q的j结点的右子树移为T的i结点的右子树 */
  T[i]=q[j]; /* 把q的j结点移为T的i结点 */
  q[j]=Nil; /* 把q的j结点置空 */
}
 Status InsertChild(SqBiTree T,TElemType p,Status LR,SqBiTree c)
{ /* 初始条件: 二叉树T存在,p是T中某个结点的值,LR为0或1,非空二叉树c与T */
  /*           不相交且右子树为空 */
  /* 操作结果: 根据LR为0或1,插入c为T中p结点的左或右子树。p结点的原有左或 */
  /*           右子树则成为c的右子树 */
  int j,k,i=0;
  for(j=0;j<(int)pow(2,BiTreeDepth(T))-1;j++) /* 查找p的序号 */
    if(T[j]==p) /* j为p的序号 */
      break;
  k=2*j+1+LR; /* k为p的左或右孩子的序号 */
  if(T[k]!=Nil) /* p原来的左或右孩子不空 */
    Move(T,k,T,2*k+2); /* 把从T的k结点开始的子树移为从k结点的右子树开始的子树 */
  Move(c,i,T,k); /* 把从c的i结点开始的子树移为从T的k结点开始的子树 */
  return OK;
}
void Print(SqBiTree T)
{ /* 逐层、按本层序号输出二叉树 */
  int j,k;
  position p;
  TElemType e;
  for(j=1;j<=BiTreeDepth(T);j++)
  {
    printf("第%d层: ",j);
    for(k=1;k<=pow(2,j-1);k++)
    {
      p.level=j;
      p.order=k;
      e=Value(T,p);
      if(e!=Nil)
        printf("%d:%d ",k,e);
    }
    printf("\n");
  }
}
void main()
{
  int j;
  TElemType e;
  SqBiTree T,s;
  InitBiTree(T);
  CreateBiTree(T);
  printf("建立右子树为空的树s:\n");
  CreateBiTree(s);
  printf("树s插到树T中,请输入树T中树s的双亲结点 s为左(0)或右(1)子树: ");
  scanf("%d%d",&e,&j);
  InsertChild(T,e,j,s);
  Print(T);
}
