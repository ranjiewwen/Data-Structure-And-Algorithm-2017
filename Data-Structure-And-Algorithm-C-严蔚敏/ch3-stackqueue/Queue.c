#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int index=0;
int n=5;
int q[100];
void enqueue(int k)
{
	if(index<n)
	{
		q[index]=k;
		index++;
	}
	else
	{
		printf("Queue is FULL!!\n");
	}
}
void dequeue()
{
	if(index==0)
	{
		printf("Queue is EMPTY!!\n");
	}
	else
	{
		int i=1;
		printf("The element removed is:%d\n",q[0]);
		while(i<index)
		{
			q[i-1]=q[i];
			i++;
		}
		index--;
	}
}
void print()
{
	if(index==0)
	{
		printf("Queue is EMPTY!!\n");
	}
	else 
	{
     int i=0;
     printf("The elements are:\n");
	 while(i<index)
	 {
	 	printf("%d\n",q[i]);
	 	i++;
	 }		
	}
}
void main()
{
	int a,k;
	while(1)
	{
		printf("Select your option:\n");
		printf("1.Enqueue\n2.Dequeue\n3.Print elements\n4.Exit\n");
		scanf("%d",&a);
		switch(a)
		{
			case 1: printf("Enter the element to be inserted:\n");
			        scanf("%d",&k);
			        enqueue(k);
			        break;
			case 2: dequeue();
			        break;
			case 3: print();
			        break;
			case 4: exit(0);
			        break;
		}
	}
	getch();
}
