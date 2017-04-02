#include "stdio.h"
#include <string.h>
int  nfind ( char  *B,  char  *A )
{
  int  i, j, start  = 0;
  int  lasts = strlen (B)-1;
  int  lastp = strlen (A)-1 ;
  int  endmatch =  lastp;
  for(i=0;endmatch<=lasts;endmatch++,start++)
  {
      if ( B[endmatch] == A[lastp])
             for (j=0,i=start;j<lastp&&B[i]==A[j];)
              i++,j++;
      if ( j == lastp )
             return (start+1);    /*³É¹¦  */
  }
  /*printf("%d %d %d",lasts,lastp,start); */
  if(start==0)
      return  -1;
}
void main ()
{
	char s[]="Sit please";
	char t[]="please";
	int po=nfind(s,t);
	printf("%d",po);
	printf("\n");
}
