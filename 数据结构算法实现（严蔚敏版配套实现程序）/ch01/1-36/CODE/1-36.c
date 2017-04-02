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
listnode * locatenode(linklist head,char key)
{
    listnode * p=head;
    while( p->next&& p->data!=key)
        p=p->next;
    if(p!=NULL)
        printf("%c\n",p->data);
    return p;
}
main()
{
	linklist	list;
	listnode * node;
	char key='c';
	list=createlist();
	node=locatenode(list,key);
}
