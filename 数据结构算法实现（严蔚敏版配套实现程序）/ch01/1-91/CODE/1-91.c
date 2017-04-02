#include<limits.h> /* INT_MAX等 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
/* #define INFEASIBLE -1*/
#define LT(a,b) ((a)<(b))
#define MAXSIZE 20 /* 一个用作示例的小顺序表的最大长度 */
#define k 5 /* k路归并 */
#define N 3 /* 设每小个文件有N个数据(可将整个文件一次读入内存的称为小文件) */
#define M 10 /* 设输出M个数据换行 */
#define MINKEY INT_MIN
#define MAXKEY INT_MAX
typedef int KeyType; /* 定义关键字类型为整型 */
typedef int InfoType; /* 定义其它数据项的类型 */
typedef struct
{
  KeyType key; /* 关键字项 */
  InfoType otherinfo; /* 其它数据项，具体类型在主程中定义 */
}RedType; /* 记录类型 */
typedef struct
{
  RedType r[MAXSIZE+1]; /* r[0]闲置或用作哨兵单元 */
  int length; /* 顺序表长度 */
}SqList; /* 顺序表类型 */
FILE *fp[k+1]; /* k+1个文件指针(fp[k]为大文件指针)，全局变量 */
typedef int LoserTree[k]; /* 败者树是完全二叉树且不含叶子，可采用顺序存储结构 */
typedef RedType ExNode,External[k+1]; /* 外结点,有改变 */
External b; /* 全局变量 */
void InsertSort(SqList *L)
{ /* 对顺序表L作直接插入排序。*/
  int i,j;
  for(i=2;i<=(*L).length;++i)
    if LT((*L).r[i].key,(*L).r[i-1].key) /* "<",需将L.r[i]插入有序子表 */
    {
      (*L).r[0]=(*L).r[i]; /* 复制为哨兵 */
      for(j=i-1;LT((*L).r[0].key,(*L).r[j].key);--j)
 (*L).r[j+1]=(*L).r[j]; /* 记录后移 */
      (*L).r[j+1]=(*L).r[0]; /* 插入到正确位置 */
    }
}
void input(int i,KeyType *a)
{ /* 从第i个文件(第i个归并段)读入该段当前第1个记录的关键字到外结点 */
  fread(a,sizeof(KeyType),1,fp[i]);
}
void output(int i)
{ /* 将第i个文件(第i个归并段)中当前的记录写至输出归并段 */
  ExNode a;
  a.key=b[i].key; /* 当前记录的关键字已读到b[i].key中 */
  fread(&a.otherinfo,sizeof(InfoType),1,fp[i]);
  fwrite(&a,sizeof(ExNode),1,fp[k]);
}
void Adjust(LoserTree ls,int s)
{ /* 沿从叶子结点b[s]到根结点ls[0]的路径调整败者树。*/
  int i,t;
  t=(s+k)/2; /* ls[t]是b[s]的双亲结点 */
  while(t>0)
  {
    if(b[s].key>b[ls[t]].key)
    {
      i=s;
      s=ls[t]; /* s指示新的胜者 */
      ls[t]=i;
    }
    t=t/2;
  }
  ls[0]=s;
}
void CreateLoserTree(LoserTree ls)
{ /* 已知b[0]到b[k-1]为完全二叉树ls的叶子结点，存有k个关键字，沿从叶子 */
  /* 到根的k条路径将ls调整成为败者树。*/
  int i;
  b[k].key=MINKEY;
  for(i=0;i<k;++i)
    ls[i]=k; /* 设置ls中"败者"的初值 */
  for(i=k-1;i>=0;--i) /* 依次从b[k-1]，b[k-2]，…，b[0]出发调整败者 */
    Adjust(ls,i);
}
void K_Merge(LoserTree ls,External b)
{ /* 利用败者树ls将编号从0到k-1的k个输入归并段中的记录归并到输出归并段。 */
  /* b[0]至b[k-1]为败者树上的k个叶子结点，分别存放k个输入归并段中当前 */
  /* 记录的关键字。*/
  int i,q;
  for(i=0;i<k;++i) /* 分别从k个输入归并段读人该段当前第一个记录的关键字到外结点 */
    input(i,&b[i].key);
  CreateLoserTree(ls); /* 建败者树ls，选得最小关键字为b[ls[0]].key */
  while(b[ls[0]].key!=MAXKEY)
  {
    q=ls[0]; /* q指示当前最小关键字所在归并段 */
    output(q); /* 将编号为q的归并段中当前（关键字为b[q].key）的记录写至输出归并段 */
    input(q,&b[q].key); /* 从编号为q的输入归并段中读人下一个记录的关键字 */
    Adjust(ls,q); /* 调整败者树，选择新的最小关键字 */
  }
  output(ls[0]); /* 将含最大关键字MAXKEY的记录写至输出归并段 */
}
void print(RedType t)
{
  printf("(%d,%d)",t.key,t.otherinfo);
}
void main()
{
  RedType a[k*N]={{16,1},{15,2},{10,3},{20,4},{9,5},{18,6},{22,7},{20,8},{40,9},{15,10},{25,11},{6,12},{12,13},{48,14},{37,15}}; /* 有k*N个记录的数组 */
  RedType r,t={MAXKEY}; /* 小文件尾部的结束标志 */
  SqList l;
  int i,j;
  char fname[k][3],fori[4]="ori",fout[4]="out",s[3];
  LoserTree ls;
  /* 由数组a创造1个大文件(不能将整个文件一次读入内存的称为大文件) */
  fp[k]=fopen(fori,"wb"); /* 以写的方式打开大文件fori */
  fwrite(a,sizeof(RedType),k*N,fp[k]); /* 将数组a中的数据写入文件fori中(表示1个大文件) */
  fclose(fp[k]); /* 关闭文件fori */
  fp[k]=fopen(fori,"rb"); /* 以读的方式打开大文件fori */
  printf("大文件的记录为:\n");
  for(i=1;i<=N*k;i++)
  {
    fread(&r,sizeof(RedType),1,fp[k]); /* 依次将大文件fori的数据读入r */
    print(r); /* 输出r的内容 */
    if(i%M==0)
      printf("\n");
  }
  printf("\n");
  rewind(fp[k]); /* 使fp[k]的指针重新返回大文件fori的起始位置，以便重新读入内存，产生有序的子文件 */
  for(i=0;i<k;i++) /* 将大文件fori的数据分成k组，每组N个数据 */
  { /* 排序后分别存到小文件f0,f1,…中 */
    fread(&l.r[1],sizeof(RedType),N,fp[k]); /* 将大文件fori的N个数据读入l */
    l.length=N;
    InsertSort(&l); /* 对l进行内部排序 */
    itoa(i,s,10); /* 生成k个文件名f0,f1,f2,… */
    strcpy(fname[i],"f");
    strcat(fname[i],s);
    fp[i]=fopen(fname[i],"wb"); /* 以写的方式打开文件f0,f1,… */
    fwrite(&l.r[1],sizeof(RedType),N,fp[i]); /* 将排序后的N个数据分别写入f0,f1,… */
    fwrite(&t,sizeof(RedType),1,fp[i]); /* 将文件结束标志分别写入f0,f1,… */
    fclose(fp[i]); /* 关闭文件f0,f1,… */
  }
  fclose(fp[k]); /* 关闭大文件fori */
  for(i=0;i<k;i++)
  { /* 依次打开f0,f1,f2,…,k个文件 */
    itoa(i,s,10); /* 生成k个文件名f0,f1,f2,… */
    strcpy(fname[i],"f");
    strcat(fname[i],s);
    fp[i]=fopen(fname[i],"rb"); /* 以读的方式打开文件f0,f1,… */
    printf("有序子文件f%d的记录为:\n",i);
    for(j=0;j<=N;j++)
    {
      fread(&r,sizeof(RedType),1,fp[i]); /* 依次将f0,f1,…的数据读入r */
      print(r); /* 输出r的内容 */
    }
    printf("\n");
    rewind(fp[i]); /* 使fp[i]的指针重新返回f0,f1,…的起始位置，以便重新读入内存 */
  }
  fp[k]=fopen(fout,"wb"); /* 以写的方式打开大文件fout */
  K_Merge(ls,b); /* 利用败者树ls将k个输入归并段中的记录归并到输出归并段，即大文件fout */
  for(i=0;i<k;i++)
    fclose(fp[i]); /* 关闭文件f0,f1,… */
  fclose(fp[k]); /* 关闭文件fout */
  fp[k]=fopen(fout,"rb"); /* 以读的方式打开大文件fout验证排序 */
  printf("排序后的大文件的记录为:\n");
  for(i=1;i<=N*k+1;i++)
  {
    fread(&t,sizeof(RedType),1,fp[k]);
    print(t);
    if(i%M==0)
      printf("\n");
  }
  printf("\n");
  fclose(fp[k]); /* 关闭文件fout */
}
