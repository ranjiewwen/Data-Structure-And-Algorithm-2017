#include"stdio.h"
char *substr(char *s,int pos,int len)
{
    char s1[50];
    int i,j,endpos;
    pos--;
    endpos=pos+len-1;
    for(i=pos,j=0;i<=endpos;i++,j++)
    	s1[j]=s[i];
    s1[len]='\0';
    printf("\nThe substring is '%s'\n",s1);
    return s1;
}
void main()
{
		char string[100];
		char *substring;
		int position;
		int length;
		printf("\nPlease input string:");
		gets(string);
		printf("Please input start position:");
		scanf("%d",&position);
		printf("Please input substring length:");
		scanf("%d",&length);
		substring=substr(string,position,length);		
}
