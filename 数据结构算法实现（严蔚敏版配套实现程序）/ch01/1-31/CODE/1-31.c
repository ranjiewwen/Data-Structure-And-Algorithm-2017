#include "stdio.h"
#define MAX_DANCERS 100//最多跳舞人数
#define QueueSize 100 //假定预分配的队列空间最多为100个元素  	
typedef struct{
	char name[20];
	char sex;  //性别，'F'表示女性，'M'表示男性
}Person;
typedef Person DataType;  //将队列中元素的数据类型改为Person
typedef struct{
	DataType data[QueueSize];
	int front;//头指针
	int rear;//尾指针
	int count; //计数器，记录队中元素总数
}CirQueue;
// 置队列空
void Initial(CirQueue *Q)
{//将顺序队列置空
	Q->front=Q->rear=0;
	Q->count=0;     //计数器置0
}
//判队列空
int IsEmpty(CirQueue *Q)
{
	return Q->front==Q->rear;
}
//判队列满
int IsFull(CirQueue *Q)
{
	return Q->rear==QueueSize-1+Q->front;
}
//进队列
void EnQueue(CirQueue *Q,DataType x)
{
	if (IsFull(Q))
	{
		printf("队列上溢"); //上溢,退出运行
		exit(1);
	}
	Q->count ++;                        //队列元素个数加1
	Q->data[Q->rear]=x;                 //新元素插入队尾
	Q->rear=(Q->rear+1)%QueueSize;      //循环意义下将尾指针加1
}
//出队列
DataType DeQueue(CirQueue *Q)
{
	DataType temp;
	if(IsEmpty(Q))
	{
		printf("队列为空"); //下溢,退出运行
		exit(1);
	}
	temp=Q->data[Q->front];
	Q->count--;                        //队列元素个数减1
	Q->front=(Q->front+1)&QueueSize;   //循环意义下的头指针加1
	return temp;
	
}
// 取队列顶元素
DataType Front(CirQueue *Q)
{
	if(IsEmpty(Q))
	{
		printf("队列为空"); //下溢,退出运行
		exit(1);
	}
	return Q->data[Q->front];
}
void DancePartner(Person dancer[],int num)
{//结构数组dancer中存放跳舞的男女，num是跳舞的人数。
	int i;
	Person p;
	CirQueue Mdancers,Fdancers;
	Initial(&Mdancers);//男士队列初始化
	Initial(&Fdancers);//女士队列初始化
	for(i=0;i<num;i++){//依次将跳舞者依其性别入队
		p=dancer[i];
		if(p.sex=='F')
			EnQueue(&Fdancers,p);   //排入女队
		else
			EnQueue(&Mdancers,p);   //排入男队
	}
	printf("舞队是:\n");
	while(!IsEmpty(&Fdancers)&&!IsEmpty(&Mdancers)){
		//依次输入男女舞伴名
		p=DeQueue(&Fdancers);     //女士出队
		printf("%s        ",p.name);//打印出队女士名
		p=DeQueue(&Mdancers);     //男士出队
		printf("%s\n",p.name);    //打印出队男士名
	}
	if(!IsEmpty(&Fdancers)){ //输出女士剩余人数及队头女士的名字
		printf("还有 %d 个女士等下一轮.\n",Fdancers.count);
		p=Front(&Fdancers);  //取队头
		printf("%s will be the first to get a partner. \n",p.name);
	}
	else if(!IsEmpty(&Mdancers)){//输出男队剩余人数及队头者名字
		printf("还有%d 个男士等下一轮.\n",Mdancers.count);
		p=Front(&Mdancers);
		printf("%s will be the first to get a partner.\n",p.name);
	}
}
void InitialDancer(Person dancer[])
{
	//跳舞报名
}
void main()
{
	Person dancer[MAX_DANCERS];
	int n=93;
	InitialDancer(dancer);
	DancePartner(dancer,93);
}

