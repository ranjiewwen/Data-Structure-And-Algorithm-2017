#include<stdio.h> /* EOF(=^Z或F6),NULL */
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
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
void LevelOrderTraverse(SqBiTree T,Status(*Visit)(TElemType))
{ /* 层序遍历二叉树 */
  int i=MAX_TREE_SIZE-1,j;
  while(T[i]==Nil)
    i--; /* 找到最后一个非空结点的序号 */
  for(j=0;j<=i;j++)  /* 从根结点起,按层序遍历二叉树 */
    if(T[j]!=Nil)
      Visit(T[j]); /* 只遍历非空的结点 */
  printf("\n");
}
 Status visit(TElemType e)
{
  printf("%d ",e);
  return OK;
}
void main()
{
  SqBiTree T;
  InitBiTree(T);
  CreateBiTree(T);
  printf("层序遍历二叉树:\n");
  LevelOrderTraverse(T,visit);
}
