#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int stk[100];
int index=0;
int n=5;
void push(int k)
{
 if(index<n)
 {
 	stk[index]=k;
 	index++;
 }	
 else
 {
 	printf("Stack is FULL!!\n");
 }
}
void pop()
{
	if(index!=0)
	{
	 printf("Element popped out is:%d\n",stk[index-1]);
	 index--;
    }
    else
    {
    	printf("Stack is EMPTY!!\n");
	}
    
}
void print()
{
	if(index==0)
	{
		printf("Stack is EMPTY!!\n");
	}
	else
	{
		int i=0;
		printf("The elements in STACK are:\n");
		while(i<index)
		{
			printf("%d\n",stk[i]);
			i++;
		}
	}
}
int main()
{
	int a,k;
	while(1)
	{
		printf("Select your option:\n");
		printf("1.Push\n2.Pop\n3.Print\n4.Exit\n");
		scanf("%d",&a);
		switch(a)
		{
			case 1: printf("Enter the element to be pushed into the stack:");
			        scanf("%d",&k);
			        push(k);
			        break;
			case 2: pop();
			        break;
			case 3: print();
			        break;
			case 4:	exit(0);
		}
	}
	getch();
}
