#include"stdio.h"
char *strcmp(char *s1,char *s2)
{
    int i,j;
    for(i=0;s1[i]==s2[i];i++)
        if(s1[i]=='\0'&&s2[i]=='\0')
            return 0;
    if(s1[i]>s2[i])
        return 1;
    return -1;
}
void main()
{
		char s1[50];
		char s2[50];
		int compare;
		printf("\nPlease input string(1):");
		gets(s1);
		printf("\nPlease input string(2):");
		gets(s2);
		compare=strcmp(s1,s2);
		printf("\nString(1):%s",s1);
		printf("\nString(2):%s",s2);
		printf("\nCompare result:");
		switch(compare)
		{
		  case 0:
		      printf("\nString(1)=String(2)\n");
		      break;
          case 1:
		      printf("\nString(1)>String(2)\n");
		      break;
          case -1:
		      printf("\nString(1)<String(2)\n");
		      break;
    }
}
