#include "stdio.h"
#define QueueSize 100 /*假定预分配的队列空间最多为100个元素*/  	
typedef int DataType;/*假定队列元素的数据类型为字符*/  	
typedef struct{
      DataType data[QueueSize];
      int front;/*头指针*/
	  int rear;/*尾指针*/
}SeqQueue;   
/* 置队列空*/
void Initial(SeqQueue *Q)
{/*将顺序队列置空*/
      Q->front=Q->rear=0;
} 
/*判队列空*/
int IsEmpty(SeqQueue *Q)
{
    return Q->front==Q->rear;
}
/*判队列满*/
int IsFull(SeqQueue *Q)
{
	return Q->rear==QueueSize-1+Q->front;
}
/*进队列*/
void Push(SeqQueue *Q,DataType x)
{
    if (IsFull(Q))
	{
		printf("队列上溢"); /*上溢,退出运行*/
		exit(1);
	}
    Q->data[Q->rear++]=x;/*队列顶指针加1后将x入队列*/
}
/*出队列*/
DataType Pop(SeqQueue *Q)
{
	if(IsEmpty(Q))
	{
		printf("队列为空"); /*下溢,退出运行*/
		exit(1);
	}
	return Q->data[Q->front++];/*队列顶元素返回后将队列顶指针减1*/
}
/* 取队列顶元素*/
DataType Top(SeqQueue *Q)
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
	SeqQueue s;
	DataType first,sec;
	Initial(&s);
	Push(&s,'a');
	Push(&s,'b');
	first=Top(&s);
	Pop(&s);
	sec=Top(&s);
	Pop(&s);
}
