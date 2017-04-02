#include "stdio.h"
#define QueueSize 100 /*假定预分配的队列空间最多为100个元素*/  
typedef char DataType ; /*假定队列元素的数据类型为字符*/
typedef struct node{
	DataType data;
	struct node *next;
}QueueNode;
typedef struct{
	QueueNode *front;  /*头指针*/
	QueueNode *rear;
}LinkQueue;
/* 置队列空*/

void Initial(LinkQueue *Q)
/*将顺序队列置空*/

{    Q->front=Q->rear=NULL;
} 

/*判队列空*/
int IsEmpty(LinkQueue *Q)
{
    return Q->front==NULL&&Q->rear==NULL;
}

/*进队列*/
void Push(LinkQueue *Q,DataType x)
{
/*将元素x插入链队列尾部*/
	QueueNode *p=(QueueNode *)malloc(sizeof(QueueNode));/*申请新结点*/
	p->data=x;
	p->next=NULL;
    if(IsEmpty(Q))
		Q->front=Q->rear=p;  /*将x插入空队列*/
	else 
	{ /*x插入非空队列的尾*/
		Q->rear->next=p;     /*p链到原队尾结点后*/
		Q->rear=p;           /*队尾指针指向新的尾*/
	}
}

/*出队列*/
DataType Pop(LinkQueue *Q)
{
	DataType x;
	QueueNode *p;
	if(IsEmpty(Q))
	{
		printf("队列为空");/*下溢*/
		exit(1);
	}
	p=Q->front;                   /*指向对头结点*/
	x=p->data;                    /*保存对头结点的数据*/
	Q->front=p->next;             /*将对头结点从链上摘下*/
    if(Q->rear==p)/*原队中只有一个结点，删去后队列变空，此时队头指针已为空*/
		Q->rear=NULL;
	free(p);   /*释放被删队头结点*/
	return x;  /*返回原队头数据*/
}

/* 取队列顶元素*/
DataType Front(LinkQueue *Q)
{
	if(IsEmpty(Q))
	{
		printf("队列为空"); /*下溢,退出运行*/
		exit(1);
	}
	return Q->front->data;
}

void main()
{
	LinkQueue s;
	DataType first,sec;
	Initial(&s);
	Push(&s,'a');
	Push(&s,'b');
	first=Front(&s);
	Pop(&s);
	sec=Front(&s);
	Pop(&s);
}
