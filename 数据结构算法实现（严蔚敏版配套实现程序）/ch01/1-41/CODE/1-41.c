#include "stdio.h"
typedef   char  datatype;
typedef	 struct	node{
	datatype	 data;
	struct 	node  *next;
} position;
typedef 	struct queue{
	position 	*front;
	position 	*rear;
}queuetype;
/*使队列为空：*/
void MakeNull(queuetype * q)
{
		q->rear=q->front;
		while(q->front!=NULL){
			q->front=q->front->next;
			free(q->rear);/*释放空间*/
			q->rear=q->front;
		}
		q->front=(position*)malloc(sizeof(position));
		q->front->next=NULL;
		q->rear=q->front;
}
/* 取队列的队头元素：*/
datatype Front(queuetype *q)
{
		if(Empty(q))
			printf("'The queue is empty!");
		else
			return(q->front->next->data);
}
/*删除队列头元素：*/
void dequeue(queuetype * q)
{
		position* p;
		if(Empty(q))
			printf("The queue is empty!");
		else{
			p=q->front;
			q->front=q->front->next;
			free(p);
		}
}
/* 在队列中加入新元素：*/
void Enqueue(datatype x,queuetype * q)
{
		position* p;
		p=(position*)malloc(sizeof(position));
		p->data=x;
		p->next=NULL;
		q->rear->next=p;
		q->rear=p;
}
/*判断是否为空队列：*/
int Empty(queuetype * q)
{
	return (q->front==q->rear);
}
void main()
{
	queuetype *	m_q;
        char	m_top;
        m_q=(queuetype *)malloc(sizeof(queuetype));
        m_q->front=m_q->rear=(position*)malloc(sizeof(position));
        m_q->rear->next=NULL;
	if(!Empty(m_q))
	{
		m_top=Front(m_q);
		dequeue(m_q);
	}
	else
		Enqueue('c',m_q);
	MakeNull(m_q);
}
