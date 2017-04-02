#include"stdio.h"
char *strrep(char *s1,char *s2,int pos)
{
    int i,j;
    pos--;
    i=0;
    for(j=pos;s1[j]!='\0';j++)
    	if(s2[i]!='\0')
    		{
    			s1[j]=s2[i];
    			i++;
    		}
    	else
    		break;
    return s1;
}
void main()
{
    char string1[100];
    char string2[50];
    int position;
    printf("\nPlease input original string:");
    gets(string1);
    printf("\nPlease input substitute string:");
    gets(string2);
    printf("\nPlease input substitute position:");
    scanf("%d",&position);
    strrep(string1,string2,position);
    printf("\nThe final string:%s\n",string1);
}
