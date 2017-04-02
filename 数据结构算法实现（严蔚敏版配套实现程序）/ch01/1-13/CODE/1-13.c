#include"stdio.h"
int Strlen(char *s)
{
	int i;
	for(i=0;s[i]!='\0';)
		i++;
	return i;
}
void main()
{
	char string[50];
	int length;
	printf("\nPlease input string:");
	gets(string);
	length=Strlen(string);
	printf("\nThe input string length is %d",length);	
}
