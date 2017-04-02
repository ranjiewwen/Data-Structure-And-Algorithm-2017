#define MAX_NAME 5 /* 顶点字符串的最大长度+1 */
#define MAX_INFO 20 /* 相关信息字符串的最大长度+1 */
typedef int VRType;
typedef char VertexType[MAX_NAME];
typedef char InfoType;
#include<limits.h> /* INT_MAX等 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
#define INFINITY INT_MAX /* 用整型最大值代替∞ */
#define MAX_VERTEX_NUM 20 /* 最大顶点个数 */
typedef enum{DG,DN,AG,AN}GraphKind; /* {有向图,有向网,无向图,无向网} */
typedef struct
{
  VRType adj; /* 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否； */
       /* 对带权图，c则为权值类型 */
  InfoType *info; /* 该弧相关信息的指针(可无) */
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
  VertexType vexs[MAX_VERTEX_NUM]; /* 顶点向量 */
  AdjMatrix arcs; /* 邻接矩阵 */
  int vexnum,arcnum; /* 图的当前顶点数和弧数 */
  GraphKind kind; /* 图的种类标志 */
}MGraph;
int LocateVex(MGraph G,VertexType u)
{ /* 初始条件:图G存在,u和G中顶点有相同特征 */
  /* 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
  int i;
  for(i=0;i<G.vexnum;++i)
    if(strcmp(u,G.vexs[i])==0)
      return i;
  return -1;
}
Status CreateFAG(MGraph *G)
{ /* 采用数组(邻接矩阵)表示法,由文件构造没有相关信息的无向图G */
  int i,j,k;
  char filename[13];
  VertexType va,vb;
  FILE *graphlist;
  printf("请输入数据文件名(f7-1.dat)：");
  scanf("%s",filename);
  graphlist=fopen(filename,"r");
  fscanf(graphlist,"%d",&(*G).vexnum);
  fscanf(graphlist,"%d",&(*G).arcnum);
  for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
    fscanf(graphlist,"%s",(*G).vexs[i]);
  for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
    for(j=0;j<(*G).vexnum;++j)
    {
      (*G).arcs[i][j].adj=0; /* 图 */
      (*G).arcs[i][j].info=NULL; /* 没有相关信息 */
    }
  for(k=0;k<(*G).arcnum;++k)
  {
    fscanf(graphlist,"%s%s",va,vb);
    i=LocateVex(*G,va);
    j=LocateVex(*G,vb);
    (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* 无向图 */
  }
  fclose(graphlist);
  (*G).kind=AG;
  return OK;
}
Status CreateDG(MGraph *G)
{ /* 采用数组(邻接矩阵)表示法,构造有向图G */
  int i,j,k,l,IncInfo;
  char s[MAX_INFO],*info;
  VertexType va,vb;
  printf("请输入有向图G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
  scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
  printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
  for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
    scanf("%s",(*G).vexs[i]);
  for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
    for(j=0;j<(*G).vexnum;++j)
    {
      (*G).arcs[i][j].adj=0; /* 图 */
      (*G).arcs[i][j].info=NULL;
    }
  printf("请输入%d条弧的弧尾 弧头(以空格作为间隔): \n",(*G).arcnum);
  for(k=0;k<(*G).arcnum;++k)
  {
    scanf("%s%s%*c",va,vb);  /* %*c吃掉回车符 */
    i=LocateVex(*G,va);
    j=LocateVex(*G,vb);
    (*G).arcs[i][j].adj=1; /* 有向图 */
    if(IncInfo)
    {
      printf("请输入该弧的相关信息(<%d个字符): ",MAX_INFO);
      gets(s);
      l=strlen(s);
      if(l)
      {
        info=(char*)malloc((l+1)*sizeof(char));
        strcpy(info,s);
        (*G).arcs[i][j].info=info; /* 有向 */
      }
    }
  }
  (*G).kind=DG;
  return OK;
}
Status CreateDN(MGraph *G)
{ /* 采用数组(邻接矩阵)表示法,构造有向网G */
  int i,j,k,w,IncInfo;
  char s[MAX_INFO],*info;
  VertexType va,vb;
  printf("请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
  scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
  printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
  for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
    scanf("%s",(*G).vexs[i]);
  for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
    for(j=0;j<(*G).vexnum;++j)
    {
      (*G).arcs[i][j].adj=INFINITY; /* 网 */
      (*G).arcs[i][j].info=NULL;
    }
  printf("请输入%d条弧的弧尾 弧头 权值(以空格作为间隔): \n",(*G).arcnum);
  for(k=0;k<(*G).arcnum;++k)
  {
    scanf("%s%s%d%*c",va,vb,&w);  /* %*c吃掉回车符 */
    i=LocateVex(*G,va);
    j=LocateVex(*G,vb);
    (*G).arcs[i][j].adj=w; /* 有向网 */
    if(IncInfo)
    {
      printf("请输入该弧的相关信息(<%d个字符): ",MAX_INFO);
      gets(s);
      w=strlen(s);
      if(w)
      {
        info=(char*)malloc((w+1)*sizeof(char));
        strcpy(info,s);
        (*G).arcs[i][j].info=info; /* 有向 */
      }
    }
  }
  (*G).kind=DN;
  return OK;
}
Status CreateAG(MGraph *G)
{ /* 采用数组(邻接矩阵)表示法,构造无向图G */
  int i,j,k,l,IncInfo;
  char s[MAX_INFO],*info;
  VertexType va,vb;
  printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
  scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
  printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
  for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
    scanf("%s",(*G).vexs[i]);
  for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
    for(j=0;j<(*G).vexnum;++j)
    {
      (*G).arcs[i][j].adj=0; /* 图 */
      (*G).arcs[i][j].info=NULL;
    }
  printf("请输入%d条边的顶点1 顶点2(以空格作为间隔): \n",(*G).arcnum);
  for(k=0;k<(*G).arcnum;++k)
  {
    scanf("%s%s%*c",va,vb); /* %*c吃掉回车符 */
    i=LocateVex(*G,va);
    j=LocateVex(*G,vb);
    (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* 无向图 */
    if(IncInfo)
    {
      printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
      gets(s);
      l=strlen(s);
      if(l)
      {
        info=(char*)malloc((l+1)*sizeof(char));
        strcpy(info,s);
        (*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* 无向 */
      }
    }
  }
  (*G).kind=AG;
  return OK;
}
Status CreateAN(MGraph *G)
{ /* 采用数组(邻接矩阵)表示法,构造无向网G。算法7.2 */
  int i,j,k,w,IncInfo;
  char s[MAX_INFO],*info;
  VertexType va,vb;
  printf("请输入无向网G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
  scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
  printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
  for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
    scanf("%s",(*G).vexs[i]);
  for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
    for(j=0;j<(*G).vexnum;++j)
    {
      (*G).arcs[i][j].adj=INFINITY; /* 网 */
      (*G).arcs[i][j].info=NULL;
    }
  printf("请输入%d条边的顶点1 顶点2 权值(以空格作为间隔): \n",(*G).arcnum);
  for(k=0;k<(*G).arcnum;++k)
  {
    scanf("%s%s%d%*c",va,vb,&w); /* %*c吃掉回车符 */
    i=LocateVex(*G,va);
    j=LocateVex(*G,vb);
    (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=w; /* 无向 */
    if(IncInfo)
    {
      printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
      gets(s);
      w=strlen(s);
      if(w)
      {
        info=(char*)malloc((w+1)*sizeof(char));
        strcpy(info,s);
        (*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* 无向 */
      }
    }
  }
  (*G).kind=AN;
  return OK;
}
Status CreateGraph(MGraph *G)
{ /* 采用数组(邻接矩阵)表示法,构造图G。*/
  printf("请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
  scanf("%d",&(*G).kind);
  switch((*G).kind)
  {
    case DG: return CreateDG(G); /* 构造有向图 */
    case DN: return CreateDN(G); /* 构造有向网 */
    case AG: return CreateAG(G); /* 构造无向图 */
    case AN: return CreateAN(G); /* 构造无向网 */
    default: return ERROR;
  }
}
void DestroyGraph(MGraph *G)
{ /* 初始条件: 图G存在。操作结果: 销毁图G */
  int i,j;
  if((*G).kind<2) /* 有向 */
    for(i=0;i<(*G).vexnum;i++) /* 释放弧的相关信息(如果有的话) */
    {
      for(j=0;j<(*G).vexnum;j++)
        if((*G).arcs[i][j].adj==1&&(*G).kind==0||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==1) /* 有向图的弧||有向网的弧 */
          if((*G).arcs[i][j].info) /* 有相关信息 */
          {
            free((*G).arcs[i][j].info);
            (*G).arcs[i][j].info=NULL;
          }
    }
  else /* 无向 */
    for(i=0;i<(*G).vexnum;i++) /* 释放边的相关信息(如果有的话) */
      for(j=i+1;j<(*G).vexnum;j++)
        if((*G).arcs[i][j].adj==1&&(*G).kind==2||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==3) /* 无向图的边||无向网的边 */
          if((*G).arcs[i][j].info) /* 有相关信息 */
          {
            free((*G).arcs[i][j].info);
            (*G).arcs[i][j].info=(*G).arcs[j][i].info=NULL;
          }
  (*G).vexnum=0;
  (*G).arcnum=0;
}
VertexType* GetVex(MGraph G,int v)
{ /* 初始条件: 图G存在，v是G中某个顶点的序号。操作结果: 返回v的值 */
  if(v>=G.vexnum||v<0)
    exit(ERROR);
  return &G.vexs[v];
}
Status PutVex(MGraph *G,VertexType v,VertexType value)
{ /* 初始条件: 图G存在，v是G中某个顶点。操作结果: 对v赋新值value */
  int k;
  k=LocateVex(*G,v); /* k为顶点v在图G中的序号 */
  if(k<0)
    return ERROR;
  strcpy((*G).vexs[k],value);
  return OK;
}
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
void ShortestPath_FLOYD(MGraph G,PathMatrix *P,DistancMatrix *D)
{ /* 用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w]及其 */
  /* 带权长度D[v][w]。若P[v][w][u]为TRUE,则u是从v到w当前求得最短 */
  /* 路径上的顶点。算法7.16 */
  int u,v,w,i;
  for(v=0;v<G.vexnum;v++) /* 各对结点之间初始已知路径及距离 */
    for(w=0;w<G.vexnum;w++)
    {
      (*D)[v][w]=G.arcs[v][w].adj;
      for(u=0;u<G.vexnum;u++)
        (*P)[v][w][u]=FALSE;
      if((*D)[v][w]<INFINITY) /* 从v到w有直接路径 */
      {
        (*P)[v][w][v]=TRUE;
        (*P)[v][w][w]=TRUE;
      }
    }
  for(u=0;u<G.vexnum;u++)
    for(v=0;v<G.vexnum;v++)
      for(w=0;w<G.vexnum;w++)
        if((*D)[v][u]+(*D)[u][w]<(*D)[v][w]) /* 从v经u到w的一条路径更短 */
        {
          (*D)[v][w]=(*D)[v][u]+(*D)[u][w];
          for(i=0;i<G.vexnum;i++)
            (*P)[v][w][i]=(*P)[v][u][i]||(*P)[u][w][i];
        }
}
void main()
{
  MGraph g;
  int i,j,k,l,m,n;
  PathMatrix p;
  DistancMatrix d;
  CreateDN(&g);
  for(i=0;i<g.vexnum;i++)
    g.arcs[i][i].adj=0; /* ShortestPath_FLOYD()要求对角元素值为0 */
  printf("邻接矩阵:\n");
  for(i=0;i<g.vexnum;i++)
  {
    for(j=0;j<g.vexnum;j++)
      printf("%11d",g.arcs[i][j]);
    printf("\n");
  }
  ShortestPath_FLOYD(g,&p,&d);
  printf("d矩阵:\n");
  for(i=0;i<g.vexnum;i++)
  {
    for(j=0;j<g.vexnum;j++)
      printf("%6d",d[i][j]);
    printf("\n");
  }
  for(i=0;i<g.vexnum;i++)
    for(j=0;j<g.vexnum;j++)
      printf("%s到%s的最短距离为%d\n",g.vexs[i],g.vexs[j],d[i][j]);
  printf("p矩阵:\n");
  l=strlen(g.vexs[0]); /* 顶点向量字符串的长度 */
  for(i=0;i<g.vexnum;i++)
  {
    for(j=0;j<g.vexnum;j++)
    {
      if(i!=j)
      {
        m=0; /* 占位空格 */
        for(k=0;k<g.vexnum;k++)
          if(p[i][j][k]==1)
            printf("%s",g.vexs[k]);
          else
            m++;
        for(n=0;n<m*l;n++) /* 输出占位空格 */
          printf(" ");
      }
      else
        for(k=0;k<g.vexnum*l;k++) /* 输出占位空格 */
          printf(" ");
      printf("   "); /* 输出矩阵元素之间的间距 */
    }
    printf("\n");
  }
}
