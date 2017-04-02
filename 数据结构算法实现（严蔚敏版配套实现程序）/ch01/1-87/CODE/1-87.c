#include "stdio.h"
#define num_arr	5
typedef struct attr
{
	int key;
	char name[10];
}ArrType ;
void sort(ArrType  A[])
{
	int	i;
	ArrType B[num_arr];
	for(i=0; i<num_arr ; i++)
    	B[A[i].key] = A[i];
	for(i=0; i<num_arr ; i++)
	   printf("%s\n",B[i].name);
}
void main()
{
    ArrType c[num_arr]={{4,"John"},{1,"Jane"},{0,"Alice"},{2,"Peter"},{3,"Tom"}};
	sort(c);
}
