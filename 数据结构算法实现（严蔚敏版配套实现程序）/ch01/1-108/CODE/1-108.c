#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
#define MAX_NAME 5 /* 顶点字符串的最大长度 */
typedef int InfoType;
typedef char VertexType[MAX_NAME]; /* 字符串类型 */
#define MAX_VERTEX_NUM 20
typedef enum{DG,DN,AG,AN}GraphKind; /* {有向图,有向网,无向图,无向网} */
typedef struct ArcNode
{
  int adjvex; /* 该弧所指向的顶点的位置 */
  struct ArcNode *nextarc; /* 指向下一条弧的指针 */
  InfoType *info; /* 网的权值指针） */
}ArcNode; /* 表结点 */
typedef struct
{
  VertexType data; /* 顶点信息 */
  ArcNode *firstarc; /* 第一个表结点的地址,指向第一条依附该顶点的弧的指针 */
}VNode,AdjList[MAX_VERTEX_NUM]; /* 头结点 */
typedef struct
{
  AdjList vertices;
  int vexnum,arcnum; /* 图的当前顶点数和弧数 */
  int kind; /* 图的种类标志 */
}ALGraph;
int LocateVex(ALGraph G,VertexType u)
{ /* 初始条件: 图G存在,u和G中顶点有相同特征 */
  /* 操作结果: 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
  int i;
  for(i=0;i<G.vexnum;++i)
    if(strcmp(u,G.vertices[i].data)==0)
      return i;
  return -1;
}
Status CreateGraph(ALGraph *G)
{ /* 采用邻接表存储结构,构造没有相关信息的图G(用一个函数构造4种图) */
  int i,j,k;
  int w; /* 权值 */
  VertexType va,vb;
  ArcNode *p;
  printf("请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
  scanf("%d",&(*G).kind);
  printf("请输入图的顶点数,边数: ");
  scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);
  printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
  for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
  {
    scanf("%s",(*G).vertices[i].data);
    (*G).vertices[i].firstarc=NULL;
  }
  if((*G).kind==1||(*G).kind==3) /* 网 */
    printf("请顺序输入每条弧(边)的权值、弧尾和弧头(以空格作为间隔):\n");
  else /* 图 */
    printf("请顺序输入每条弧(边)的弧尾和弧头(以空格作为间隔):\n");
  for(k=0;k<(*G).arcnum;++k) /* 构造表结点链表 */
  {
    if((*G).kind==1||(*G).kind==3) /* 网 */
      scanf("%d%s%s",&w,va,vb);
    else /* 图 */
      scanf("%s%s",va,vb);
    i=LocateVex(*G,va); /* 弧尾 */
    j=LocateVex(*G,vb); /* 弧头 */
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=j;
    if((*G).kind==1||(*G).kind==3) /* 网 */
    {
      p->info=(int *)malloc(sizeof(int));
      *(p->info)=w;
    }
    else
      p->info=NULL; /* 图 */
    p->nextarc=(*G).vertices[i].firstarc; /* 插在表头 */
    (*G).vertices[i].firstarc=p;
    if((*G).kind>=2) /* 无向图或网,产生第二个表结点 */
    {
      p=(ArcNode*)malloc(sizeof(ArcNode));
      p->adjvex=i;
      if((*G).kind==3) /* 无向网 */
      {
        p->info=(int*)malloc(sizeof(int));
        *(p->info)=w;
      }
      else
        p->info=NULL; /* 无向图 */
      p->nextarc=(*G).vertices[j].firstarc; /* 插在表头 */
      (*G).vertices[j].firstarc=p;
    }
  }
  return OK;
}
VertexType* GetVex(ALGraph G,int v)
{ /* 初始条件: 图G存在,v是G中某个顶点的序号。操作结果: 返回v的值 */
  if(v>=G.vexnum||v<0)
    exit(ERROR);
  return &G.vertices[v].data;
}
int FirstAdjVex(ALGraph G,VertexType v)
{ /* 初始条件: 图G存在,v是G中某个顶点 */
  /* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 */
  ArcNode *p;
  int v1;
  v1=LocateVex(G,v); /* v1为顶点v在图G中的序号 */
  p=G.vertices[v1].firstarc;
  if(p)
    return p->adjvex;
  else
    return -1;
}
int NextAdjVex(ALGraph G,VertexType v,VertexType w)
{ /* 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点 */
  /* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号。 */
  /*           若w是v的最后一个邻接点,则返回-1 */
  ArcNode *p;
  int v1,w1;
  v1=LocateVex(G,v); /* v1为顶点v在图G中的序号 */
  w1=LocateVex(G,w); /* w1为顶点w在图G中的序号 */
  p=G.vertices[v1].firstarc;
  while(p&&p->adjvex!=w1) /* 指针p不空且所指表结点不是w */
    p=p->nextarc;
  if(!p||!p->nextarc) /* 没找到w或w是最后一个邻接点 */
    return -1;
  else /* p->adjvex==w */
    return p->nextarc->adjvex; /* 返回v的(相对于w的)下一个邻接顶点的序号 */
}
Boolean visited[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */
void(*VisitFunc)(char* v); /* 函数变量(全局量) */
void DFS(ALGraph G,int v)
{ /* 从第v个顶点出发递归地深度优先遍历图G。*/
  int w;
  VertexType v1,w1;
  strcpy(v1,*GetVex(G,v));
  visited[v]=TRUE; /* 设置访问标志为TRUE(已访问) */
  VisitFunc(G.vertices[v].data); /* 访问第v个顶点 */
  for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,*GetVex(G,w))))
    if(!visited[w])
      DFS(G,w); /* 对v的尚未访问的邻接点w递归调用DFS */
}
typedef int QElemType; /* 队列类型 */
typedef struct QNode
{
  QElemType data;
  struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
  QueuePtr front,rear; /* 队头、队尾指针 */
}LinkQueue;
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
void BFSTraverse(ALGraph G,void(*Visit)(char*))
{/*按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited。算法7.6 */
  int v,u,w;
  VertexType u1,w1;
  LinkQueue Q;
  for(v=0;v<G.vexnum;++v)
    visited[v]=FALSE; /* 置初值 */
  InitQueue(&Q); /* 置空的辅助队列Q */
  for(v=0;v<G.vexnum;v++) /* 如果是连通图,只v=0就遍历全图 */
    if(!visited[v]) /* v尚未访问 */
    {
      visited[v]=TRUE;
      Visit(G.vertices[v].data);
      EnQueue(&Q,v); /* v入队列 */
      while(!QueueEmpty(Q)) /* 队列不空 */
      {
        DeQueue(&Q,&u); /* 队头元素出队并置为u */
        strcpy(u1,*GetVex(G,u));
        for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,*GetVex(G,w))))
          if(!visited[w]) /* w为u的尚未访问的邻接顶点 */
          {
            visited[w]=TRUE;
            Visit(G.vertices[w].data);
            EnQueue(&Q,w); /* w入队 */
          }
      }
    }
  printf("\n");
}

