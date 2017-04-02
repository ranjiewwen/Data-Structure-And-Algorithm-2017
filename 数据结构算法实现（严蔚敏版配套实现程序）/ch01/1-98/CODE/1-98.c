#include<stdio.h> /* EOF(=^Z或F6),NULL */
/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
#define m 3 /* B树的阶，暂设为3 */
#define N 16 /* 数据元素个数 */
#define MAX 5 /* 字符串最大长度+1 */
typedef int KeyType; /* 设关键字域为整型 */
typedef struct
{
  char info[MAX];
}Others;/* 记录的其它部分 */
typedef struct
{
  KeyType key; /* 关键字 */
  Others others; /* 其它部分(由主程定义) */
}Record; /* 记录类型 */

typedef struct BTNode
{
  int keynum; /* 结点中关键字个数，即结点的大小 */
  struct BTNode *parent; /* 指向双亲结点 */
  struct Node /* 结点向量类型 */
  {
    KeyType key; /* 关键字向量 */
    struct BTNode *ptr; /* 子树指针向量 */
    Record *recptr; /* 记录指针向量 */
  }node[m+1]; /* key,recptr的0号单元未用 */
}BTNode,*BTree; /* B树结点和B树的类型 */

typedef struct
{
  BTNode *pt; /* 指向找到的结点 */
  int i; /* 1..m，在结点中的关键字序号 */
  int tag; /* 1:查找成功，O:查找失败 */
}Result; /* B树的查找结果类型 */
Status InitDSTable(BTree *DT)
{ /* 操作结果: 构造一个空的动态查找表DT */
  *DT=NULL;
  return OK;
}

