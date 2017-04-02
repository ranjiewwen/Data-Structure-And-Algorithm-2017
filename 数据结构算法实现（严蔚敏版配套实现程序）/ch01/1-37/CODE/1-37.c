#include <stdio.h>
typedef   char  datatype;
typedef	  struct	node{
	datatype	  data;
	struct 	node  *next;
} listnode;
typedef  listnode  *linklist;
listnode  *p;
linklist  createlist(void)
{
      char ch;
      linklist  head;
      listnode  *p;
      head=NULL;/*初始化为空*/
      ch=getchar( );
      while (ch!='\n'){
           p=(listnode*)malloc(sizeof(listnode));/*分配空间*/
           p->data=ch;/*数据域赋值*/
           p->next=head;/*指定后继指针*/
		   head=p;/*head指针指定到新插入的结点上*/
       	   ch=getchar( );
      }
      return (head);
}
void  insertnode(linklist  head,char x,int i)
{
	int j=0;
	listnode  * p,*s;
	p=head;
	while(p&&j<i-1){
		p=p->next;
		++j;
	}
	if(!p||j>i-1)
		exit(1);
	s=(linklist)malloc(sizeof(listnode));
	s->data=x;
	s->next=p->next;
	p->next=s;
}
main()
{
	linklist	list;
	int i=1;
	char x='c';
	list=createlist();
	insertnode(list,x,i);
	do
	{
	   printf("%c",list->data);
	   list=list->next;
  }while(list!=NULL);
  printf("\n");
}
