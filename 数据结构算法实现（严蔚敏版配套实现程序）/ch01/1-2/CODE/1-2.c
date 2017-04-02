#include"stdio.h"
void main()
{
	int  Employee[10]={27000,32000,32500,27500,30000,29000,31000,32500,30000,26000};
	int  Index;
	int  NewSalary;
	int  Selection;
	while(1)
	{
		printf("===================================================\n");
		printf("=Simple Employee Salary Management System         =\n");
		printf("=1.Display employee salary                        =\n");
		printf("=2.Modify employee salary                         =\n");
		printf("=3.Quit                                           =\n");
		printf("Please input your choose:");
		scanf("%d",&Selection);
		if(Selection==1||Selection==2)
		{
			printf("**Please input the employee number:");
			scanf("%d",&Index);
			if(Index<10)
			{
			     printf("**Employee Number is %d.",Index);
			     printf("The Salary is %d\n",Employee[Index]);
			}
			else
			{
					printf("##The error employee number!\n");
					exit(1);
			}
		}
		switch(Selection)
		{
		    case  1:
                break;
             case   2:
                printf("**Please input new salary:");
                scanf("%d",&NewSalary);
                Employee[Index]=NewSalary;
                break;
             case    3:
                exit(1);
                break;
        }
        printf("\n");
   }
}