void Display(ALGraph G)
{ /* 输出图的邻接矩阵G */
  int i;
  ArcNode *p;
  switch(G.kind)
  {
    case DG: printf("有向图\n");
             break;
    case DN: printf("有向网\n");
             break;
    case AG: printf("无向图\n");
             break;
    case AN: printf("无向网\n");
  }
  printf("%d个顶点：\n",G.vexnum);
  for(i=0;i<G.vexnum;++i)
    printf("%s ",G.vertices[i].data);
  printf("\n%d条弧(边):\n",G.arcnum);
  for(i=0;i<G.vexnum;i++)
  {
    p=G.vertices[i].firstarc;
    while(p)
    {
      if(G.kind<=1) /* 有向 */
      {
        printf("%s→%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
        if(G.kind==DN) /* 网 */
          printf(":%d ",*(p->info));
      }
      else /* 无向(避免输出两次) */
      {
        if(i<p->adjvex)
        {
          printf("%s－%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
          if(G.kind==AN) /* 网 */
            printf(":%d ",*(p->info));
        }
      }
      p=p->nextarc;
    }
    printf("\n");
  }
}
void FindInDegree(ALGraph G,int indegree[])
{ /* 求顶点的入度*/
  int i;
  ArcNode *p;
  for(i=0;i<G.vexnum;i++)
    indegree[i]=0; /* 赋初值 */
  for(i=0;i<G.vexnum;i++)
  {
    p=G.vertices[i].firstarc;
    while(p)
    {
      indegree[p->adjvex]++;
      p=p->nextarc;
    }
  }
}
typedef int SElemType; /* 栈类型 */
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
Status TopologicalSort(ALGraph G)
{ /* 有向图G采用邻接表存储结构。若G无回路,则输出G的顶点的一个拓扑序列并返回OK, */
  /* 否则返回ERROR。*/
  int i,k,count,indegree[MAX_VERTEX_NUM];
  SqStack S;
  ArcNode *p;
  FindInDegree(G,indegree); /* 对各顶点求入度indegree[0..vernum-1] */
  InitStack(&S); /* 初始化栈 */
  for(i=0;i<G.vexnum;++i) /* 建零入度顶点栈S */
    if(!indegree[i])
      Push(&S,i); /* 入度为0者进栈 */
  count=0; /* 对输出顶点计数 */
  while(!StackEmpty(S))
  { /* 栈不空 */
    Pop(&S,&i);
    printf("%s ",G.vertices[i].data); /* 输出i号顶点并计数 */
    ++count;
    for(p=G.vertices[i].firstarc;p;p=p->nextarc)
    { /* 对i号顶点的每个邻接点的入度减1 */
      k=p->adjvex;
      if(!(--indegree[k])) /* 若入度减为0,则入栈 */
        Push(&S,k);
    }
  }
  if(count<G.vexnum)
  {
    printf("此有向图有回路\n");
    return ERROR;
  }
  else
  {
    printf("为一个拓扑序列。\n");
    return OK;
  }
}
void main()
{
  ALGraph f;
  printf("请选择有向图\n");
  CreateGraph(&f);
  Display(f);
  TopologicalSort(f);
}