void DestroyDSTable(BTree *DT)
{ /* 初始条件: 动态查找表DT存在。操作结果: 销毁动态查找表DT */
  int i;
  if(*DT) /* 非空树 */
  {
    for(i=0;i<=(*DT)->keynum;i++)
      DestroyDSTable(&(*DT)->node[i].ptr); /* 依次销毁第i棵子树 */
    free(*DT); /* 释放根结点 */
    *DT=NULL; /* 空指针赋0 */
  }
}
int Search(BTree p, KeyType K)
{ /* 在p->node[1..keynum].key中查找i,使得p->node[i].key≤K＜p->node[i+1].key */
  int i=0,j;
  for(j=1;j<=p->keynum;j++)
    if(p->node[j].key<=K)
      i=j;
  return i;
}
Result SearchBTree(BTree T, KeyType K)
{ /* 在m阶B树T上查找关键字K，返回结果(pt,i,tag)。若查找成功，则特征值 */
  /* tag=1，指针pt所指结点中第i个关键字等于K；否则特征值tag=0，等于K的 */
  /* 关键字应插入在指针Pt所指结点中第i和第i+1个关键字之间。*/
  BTree p=T,q=NULL; /* 初始化，p指向待查结点，q指向p的双亲 */
  Status found=FALSE;
  int i=0;
  Result r;
  while(p&&!found)
  {
    i=Search(p,K); /* p->node[i].key≤K<p->node[i+1].key */
    if(i>0&&p->node[i].key==K) /* 找到待查关键字 */
      found=TRUE;
    else
    {
      q=p;
      p=p->node[i].ptr;
    }
  }
  r.i=i;
  if(found) /* 查找成功 */
  {
    r.pt=p;
    r.tag=1;
  }
  else /*  查找不成功，返回K的插入位置信息 */
  {
    r.pt=q;
    r.tag=0;
  }
  return r;
}
void Insert(BTree *q,int i,Record *r,BTree ap)
{ /* 将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中 */
  int j;
  for(j=(*q)->keynum;j>i;j--) /* 空出q->node[i+1] */
    (*q)->node[j+1]=(*q)->node[j];
  (*q)->node[i+1].key=r->key;
  (*q)->node[i+1].ptr=ap;
  (*q)->node[i+1].recptr=r;
  (*q)->keynum++;
}
void split(BTree *q,BTree *ap)
{ /* 将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap */
  int i,s=(m+1)/2;
  *ap=(BTree)malloc(sizeof(BTNode)); /* 生成新结点ap */
  (*ap)->node[0].ptr=(*q)->node[s].ptr; /* 后一半移入ap */
  for(i=s+1;i<=m;i++)
  {
    (*ap)->node[i-s]=(*q)->node[i];
    if((*ap)->node[i-s].ptr)
      (*ap)->node[i-s].ptr->parent=*ap;
  }
  (*ap)->keynum=m-s;
  (*ap)->parent=(*q)->parent;
  (*q)->keynum=s-1; /* q的前一半保留，修改keynum */
}
void NewRoot(BTree *T,Record *r,BTree ap)
{ /* 生成含信息(T,r,ap)的新的根结点*T，原T和ap为子树指针 */
  BTree p;
  p=(BTree)malloc(sizeof(BTNode));
  p->node[0].ptr=*T;
  *T=p;
  if((*T)->node[0].ptr)
    (*T)->node[0].ptr->parent=*T;
  (*T)->parent=NULL;
  (*T)->keynum=1;
  (*T)->node[1].key=r->key;
  (*T)->node[1].recptr=r;
  (*T)->node[1].ptr=ap;
  if((*T)->node[1].ptr)
    (*T)->node[1].ptr->parent=*T;
}
void InsertBTree(BTree *T,Record *r,BTree q,int i)
{ /* 在m阶B树T上结点*q的key[i]与key[i+1]之间插入关键字K的指针r。若引起 */
  /* 结点过大,则沿双亲链进行必要的结点分裂调整,使T仍是m阶B树。*/
  BTree ap=NULL;
  Status finished=FALSE;
  int s;
  Record *rx;
  rx=r;
  while(q&&!finished)
  {
    Insert(&q,i,rx,ap); /* 将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中 */
    if(q->keynum<m)
      finished=TRUE; /* 插入完成 */
    else
    { /* 分裂结点*q */
      s=(m+1)/2;
      rx=q->node[s].recptr;
      split(&q,&ap); /* 将q->key[s+1..m],q->ptr[s..m]和q->recptr[s+1..m]移入新结点*ap */
      q=q->parent;
      if(q)
        i=Search(q,rx->key); /* 在双亲结点*q中查找rx->key的插入位置 */
    }
  }
  if(!finished) /* T是空树(参数q初值为NULL)或根结点已分裂为结点*q和*ap */
    NewRoot(T,rx,ap); /* 生成含信息(T,rx,ap)的新的根结点*T，原T和ap为子树指针 */
}
void TraverseDSTable(BTree DT,void(*Visit)(BTNode,int))
{ /* 初始条件: 动态查找表DT存在，Visit是对结点操作的应用函数 */
  /* 操作结果: 按关键字的顺序对DT的每个结点调用函数Visit()一次且至多一次 */
  int i;
  if(DT) /* 非空树 */
  {
    if(DT->node[0].ptr) /* 有第0棵子树 */
      TraverseDSTable(DT->node[0].ptr,Visit);
    for(i=1;i<=DT->keynum;i++)
    {
      Visit(*DT,i);
      if(DT->node[i].ptr) /* 有第i棵子树 */
 TraverseDSTable(DT->node[i].ptr,Visit);
    }
  }
}
void print(BTNode c,int i) /* TraverseDSTable()调用的函数 */
{
  printf("(%d,%s)",c.node[i].key,c.node[i].recptr->others.info);
}
void main()
{
  Record r[N]={{24,"1"},{45,"2"},{53,"3"},{12,"4"},{37,"5"},
               {50,"6"},{61,"7"},{90,"8"},{100,"9"},{70,"10"},
               {3,"11"},{30,"12"},{26,"13"},{85,"14"},{3,"15"},
	{7,"16"}}; /* (以教科书中图9.16为例) */
  BTree t;
  Result s;
  int i;
  InitDSTable(&t);
  for(i=0;i<N;i++)
  {
    s=SearchBTree(t,r[i].key);
    if(!s.tag)
      InsertBTree(&t,&r[i],s.pt,s.i);
  }
  printf("按关键字的顺序遍历B_树:\n");
  TraverseDSTable(t,print);
  printf("\n请输入待查找记录的关键字: ");
  scanf("%d",&i);
  s=SearchBTree(t,i);
  if(s.tag)
    print(*(s.pt),s.i);
  else
    printf("没找到");
  printf("\n");
  DestroyDSTable(&t);
}
