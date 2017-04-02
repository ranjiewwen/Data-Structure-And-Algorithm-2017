#include <stdio.h>
#define N	4
typedef   char  datatype;
typedef	  struct	node{
datatype	  data;
struct 	node  *next;
} listnode;
typedef  listnode  *linklist;
listnode  *p;
 linklist  creater()
{
    char  ch;
    linklist  head;
    listnode  *p,*r;
    head=NULL;
	r=NULL;/*r为尾指针*/
    while((ch=getchar())!='\n'){
        p=(listnode *)malloc(sizeof(listnode));
        p->data=ch;
        if(head==NULL)
            head=p;/*head 指向第一个插入结点*/
        else
			r->next=p;/*插入到链表尾部*/
        r=p;/*r指向最新结点，即最后结点*/
     }
     if (r!=NULL)
          r->next=NULL;/*链表尾部结点的后继指针指定为空*/
     return(head);
 }
main()
{
	linklist newlist=creater();
	do
	{
	   printf("%c",newlist->data);
	   newlist=newlist->next;
    }while(newlist!=NULL);
    printf("\n");
}
