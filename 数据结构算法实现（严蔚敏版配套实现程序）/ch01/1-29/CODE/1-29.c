#include "stdio.h"
#define QueueSize 100 /*假定预分配的队列空间最多为100个元素*/  	
typedef int DataType;/*假定队列元素的数据类型为字符*/  	
typedef struct{
	DataType data[QueueSize];
	int front;/*头指针*/
	int rear;/*尾指针*/
	int count; /*计数器，记录队中元素总数*/           
}CirQueue;   
/* 置队列空*/
void Initial(CirQueue *Q)
{/*将顺序队列置空*/
	Q->front=Q->rear=0;
	Q->count=0;     /*计数器置0*/       
} 
/* 判队列空*/
int IsEmpty(CirQueue *Q)
{
	return Q->front==Q->rear;
}
/*判队列满*/
int IsFull(CirQueue *Q)
{
	return Q->rear==QueueSize-1+Q->front;
}
/*进队列*/
void EnQueue(CirQueue *Q,DataType x)
{
	if (IsFull(Q))
	{
		printf("队列上溢"); /*上溢,退出运行*/
		exit(1);
	}
	Q->count ++;                        /*队列元素个数加1*/
	Q->data[Q->rear]=x;                 /*新元素插入队尾*/
	Q->rear=(Q->rear+1)%QueueSize;      /*循环意义下将尾指针加1*/
}
/*出队列*/
DataType DeQueue(CirQueue *Q)
{
	DataType temp;
	if(IsEmpty(Q))
	{
		printf("队列为空"); /*下溢,退出运行*/
		exit(1);
	}
	temp=Q->data[Q->front];
	Q->count--;                        /*队列元素个数减1*/
	Q->front=(Q->front+1)&QueueSize;   /*循环意义下的头指针加1*/
	return temp; 
	
}
/* 取队列顶元素*/
DataType Front(CirQueue *Q)
{
	if(IsEmpty(Q))
	{
		printf("队列为空"); /*下溢,退出运行*/
		exit(1);
	}
	return Q->data[Q->front];
}
void main()
{
	CirQueue s;
	DataType first,sec;
	Initial(&s);
	EnQueue(&s,'a');
	EnQueue(&s,'b');
	first=Front(&s);
	DeQueue(&s);
	sec=Front(&s);
	DeQueue(&s);
}
