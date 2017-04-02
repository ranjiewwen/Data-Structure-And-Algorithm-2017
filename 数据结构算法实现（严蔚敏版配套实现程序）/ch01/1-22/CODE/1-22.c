#include "stdio.h"
#include <string.h>
void catstr(char *des,char *sour)
{
  int end=strlen(des);
  int i,j,num;
  num=strlen(sour);	
	for(i=end,j=0;j<num;i++,j++)
		des[i]=sour[j];
	for(i=0;i<end+num;i++)
	   printf("%c",des[i]);
	printf("\n");
}
void main ()
{
	char s[]="Sit down";
	char t[]=" please!";
	catstr(s,t);
}
