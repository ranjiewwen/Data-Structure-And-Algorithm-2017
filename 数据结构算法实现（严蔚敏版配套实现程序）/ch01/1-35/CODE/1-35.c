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
listnode * getnode(linklist head,int i)
{
     int j;
     listnode * p;
     p=head;
	 	 j=0;
     while(p->next && j<i){/*遍历第i个结点前的所有结点*/
           p=p->next;
           j++;
     }
     if (i==j)
     {
         printf("%c\n",p->data);
         return p;
     }
     else
         return NULL;
}
main()
{
		linklist	list;
		listnode * node;
		int i=0;
		list=createlist();
		node=getnode(list,i);
}
