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
linklist  concatenate(linklist list1,linklist list2)
{
	listnode *temp;
    if (list1==NULL)
		return list2;
    else {
        if (list2!=NULL) {
            for ( temp =list1; temp->next; temp = temp->next )
				; /*遍历到list1的末尾*/
           	temp->next=list2;/*将list2链接到list1末尾*/
        }
	}
    return list1;
}
main()
{
	linklist	list1,list2,list3;
	list1=createlist();
	list2=createlist();
	list3=concatenate(list1,list2);
	do
	{
	   printf("%c",list3->data);
	   list3=list3->next;
    }while(list3!=NULL);
    printf("\n");
}
