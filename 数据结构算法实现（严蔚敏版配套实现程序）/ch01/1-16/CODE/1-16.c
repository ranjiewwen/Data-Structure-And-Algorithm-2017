#include"stdio.h"
char *strdel(char *s,int pos,int len)
{
    int i;
    pos--;
    for(i=pos+len;s[i]!='\0';i++)
    	s[i-len]=s[i];
    s[i-len]='\0';
    return s;
}
void main()
{
		char string[50];
		int position;
		int length;
		printf("\nPlease input original string:");
		gets(string);
		printf("\nPlease input delete position:");
		scanf("%d",&position);
		printf("\nPlease input delete length:");
		scanf("%d",&length);
		strdel(string,position,length);
		printf("\nThe final string:%s",string);
}
