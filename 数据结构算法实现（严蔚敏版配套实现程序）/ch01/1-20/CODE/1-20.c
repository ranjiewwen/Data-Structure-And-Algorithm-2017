#include "stdio.h"
#include <string.h>
#define   MAX_SIZE   100
void insert (char *s,  char  *t,  int i)
{
	char string[MAX_SIZE],  *temp =string;
	if  ( i < 0||i > strlen (s) )
    {
		printf ( "插入位置不正确！\n");
		exit (1);
	}
	if  (!strlen (s))
		strcpy (s,  t);
	else   if (strlen (t))  {
		strncpy (temp, s, i);
		strcat (temp, t) ;
		strcat (temp,  (s + i ));
		strcpy (s, temp );
	}
}
void main ()
{
	char s[]="Sitplease.";
	char t[]=" down ";
	insert(s,t,3);
	printf("%s",s);
	printf ( "\n");
}
