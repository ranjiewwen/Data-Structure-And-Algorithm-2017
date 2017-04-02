#include<limits.h> /* INT_MAX等 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#define OK 1
#define ERROR 0
#define N 5 /* 数据元素个数 */
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
typedef int KeyType; /* 设关键字域为整型 */
typedef struct /* 数据元素类型(以教科书图9.1高考成绩为例) */
{
  long number; /* 准考证号 */
  char name[9]; /* 姓名(4个汉字加1个串结束标志) */
  int politics; /* 政治 */
  int Chinese; /* 语文 */
  int English; /* 英语 */
  int math; /* 数学 */
  int physics; /* 物理 */
  int chemistry; /* 化学 */
  int biology; /* 生物 */
  KeyType key; /* 关键字类型应为KeyType,域名应为key,与bo9-1.c中一致 */
} ElemType;
ElemType r[N]={{179324,"何芳芳",85,89,98,100,93,80,47},
               {179325,"陈红",85,86,88,100,92,90,45},
               {179326,"陆华",78,75,90,80,95,88,37},
               {179327,"张平",82,80,78,98,84,96,40},
               {179328,"赵小怡",76,85,94,57,77,69,44}}; /* 全局变量 */
#define total key /* 定义总分(total)为关键字 */
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
typedef struct
{
  ElemType *elem; /* 数据元素存储空间基址，建表时按实际长度分配，0号单元留空 */
  int length; /* 表长度 */
}SSTable;
Status Creat_Seq(SSTable *ST,int n)
{ /* 操作结果: 构造一个含n个数据元素的静态顺序查找表ST(数据来自全局数组r) */
  int i;
  (*ST).elem=(ElemType *)calloc(n+1,sizeof(ElemType)); /* 动态生成n个数据元素空间(0号单元不用) */
  if(!(*ST).elem)
    return ERROR;
  for(i=1;i<=n;i++)
    *((*ST).elem+i)=r[i-1]; /* 将全局数组r的值依次赋给ST */
  (*ST).length=n;
  return OK;
}

void Ascend(SSTable *ST)
{ /* 重建静态查找表为按关键字非降序排序 */
  int i,j,k;
  for(i=1;i<(*ST).length;i++)
  {
    k=i;
    (*ST).elem[0]=(*ST).elem[i]; /* 待比较值存[0]单元 */
    for(j=i+1;j<=(*ST).length;j++)
      if LT((*ST).elem[j].key,(*ST).elem[0].key)
      {
        k=j;
        (*ST).elem[0]=(*ST).elem[j];
      }
    if(k!=i) /* 有更小的值则交换 */
    {
      (*ST).elem[k]=(*ST).elem[i];
      (*ST).elem[i]=(*ST).elem[0];
    }
  }
}
Status Creat_Ord(SSTable *ST,int n)
{ /* 操作结果: 构造一个含n个数据元素的静态按关键字非降序查找表ST */
  /* 数据来自全局数组r */
  Status f;
  f=Creat_Seq(ST,n);
  if(f)
    Ascend(ST);
  return f;
}
Status Destroy(SSTable *ST)
{ /* 初始条件: 静态查找表ST存在。操作结果: 销毁表ST */
  free((*ST).elem);
  (*ST).elem=NULL;
  (*ST).length=0;
  return OK;
}
int Search_Seq(SSTable ST,KeyType key)
{ /* 在顺序表ST中顺序查找其关键字等于key的数据元素。若找到，则函数值为 */
  /* 该元素在表中的位置，否则为0。*/
  int i;
  ST.elem[0].key=key; /* 哨兵 */
  for(i=ST.length;!EQ(ST.elem[i].key,key);--i); /* 从后往前找 */
  return i; /* 找不到时，i为0 */
}
int Search_Bin(SSTable ST,KeyType key)
{ /* 在有序表ST中折半查找其关键字等于key的数据元素。若找到，则函数值为 */
  /* 该元素在表中的位置，否则为0。*/
  int low,high,mid;
  low=1; /* 置区间初值 */
  high=ST.length;
  while(low<=high)
  {
    mid=(low+high)/2;
    if EQ(key,ST.elem[mid].key)  /* 找到待查元素 */
      return mid;
    else if LT(key,ST.elem[mid].key)
      high=mid-1; /* 继续在前半区间进行查找 */
    else
      low=mid+1; /* 继续在后半区间进行查找 */
  }
  return 0; /* 顺序表中不存在待查元素 */
}
Status Traverse(SSTable ST,void(*Visit)(ElemType))
{ /* 初始条件: 静态查找表ST存在，Visit()是对元素操作的应用函数 */
  /* 操作结果: 按顺序对ST的每个元素调用函数Visit()一次且仅一次。 */
  /* 一旦Visit()失败，则操作失败 */
  ElemType *p;
  int i;
  p=++ST.elem; /* p指向第一个元素 */
  for(i=1;i<=ST.length;i++)
    Visit(*p++);
  return OK;
}
void print(ElemType c) /* Traverse()调用的函数 */
{ printf("%-8ld%-8s%4d%5d%5d%5d%5d%5d%5d%5d\n",c.number,c.name,c.politics,c.Chinese,c.English,c.math,c.physics,c.chemistry,c.biology,c.total);
}
void main()
{
  SSTable st;
  int i,s;
  for(i=0;i<N;i++) /* 计算总分 */
    r[i].total=r[i].politics+r[i].Chinese+r[i].English+r[i].math+r[i].physics+r[i].chemistry+r[i].biology;
  Creat_Seq(&st,N); /* 由全局数组产生静态查找表st */
  printf("准考证号  姓名  政治 语文 外语 数学 物理 化学 生物 总分\n");
  Traverse(st,print); /* 按顺序输出静态查找表st */
  printf("请输入待查找人的总分: ");
  scanf("%d",&s);
  i=Search_Seq(st,s); /* 顺序查找 */
  if(i)
    print(*(st.elem+i));
  else
    printf("没找到\n");
  Destroy(&st);
}
