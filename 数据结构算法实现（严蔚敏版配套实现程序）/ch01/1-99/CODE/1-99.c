#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
#define N 16 /* 数据元素个数 */
typedef struct
{
  int ord;
}Others; /* 记录的其它部分 */
#define Nil ' ' /* 定义结束符为空格(与教科书不同) */
#define MAXKEYLEN 16 /* 关键字的最大长度 */
typedef struct
{
  char ch[MAXKEYLEN]; /* 关键字 */
  int num; /* 关键字长度 */
}KeysType; /* 关键字类型 */
typedef struct
{
  KeysType key; /* 关键字 */
  Others others; /* 其它部分(由主程定义) */
}Record; /* 记录类型 */
typedef enum{LEAF,BRANCH}NodeKind; /* 结点种类:{叶子,分支} */
typedef struct DLTNode /* 双链树类型 */
{
  char symbol;
  struct DLTNode *next; /* 指向兄弟结点的指针 */
  NodeKind kind;
  union
  {
    Record *infoptr; /* 叶子结点的记录指针 */
    struct DLTNode *first; /* 分支结点的孩子链指针 */
  }a;
}DLTNode,*DLTree;
Status InitDSTable(DLTree *DT)
{ /* 操作结果: 构造一个空的双链键树DT */
  *DT=NULL;
  return OK;
}
void DestroyDSTable(DLTree *DT)
{ /* 初始条件: 双链键树DT存在。操作结果: 销毁双链键树DT */
  if(*DT) /* 非空树 */
  {
    if((*DT)->kind==BRANCH&&(*DT)->a.first) /* *DT是分支结点且有孩子 */
      DestroyDSTable(&(*DT)->a.first); /* 销毁孩子子树 */
    if((*DT)->next) /* 有兄弟 */
      DestroyDSTable(&(*DT)->next); /* 销毁兄弟子树 */
    free(*DT); /* 释放根结点 */
    *DT=NULL; /* 空指针赋0 */
  }
}
Record *SearchDLTree(DLTree T,KeysType K)
{ /* 在非空双链键树T中查找关键字等于K的记录，若存在， */
  /* 则返回指向该记录的指针，否则返回空指针。*/
  DLTree p;
  int i;
  if(T)
  {
    p=T; /* 初始化 */
    i=0;
    while(p&&i<K.num)
    {
      while(p&&p->symbol!=K.ch[i]) /* 查找关键字的第i位 */
        p=p->next;
      if(p&&i<K.num) /* 准备查找下一位 */
        p=p->a.first;
      ++i;
    } /* 查找结束 */
    if(!p) /* 查找不成功 */
      return NULL;
    else /* 查找成功 */
      return p->a.infoptr;
  }
  else
    return NULL; /* 树空 */
}
void InsertDSTable(DLTree *DT,Record *r)
{ /* 初始条件: 双链键树DT存在，r为待插入的数据元素的指针 */
  /* 操作结果: 若DT中不存在其关键字等于(*r).key.ch的数据元素， */
  /*           则按关键字顺序插r到DT中 */
  DLTree p=NULL,q,ap;
  int i=0;
  KeysType K=r->key;
  if(!*DT&&K.num) /* 空树且关键字符串非空 */
  {
    *DT=ap=(DLTree)malloc(sizeof(DLTNode));
    for(;i<K.num;i++) /* 插入分支结点 */
    {
      if(p)
        p->a.first=ap;
      ap->next=NULL;
      ap->symbol=K.ch[i];
      ap->kind=BRANCH;
      p=ap;
      ap=(DLTree)malloc(sizeof(DLTNode));
    }
    p->a.first=ap; /* 插入叶子结点 */
    ap->next=NULL;
    ap->symbol=Nil;
    ap->kind=LEAF;
    ap->a.infoptr=r;
  }
  else /* 非空树 */
  {
    p=*DT; /* 指向根结点 */
    while(p&&i<K.num)
    {
      while(p&&p->symbol<K.ch[i]) /* 沿兄弟结点查找 */
      {
        q=p;
        p=p->next;
      }
      if(p&&p->symbol==K.ch[i]) /* 找到与K.ch[i]相符的结点 */
      {
        q=p;
        p=p->a.first; /* p指向将与K.ch[i+1]比较的结点 */
        ++i;
      }
      else /* 没找到,插入关键字 */
      {
        ap=(DLTree)malloc(sizeof(DLTNode));
        if(q->a.first==p)
          q->a.first=ap; /* 在长子的位置插入 */
        else /* q->next==p */
          q->next=ap; /* 在兄弟的位置插入 */
        ap->next=p;
        ap->symbol=K.ch[i];
        ap->kind=BRANCH;
        p=ap;
        ap=(DLTree)malloc(sizeof(DLTNode));
        i++;
        for(;i<K.num;i++) /* 插入分支结点 */
        {
          p->a.first=ap;
          ap->next=NULL;
          ap->symbol=K.ch[i];
          ap->kind=BRANCH;
   p=ap;
          ap=(DLTree)malloc(sizeof(DLTNode));
        }
        p->a.first=ap; /* 插入叶子结点 */
        ap->next=NULL;
        ap->symbol=Nil;
        ap->kind=LEAF;
        ap->a.infoptr=r;
      }
    }
  }
}
typedef struct
{
  char ch;
  DLTree p;
}SElemType; /* 定义栈元素类型 */
#define STACK_INIT_SIZE 10 /* 存储空间初始分配量 */
#define STACKINCREMENT 2 /* 存储空间分配增量 */
typedef struct SqStack
{
  SElemType *base; /* 在栈构造之前和销毁之后，base的值为NULL */
  SElemType *top; /* 栈顶指针 */
  int stacksize; /* 当前已分配的存储空间，以元素为单位 */
}SqStack; /* 顺序栈 */
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
void TraverseDSTable(DLTree DT,void(*Vi)(Record))
{ /* 初始条件: 双链键树DT存在，Vi是对结点操作的应用函数， */
  /*           ViR是对记录操作的应用函数 */
  /* 操作结果: 按关键字的顺序输出关键字及其对应的记录 */
  SqStack s;
  SElemType e;
  DLTree p;
  int i=0,n=8;
  if(DT)
  {
    InitStack(&s);
    e.p=DT;
    e.ch=DT->symbol;
    Push(&s,e);
    p=DT->a.first;
    while(p->kind==BRANCH) /* 分支结点 */
    {
      e.p=p;
      e.ch=p->symbol;
      Push(&s,e);
      p=p->a.first;
    }
    e.p=p;
    e.ch=p->symbol;
    Push(&s,e);
    Vi(*(p->a.infoptr));
    i++;
    while(!StackEmpty(s))
    {
      Pop(&s,&e);
      p=e.p;
      if(p->next) /* 有兄弟结点 */
      {
        p=p->next;
        while(p->kind==BRANCH) /* 分支结点 */
        {
          e.p=p;
          e.ch=p->symbol;
          Push(&s,e);
          p=p->a.first;
        }
        e.p=p;
        e.ch=p->symbol;
        Push(&s,e);
        Vi(*(p->a.infoptr));
        i++;
        if(i%n==0)
          printf("\n"); /* 输出n个元素后换行 */
      }
    }
  }
}
void print(Record e)
{
  int i;
  printf("(");
  for(i=0;i<e.key.num;i++)
    printf("%c",e.key.ch[i]);
  printf(",%d)",e.others.ord);
}
void main()
{
  DLTree t;
  int i;
  char s[MAXKEYLEN+1];
  KeysType k;
  Record *p;
  Record r[N]={{{"CAI"},1},{{"CAO"},2},{{"LI"},3},{{"LAN"},4},
               {{"CHA"},5},{{"CHANG"},6},{{"WEN"},7},{{"CHAO"},8},
               {{"YUN"},9},{{"YANG"},10},{{"LONG"},11},{{"WANG"},12},
               {{"ZHAO"},13},{{"LIU"},14},{{"WU"},15},{{"CHEN"},16}};
  /* 数据元素(以教科书式9-24为例) */
  InitDSTable(&t);
  for(i=0;i<N;i++)
  {
    r[i].key.num=strlen(r[i].key.ch);
    p=SearchDLTree(t,r[i].key);
    if(!p) /* t中不存在关键字为r[i].key的项 */
      InsertDSTable(&t,&r[i]);
  }
  printf("按关键字符串的顺序遍历双链键树:\n");
  TraverseDSTable(t,print);
  printf("\n请输入待查找记录的关键字符串: ");
  scanf("%s",s);
  k.num=strlen(s);
  strcpy(k.ch,s);
  p=SearchDLTree(t,k);
  if(p)
    print(*p);
  else
    printf("没找到");
  printf("\n");
  DestroyDSTable(&t);
}
