#include"stdio.h"
struct s_node
{
	int data;
	struct s_node *next;
};
typedef struct s_node s_list;
typedef	s_list *link;
link stack=NULL;
void print_stack()
{
	link temp=NULL;
	temp=stack;
	if(temp==NULL)
		printf("The stack is empty!\n");
	else
		{
			while(temp!=NULL)
			{
				printf("[%d]",temp->data);
				temp=temp->next;
			}
			printf("\n");
		}
}
void push(int value)
{
	link newnode;
	printf("\nThe stack content before(top->bottom):");
	print_stack();
	newnode=(link)malloc(sizeof(s_list));
	newnode->data=value;
	newnode->next=stack;
	stack=newnode;
}
int pop()
{
	link top;
	int temp;
	printf("\nThe stack content before(top->bottom):");
	print_stack();	
	if(stack!=NULL)
		{
			top=stack;
			stack=stack->next;
			temp=top->data;
			free(top);
			return temp;
		}
		else
			return -1;
}
void main()
{
	link point;
	int select;
	int i,value;
	printf("\n(1)Input a stack data");
	printf("\n(2)Output a stack data");
	printf("\n(3)Exit");
	printf("\nPlease select one=>");
	scanf("%d",&select);
	do
	{
		switch(select)
		{
			case 1:printf("\nPlease input the data=>");
			scanf("%d",&value);			
			push(value);
			printf("\nThe stack content current(top->bottom):");
			print_stack();
			break;
			case 2:value=pop();
			printf("\nThe output value is [%d]",value);
			printf("\n");
			printf("The stack content currnet(top->bottom):");
			print_stack();
			break;
		}
		printf("\n(1)Input a stack data");
		printf("\n(2)Output a stack data");
		printf("\n(3)Exit");
		printf("\nPlease select one=>");
		scanf("%d",&select);
	}while(select!=3);
}
