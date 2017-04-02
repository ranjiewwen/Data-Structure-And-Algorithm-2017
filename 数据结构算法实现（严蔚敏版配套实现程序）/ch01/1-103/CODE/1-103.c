#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
#define MAX_NAME 3 /* 顶点字符串的最大长度+1 */
typedef int InfoType; /* 存放网的权值 */
typedef char VertexType[MAX_NAME]; /* 字符串类型 */
/*图的邻接表存储表示 */
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
/* 图的邻接表存储的基本操作*/
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
{ /* 采用邻接表存储结构,构造没有相关信息的图G*/
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
void DestroyGraph(ALGraph *G)
{ /* 初始条件: 图G存在。操作结果: 销毁图G */
  int i;
  ArcNode *p,*q;
  (*G).vexnum=0;
  (*G).arcnum=0;
  for(i=0;i<(*G).vexnum;++i)
  {
    p=(*G).vertices[i].firstarc;
    while(p)
    {
      q=p->nextarc;
      if((*G).kind%2) /* 网 */
        free(p->info);
      free(p);
      p=q;
    }
  }
}
VertexType* GetVex(ALGraph G,int v)
{ /* 初始条件: 图G存在,v是G中某个顶点的序号。操作结果: 返回v的值 */
  if(v>=G.vexnum||v<0)
    exit(ERROR);
  return &G.vertices[v].data;
}
Status PutVex(ALGraph *G,VertexType v,VertexType value)
{ /* 初始条件: 图G存在,v是G中某个顶点 */
  /* 操作结果: 对v赋新值value */
  int i;
  i=LocateVex(*G,v);
  if(i>-1) /* v是G的顶点 */
  {
    strcpy((*G).vertices[i].data,value);
    return OK;
  }
  return ERROR;
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
void InsertVex(ALGraph *G,VertexType v)
{ /* 初始条件: 图G存在,v和图中顶点有相同特征 */
  /* 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
  strcpy((*G).vertices[(*G).vexnum].data,v); /* 构造新顶点向量 */
  (*G).vertices[(*G).vexnum].firstarc=NULL;
  (*G).vexnum++; /* 图G的顶点数加1 */
}
Status DeleteVex(ALGraph *G,VertexType v)
{ /* 初始条件: 图G存在,v是G中某个顶点 */
  /* 操作结果: 删除G中顶点v及其相关的弧 */
  int i,j;
  ArcNode *p,*q;
  j=LocateVex(*G,v); /* j是顶点v的序号 */
  if(j<0) /* v不是图G的顶点 */
    return ERROR;
  p=(*G).vertices[j].firstarc; /* 删除以v为出度的弧或边 */
  while(p)
  {
    q=p;
    p=p->nextarc;
    if((*G).kind%2) /* 网 */
      free(q->info);
    free(q);
    (*G).arcnum--; /* 弧或边数减1 */
  }
  (*G).vexnum--; /* 顶点数减1 */
  for(i=j;i<(*G).vexnum;i++) /* 顶点v后面的顶点前移 */
    (*G).vertices[i]=(*G).vertices[i+1];
  for(i=0;i<(*G).vexnum;i++) /* 删除以v为入度的弧或边且必要时修改表结点的顶点位置值 */
  {
    p=(*G).vertices[i].firstarc; /* 指向第1条弧或边 */
    while(p) /* 有弧 */
    {
      if(p->adjvex==j)
      {
        if(p==(*G).vertices[i].firstarc) /* 待删结点是第1个结点 */
        {
          (*G).vertices[i].firstarc=p->nextarc;
          if((*G).kind%2) /* 网 */
            free(p->info);
          free(p);
          p=(*G).vertices[i].firstarc;
          if((*G).kind<2) /* 有向 */
            (*G).arcnum--; /* 弧或边数减1 */
        }
        else
        {
          q->nextarc=p->nextarc;
          if((*G).kind%2) /* 网 */
            free(p->info);
          free(p);
          p=q->nextarc;
          if((*G).kind<2) /* 有向 */
            (*G).arcnum--; /* 弧或边数减1 */
        }
      }
      else
      {
        if(p->adjvex>j)
          p->adjvex--; /* 修改表结点的顶点位置值(序号) */
        q=p;
        p=p->nextarc;
      }
    }
  }
  return OK;
}
Status InsertArc(ALGraph *G,VertexType v,VertexType w)
{ /* 初始条件: 图G存在,v和w是G中两个顶点 */
  /* 操作结果: 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v> */
  ArcNode *p;
  int w1,i,j;
  i=LocateVex(*G,v); /* 弧尾或边的序号 */
  j=LocateVex(*G,w); /* 弧头或边的序号 */
  if(i<0||j<0)
    return ERROR;
  (*G).arcnum++; /* 图G的弧或边的数目加1 */
  if((*G).kind%2) /* 网 */
  {
    printf("请输入弧(边)%s→%s的权值: ",v,w);
    scanf("%d",&w1);
  }
  p=(ArcNode*)malloc(sizeof(ArcNode));
  p->adjvex=j;
  if((*G).kind%2) /* 网 */
  {
    p->info=(int*)malloc(sizeof(int));
    *(p->info)=w1;
  }
  else
    p->info=NULL;
  p->nextarc=(*G).vertices[i].firstarc; /* 插在表头 */
  (*G).vertices[i].firstarc=p;
  if((*G).kind>=2) /* 无向,生成另一个表结点 */
  {
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=i;
    if((*G).kind==3) /* 无向网 */
    {
      p->info=(int*)malloc(sizeof(int));
      *(p->info)=w1;
    }
    else
      p->info=NULL;
    p->nextarc=(*G).vertices[j].firstarc; /* 插在表头 */
    (*G).vertices[j].firstarc=p;
  }
  return OK;
}
Status DeleteArc(ALGraph *G,VertexType v,VertexType w)
{ /* 初始条件: 图G存在,v和w是G中两个顶点 */
  /* 操作结果: 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v> */
  ArcNode *p,*q;
  int i,j;
  i=LocateVex(*G,v); /* i是顶点v(弧尾)的序号 */
  j=LocateVex(*G,w); /* j是顶点w(弧头)的序号 */
  if(i<0||j<0||i==j)
    return ERROR;
  p=(*G).vertices[i].firstarc; /* p指向顶点v的第一条出弧 */
  while(p&&p->adjvex!=j) /* p不空且所指之弧不是待删除弧<v,w> */
  { /* p指向下一条弧 */
    q=p;
    p=p->nextarc;
  }
  if(p&&p->adjvex==j) /* 找到弧<v,w> */
  {
    if(p==(*G).vertices[i].firstarc) /* p所指是第1条弧 */
      (*G).vertices[i].firstarc=p->nextarc; /* 指向下一条弧 */
    else
      q->nextarc=p->nextarc; /* 指向下一条弧 */
    if((*G).kind%2) /* 网 */
      free(p->info);
    free(p); /* 释放此结点 */
    (*G).arcnum--; /* 弧或边数减1 */
  }
  if((*G).kind>=2) /* 无向,删除对称弧<w,v> */
  {
    p=(*G).vertices[j].firstarc; /* p指隙サ鉾的第一条出弧 */
    while(p&&p->adjvex!=i) /* p不空且所指之弧不是待删除弧<w,v> */
    { /* p指向下一条弧 */
      q=p;
      p=p->nextarc;
    }
    if(p&&p->adjvex==i) /* 找到弧<w,v> */
    {
      if(p==(*G).vertices[j].firstarc) /* p所指是第1条弧 */
        (*G).vertices[j].firstarc=p->nextarc; /* 指向下一条弧 */
      else
        q->nextarc=p->nextarc; /* 指向下一条弧 */
      if((*G).kind==3) /* 无向网 */
        free(p->info);
      free(p); /* 释放此结点 */
    }
  }
  return OK;
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
void DFSTraverse(ALGraph G,void(*Visit)(char*))
{ /* 对图G作深度优先遍历。*/
  int v;
  VisitFunc=Visit; /* 使用全局变量VisitFunc,使DFS不必设函数指针参数 */
  for(v=0;v<G.vexnum;v++)
    visited[v]=FALSE; /* 访问标志数组初始化 */
  for(v=0;v<G.vexnum;v++)
    if(!visited[v])
      DFS(G,v); /* 对尚未访问的顶点调用DFS */
  printf("\n");
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
void print(char *i)
{
  printf("%s ",i);
}
void main()
{
  int i,j,k,n;
  ALGraph g;
  VertexType v1,v2;
  printf("请选择有向图\n");
  CreateGraph(&g);
  Display(g);
  printf("删除一条边或弧，请输入待删除边或弧的弧尾 弧头：");
  scanf("%s%s",v1,v2);
  DeleteArc(&g,v1,v2);
  printf("修改顶点的值，请输入原值 新值: ");
  scanf("%s%s",v1,v2);
  PutVex(&g,v1,v2);
  printf("插入新顶点，请输入顶点的值: ");
  scanf("%s",v1);
  InsertVex(&g,v1);
  printf("插入与新顶点有关的弧或边，请输入弧或边数: ");
  scanf("%d",&n);
  for(k=0;k<n;k++)
  {
    printf("请输入另一顶点的值: ");
    scanf("%s",v2);
    printf("对于有向图，请输入另一顶点的方向(0:弧头 1:弧尾): ");
    scanf("%d",&j);
    if(j)
      InsertArc(&g,v2,v1);
    else
      InsertArc(&g,v1,v2);
  }
  Display(g);
  printf("删除顶点及相关的弧或边，请输入顶点的值: ");
  scanf("%s",v1);
  DeleteVex(&g,v1);
  Display(g);
  printf("深度优先搜索的结果:\n");
  DFSTraverse(g,print);
  printf("广度优先搜索的结果:\n");
  BFSTraverse(g,print);
  DestroyGraph(&g);
  printf("请顺序选择有向网,无向图,无向网\n");
  for(i=0;i<3;i++) /* 验证另外3种情况 */
  {
    CreateGraph(&g);
    Display(g);
    printf("插入新顶点，请输入顶点的值: ");
    scanf("%s",v1);
    InsertVex(&g,v1);
    printf("插入与新顶点有关的弧或边，请输入弧或边数: ");
    scanf("%d",&n);
    for(k=0;k<n;k++)
    {
      printf("请输入另一顶点的值: ");
      scanf("%s",v2);
      if(g.kind<=1) /* 有向 */
      {
        printf("对于有向图或网，请输入另一顶点的方向(0:弧头 1:弧尾): ");
        scanf("%d",&j);
        if(j)
          InsertArc(&g,v2,v1);
        else
          InsertArc(&g,v1,v2);
      }
      else /* 无向 */
        InsertArc(&g,v1,v2);
    }
    Display(g);
    printf("删除顶点及相关的弧或边，请输入顶点的值: ");
    scanf("%s",v1);
    DeleteVex(&g,v1);
    Display(g);
    DestroyGraph(&g);
  }
}
