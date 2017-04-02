#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
/* #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3,故去掉此行 */
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
#define MAX_NAME 2 /* 顶点字符串的最大长度+1 */
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
{/*按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited。*/
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
int count; /* 全局量count对访问计数 */
int low[MAX_VERTEX_NUM];
void DFSArticul(ALGraph G,int v0)
{ /* 从第v0个顶点出发深度优先遍历图G，查找并输出关节点。*/
  int min,w;
  ArcNode *p;
  visited[v0]=min=++count; /* v0是第count个访问的顶点 */
  for(p=G.vertices[v0].firstarc;p;p=p->nextarc) /* 对v0的每个邻接顶点检查 */
  {
    w=p->adjvex; /* w为v0的邻接顶点 */
    if(visited[w]==0) /* w未曾访问，是v0的孩子 */
    {
      DFSArticul(G,w); /* 返回前求得low[w] */
      if(low[w]<min)
        min=low[w];
      if(low[w]>=visited[v0])
        printf("%d %s\n",v0,G.vertices[v0].data); /* 关节点 */
    }
    else if(visited[w]<min)
      min=visited[w]; /* w已访问，w是v0在生成树上的祖先 */
  }
  low[v0]=min;
}
void FindArticul(ALGraph G)
{ /* 连通图G以邻接表作存储结构，查找并输出G上全部关节点。*/
  /* 全局量count对访问计数。 */
  int i,v;
  ArcNode *p;
  count=1;
  low[0]=visited[0]=1; /* 设定邻接表上0号顶点为生成树的根 */
  for(i=1;i<G.vexnum;++i)
    visited[i]=0; /* 其余顶点尚未访问 */
  p=G.vertices[0].firstarc;
  v=p->adjvex;
  DFSArticul(G,v); /* 从第v顶点出发深度优先查找关节点 */
  if(count<G.vexnum) /* 生成树的根有至少两棵子树 */
  {
    printf("%d %s\n",0,G.vertices[0].data); /* 根是关节点，输出 */
    while(p->nextarc)
    {
      p=p->nextarc;
      v=p->adjvex;
      if(visited[v]==0)
        DFSArticul(G,v);
    }
  }
}
void main()
{
  int i;
  ALGraph g;
  printf("请选择无向图\n");
  CreateGraph(&g);
  printf("输出关节点：\n");
  FindArticul(g);
  printf(" i G.vertices[i].data visited[i] low[i]\n");
  for(i=0;i<g.vexnum;++i)
    printf("%2d %9s %14d %8d\n",i,g.vertices[i].data,visited[i],low[i]);
}
