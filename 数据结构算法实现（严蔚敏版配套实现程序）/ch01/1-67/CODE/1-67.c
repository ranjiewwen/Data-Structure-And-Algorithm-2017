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
void PostOrderTraverse(BiTree T,Status(*Visit)(TElemType))
{ /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
  /* 操作结果: 后序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
  if(T) /* T不空 */
  {
    PostOrderTraverse(T->lchild,Visit); /* 先后序遍历左子树 */
    PostOrderTraverse(T->rchild,Visit); /* 再后序遍历右子树 */
    Visit(T->data); /* 最后访问根结点 */
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
  BiTree T;
  InitBiTree(&T);
   #ifdef CHAR
  printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
#endif
#ifdef INT
  printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
#endif
  CreateBiTree(&T);
  printf("后序递归遍历二叉树:\n");
  PostOrderTraverse(T,visitT);
}
