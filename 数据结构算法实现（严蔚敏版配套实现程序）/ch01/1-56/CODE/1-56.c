 #define CHAR /* 字符型 */
 #include<stdio.h> /* EOF(=^Z或F6),NULL */
 #include<math.h> /* floor(),ceil(),abs() */
 #define TRUE 1
 #define FALSE 0
 #define OK 1
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

 Status BiTreeEmpty(BiTree T)
 { /* 初始条件: 二叉树T存在 */
   /* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
   if(T)
     return FALSE;
   else
     return TRUE;
 }

 int BiTreeDepth(BiTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
   int i,j;
   if(!T)
     return 0;
   if(T->lchild)
     i=BiTreeDepth(T->lchild);
   else
     i=0;
   if(T->rchild)
     j=BiTreeDepth(T->rchild);
   else
     j=0;
   return i>j?i+1:j+1;
 }

 TElemType Root(BiTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 返回T的根 */
   if(BiTreeEmpty(T))
     return Nil;
   else
     return T->data;
 }

 void main()
 {
   BiTree T;
   TElemType e1;
   InitBiTree(&T);
   printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("二叉树的根为: %c\n",e1);
 #endif
 #ifdef INT
     printf("二叉树的根为: %d\n",e1);
 #endif
   else
     printf("树空，无根\n");
 #ifdef CHAR
   printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
 #endif
 #ifdef INT
   printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
 #endif
   CreateBiTree(&T);
   printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("二叉树的根为: %c\n",e1);
 #endif
 #ifdef INT
     printf("二叉树的根为: %d\n",e1);
 #endif
   else
     printf("树空，无根\n");
 }

