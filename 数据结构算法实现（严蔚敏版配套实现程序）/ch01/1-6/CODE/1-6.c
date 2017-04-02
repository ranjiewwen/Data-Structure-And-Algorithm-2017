#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#include<stdarg.h>
#define OK 1
#define ERROR 0
#define MAX_ARRAY_DIM 8
typedef int ElemType;
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef struct
{
  ElemType *base; /* 数组元素基址，由InitArray分配 */
  int dim; /* 数组维数 */
  int *bounds; /* 数组维界基址，由InitArray分配 */
  int *constants; /* 数组映象函数常量基址，由InitArray分配 */
}Array;
/* 顺序存储数组的基本操作*/
Status InitArray(Array *A,int dim,...)
{ /* 若维数dim和各维长度合法，则构造相应的数组A，并返回OK */
  int elemtotal=1,i; /* elemtotal是元素总值 */
  va_list ap;
  if(dim<1||dim>MAX_ARRAY_DIM)
    return ERROR;
  (*A).dim=dim;
  (*A).bounds=(int *)malloc(dim*sizeof(int));
  if(!(*A).bounds)
    exit(OVERFLOW);
  va_start(ap,dim);
  for(i=0;i<dim;++i)
  {
    (*A).bounds[i]=va_arg(ap,int);
    if((*A).bounds[i]<0)
      return UNDERFLOW; /* 在math.h中定义为4 */
    elemtotal*=(*A).bounds[i];
  }
  va_end(ap);
  (*A).base=(ElemType *)malloc(elemtotal*sizeof(ElemType));
  if(!(*A).base)
    exit(OVERFLOW);
  (*A).constants=(int *)malloc(dim*sizeof(int));
  if(!(*A).constants)
    exit(OVERFLOW);
  (*A).constants[dim-1]=1;
  for(i=dim-2;i>=0;--i)
    (*A).constants[i]=(*A).bounds[i+1]*(*A).constants[i+1];
  return OK;
}
Status DestroyArray(Array *A)
{ /* 销毁数组A */
  if((*A).base)
  {
    free((*A).base);
    (*A).base=NULL;
  }
  else
    return ERROR;
  if((*A).bounds)
  {
    free((*A).bounds);
    (*A).bounds=NULL;
  }
  else
    return ERROR;
  if((*A).constants)
  {
    free((*A).constants);
    (*A).constants=NULL;
  }
  else
    return ERROR;
  return OK;
}
Status Locate(Array A,va_list ap,int *off) /* Value()、Assign()调用此函数 */
{ /* 若ap指示的各下标值合法，则求出该元素在A中的相对地址off */
  int i,ind;
  *off=0;
  for(i=0;i<A.dim;i++)
  {
    ind=va_arg(ap,int);
    if(ind<0||ind>=A.bounds[i])
      return OVERFLOW;
    *off+=A.constants[i]*ind;
  }
  return OK;
}
Status Value(ElemType *e,Array A,...)
{ /* ...依次为各维的下标值，若各下标合法，则e被赋值为A的相应的元素值 */
  va_list ap;
  Status result;
  int off;
  va_start(ap,A);
  if((result=Locate(A,ap,&off))==OVERFLOW) /* 调用Locate() */
    return result;
  *e=*(A.base+off);
  return OK;
}
Status Assign(Array *A,ElemType e,...)
{ /* ...依次为各维的下标值，若各下标合法，则将e的值赋给A的指定的元素 */
  va_list ap;
  Status result;
  int off;
  va_start(ap,e);
  if((result=Locate(*A,ap,&off))==OVERFLOW) /* 调用Locate() */
    return result;
  *((*A).base+off)=e;
  return OK;
}
void main()
{
  Array A;
  int i,j,k,*p,dim=3,bound1=3,bound2=4,bound3=2; /* a[3][4][2]数组 */
  ElemType e,*p1;
  InitArray(&A,dim,bound1,bound2,bound3); /* 构造3＊4＊2的3维数组A */
  p=A.bounds;
  printf("A.bounds=");
  for(i=0;i<dim;i++) /* 顺序输出A.bounds */
    printf("%d ",*(p+i));
  p=A.constants;
  printf("\nA.constants=");
  for(i=0;i<dim;i++) /* 顺序输出A.constants */
    printf("%d ",*(p+i));
  printf("\n%d页%d行%d列矩阵元素如下:\n",bound1,bound2,bound3);
  for(i=0;i<bound1;i++)
  {
    for(j=0;j<bound2;j++)
    {
      for(k=0;k<bound3;k++)
      {
        Assign(&A,i*100+j*10+k,i,j,k); /* 将i*100+j*10+k赋值给A[i][j][k] */
        Value(&e,A,i,j,k); /* 将A[i][j][k]的值赋给e */
        printf("A[%d][%d][%d]=%2d ",i,j,k,e); /* 输出A[i][j][k] */
      }
      printf("\n");
    }
    printf("\n");
  }
  p1=A.base;
  printf("A.base=\n");
  for(i=0;i<bound1*bound2*bound3;i++) /* 顺序输出A.base */
  {
    printf("%4d",*(p1+i));
    if(i%(bound2*bound3)==bound2*bound3-1)
      printf("\n");
  }
  DestroyArray(&A);
}
