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
void  deletelist(linklist head,int i)
{
int j=0;
    listnode * p,*r;
	p=head;
    while(p&&j<i-1){
		p=p->next;
		++j;
	}
    if(!p->next||j>i-1)
        exit(1);
    r=p->next;
    p->next=r->next;
    free(r) ;
}
main()
{
	linklist	list;
	int i=1;
	list=createlist();
	deletelist(list,i);
	do
	{
	   printf("%c",list->data);
	   list=list->next;
    }while(list!=NULL);
    printf("\n");
}
