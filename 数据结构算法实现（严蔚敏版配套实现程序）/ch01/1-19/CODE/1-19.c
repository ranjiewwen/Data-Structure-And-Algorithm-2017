#include"stdio.h"
int partition(char *s1,char *s2,int pos)
{
	int i,j;
	i=pos;
	while(s1[i]==' ')
		i++;
	if(s1[i]!='\0')
		{
			j=0;
			while(s1[i]!='\0'&&s1[i]!=' ')
			{
				s2[j]=s1[i];
				i++;
				j++;
			}
			s2[j]='\0';
			return i;
		}
	 else
		return -1;
}
void main()
{
		char string[50];
		char partition_string[20];
		int position;
		int k;
		printf("\nPlease input strng:");
		gets(string);
		position=0;
		printf("\nPartition result:\n");
		k=0;
		while((position=partition(string,partition_string,position))!=-1)
		{
			k++;
			printf("Partition %d:%s\n",k,partition_string);
		}
}
