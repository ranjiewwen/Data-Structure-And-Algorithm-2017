#include"stdio.h"
char *strcpy(char *s1,char *s2)
{
  int i;
  for(i=0;s2[i]!='\0';i++)
  	s1[i]=s2[i];
  s1[i]='\0';
  return s1;	
}
void main()
{
	char string[50];
	char copystring[50];
	printf("\nPlease input string:");
	gets(string);
	strcpy(copystring,string);
	printf("\nString:%s",string);
	printf("\nCopystring:%s",copystring);
}
