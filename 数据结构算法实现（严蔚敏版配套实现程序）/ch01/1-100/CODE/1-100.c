#include<stdio.h> /* EOF(=^Z或F6),NULL */
#define OK 1
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
#define N 16 /* 数据元素个数 */
#define LENGTH 27 /* 结点的最大度+1(大写英文字母) */
typedef struct
{
  int ord;
}Others; /* 记录的其它部分 */
#define Nil ' ' /* 定义结束符为空格(与教科书不同) */
#define MAXKEYLEN 16 /* 关键字的最大长度，同c9-4.h */
typedef struct
{
  char ch[MAXKEYLEN]; /* 关键字 */
  int num; /* 关键字长度 */
}KeysType; 
typedef struct
{
  KeysType key; /* 关键字 */
  Others others; /* 其它部分(由主程定义) */
}Record; 
typedef enum{LEAF,BRANCH}NodeKind; 
typedef struct TrieNode /* Trie键树类型 */
{
  NodeKind kind;
  union
  {
    struct /* 叶子结点 */
    {
      KeysType K;
      Record *infoptr;
    }lf;
    struct /* 分支结点 */
    {
      struct TrieNode *ptr[LENGTH]; /* LENGTH为结点的最大度+1,在主程定义 */
    /*  int num; 改 */
    }bh;
  }a;
}TrieNode,*TrieTree;
#define EQ(a,b) (!strcmp((a),(b)))
Status InitDSTable(TrieTree *T)
{ /* 操作结果: 构造一个空的Trie键树T */
  *T=NULL;
  return OK;
}
void DestroyDSTable(TrieTree *T)
{ /* 初始条件: Trie树T存在。操作结果: 销毁Trie树T */
  int i;
  if(*T) /* 非空树 */
  {
    for(i=0;i<LENGTH;i++)
      if((*T)->kind==BRANCH&&(*T)->a.bh.ptr[i]) /* 第i个结点不空 */
        if((*T)->a.bh.ptr[i]->kind==BRANCH) /* 是子树 */
          DestroyDSTable(&(*T)->a.bh.ptr[i]);
        else /* 是叶子 */
        {
          free((*T)->a.bh.ptr[i]);
          (*T)->a.bh.ptr[i]=NULL;
        }
    free(*T); /* 释放根结点 */
    *T=NULL; /* 空指针赋0 */
  }
}
int ord(char c)
{
  c=toupper(c);
  if(c>='A'&&c<='Z')
    return c-'A'+1; /* 英文字母返回其在字母表中的序号 */
  else
    return 0; /* 其余字符返回0 */
}
Record *SearchTrie(TrieTree T,KeysType K)
{ /* 在键树T中查找关键字等于K的记录。*/
  TrieTree p;
  int i;
  for(p=T,i=0;p&&p->kind==BRANCH&&i<K.num;p=p->a.bh.ptr[ord(K.ch[i])],++i);
  /* 对K的每个字符逐个查找,*p为分支结点,ord()求字符在字母表中序号 */
  if(p&&p->kind==LEAF&&p->a.lf.K.num==K.num&&EQ(p->a.lf.K.ch,K.ch)) /* 查找成功 */
    return p->a.lf.infoptr;
  else /* 查找不成功 */
    return NULL;
}
void InsertTrie(TrieTree *T,Record *r)
{ /* 初始条件: Trie键树T存在，r为待插入的数据元素的指针 */
  /* 操作结果: 若T中不存在其关键字等于(*r).key.ch的数据元素， */
  /*           则按关键字顺序插r到T中 */
  TrieTree p,q,ap;
  int i=0,j;
  KeysType K1,K=r->key;
  if(!*T) /* 空树 */
  {
    *T=(TrieTree)malloc(sizeof(TrieNode));
    (*T)->kind=BRANCH;
    for(i=0;i<LENGTH;i++) /* 指针量赋初值NULL */
      (*T)->a.bh.ptr[i]=NULL;
    p=(*T)->a.bh.ptr[ord(K.ch[0])]=(TrieTree)malloc(sizeof(TrieNode));
    p->kind=LEAF;
    p->a.lf.K=K;
    p->a.lf.infoptr=r;
  }
  else /* 非空树 */
  {
    for(p=*T,i=0;p&&p->kind==BRANCH&&i<K.num;++i)
    {
      q=p;
      p=p->a.bh.ptr[ord(K.ch[i])];
    }
    i--;
    if(p&&p->kind==LEAF&&p->a.lf.K.num==K.num&&EQ(p->a.lf.K.ch,K.ch)) /* T中存在该关键字 */
      return;
    else /* T中不存在该关键字,插入之 */
    {
      if(!p) /* 分支空 */
      {
        p=q->a.bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
        p->kind=LEAF;
        p->a.lf.K=K;
        p->a.lf.infoptr=r;
      }
      else if(p->kind==LEAF) /* 有不完全相同的叶子 */
      {
        K1=p->a.lf.K;
        do
       {
          ap=q->a.bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
          ap->kind=BRANCH;
          for(j=0;j<LENGTH;j++) /* 指针量赋初值NULL */
            ap->a.bh.ptr[j]=NULL;
          q=ap;
          i++;
        }while(ord(K.ch[i])==ord(K1.ch[i]));
        q->a.bh.ptr[ord(K1.ch[i])]=p;
        p=q->a.bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
        p->kind=LEAF;
        p->a.lf.K=K;
        p->a.lf.infoptr=r;
      }
    }
  }
}
void TraverseDSTable(TrieTree T,Status(*Vi)(Record*))
{ /* 初始条件: Trie键树T存在，Vi是对记录指针操作的应用函数 */
  /* 操作结果: 按关键字的顺序输出关键字及其对应的记录 */
  TrieTree p;
  int i;
  if(T)
  {
    for(i=0;i<LENGTH;i++)
    {
      p=T->a.bh.ptr[i];
      if(p&&p->kind==LEAF)
        Vi(p->a.lf.infoptr);
      else if(p&&p->kind==BRANCH)
        TraverseDSTable(p,Vi);
    }
  }
}
Status pr(Record *r)
{
  printf("(%s,%d)",r->key.ch,r->others.ord);
  return OK;
}
void main()
{
  TrieTree t;
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
    r[i].key.num=strlen(r[i].key.ch)+1;
    r[i].key.ch[r[i].key.num]=Nil; /* 在关键字符串最后加结束符 */
    p=SearchTrie(t,r[i].key);
    if(!p)
      InsertTrie(&t,&r[i]);
  }
  printf("按关键字符串的顺序遍历Trie树(键树):\n");
  TraverseDSTable(t,pr);
  printf("\n请输入待查找记录的关键字符串: ");
  scanf("%s",s);
  k.num=strlen(s)+1;
  strcpy(k.ch,s);
  k.ch[k.num]=Nil; /* 在关键字符串最后加结束符 */
  p=SearchTrie(t,k);
  if(p)
    pr(p);
  else
    printf("没找到");
  printf("\n");
  DestroyDSTable(&t);
}
