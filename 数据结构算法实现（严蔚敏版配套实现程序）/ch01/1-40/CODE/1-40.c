#include "stdio.h"
typedef   char  datatype;
typedef	 struct	node{
	datatype	 data;
	struct 	node  *next;
} stack;
stack *  creat(void)
{
      char ch;
      stack *  head;
      stack *p;
      head=NULL;/*初始化为空*/
      ch=getchar( );
      while (ch!='\n'){
           p=(stack*)malloc(sizeof(stack));/*分配空间*/
           p->data=ch;/*数据域赋值*/
           p->next=head;/*指定后继指针*/
		   head=p;/*head指针指定到新插入的结点上*/
       	   ch=getchar( );
      }
      return (head);
}
void MakeNull(stack *s)/*使栈s为空*/
{
		stack *p=s;
		while(s!=NULL){
			s=s->next;
			free(p);/*释放空间*/
			p=s;
		}
}
datatype Top(stack *s)
{
	if(Empty(s))/*s为空栈，直接跳出，提示出错信息*/
		printf("The stack is empty.");
	else
		return s->data;
}
void Pop(stack *s)
{
		stack *p;
		if(Empty(s)) /*s为空栈，直接跳出，提示出错信息*/
			printf("The stack is empty.");
		else{
			p=s;
			s=s->next;
			free(p);/*释放栈顶空间*/
		}
}
void Push(stack *s,datatype x)
{
		stack *p;
		p=(stack*)malloc(sizeof(stack));
		p->data=x;
		p->next=s;
		s=p;
}
int Empty(stack *s)
{
	return(s==NULL);
}
void main()
{
	stack*	m_stack=creat();
	char	m_top;
	if(!Empty(m_stack))
	{
		m_top=Top(m_stack);
		Pop(m_stack);
	}
	else
		Push(m_stack,'a');
	MakeNull(m_stack);
}
