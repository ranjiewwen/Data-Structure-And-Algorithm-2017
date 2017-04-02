#include "stdio.h"
#define  MAX_TERMS 100    /* size of terms array */
typedef  struct {
	float  coef;
	int expon;
}  polynomial;
polynomial  terms[ MAX_TERMS];
int avail = 0;
int COMPARE(int coef1,int coef2)
{
	if(coef1<coef2)
		return -1;
	else if(coef1==coef2)
		return 0;
	else
		return 1;
}
void attach (float coefficient, int exponent)
{  /* 加一个新项到多项式中 */
     if (avail > MAX_TERMS)  {
        printf("Too many terms in the polynomial \n");
        exit(1);
     }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}
void padd( int starta, int  finisha, int startb, int finishb, 
		  int *startd,int *finishd)
{ /* A(x)＋B(x)＝D (x) */
    float coefficient;
    *startd = avail;
    while ( starta <= finisha && startb <=finishb)
        switch (COMPARE(terms[starta].expon, terms[startb].expon))  {
           case -1:  /* a 指数小于 b指数*/
              attach(terms[startb].coef, terms[startb].expon);
                  startb ++;
                  break;
           case 0:  /*两指数相等*/
                  coefficient = terms[starta].coef + terms[startb].coef;
                  if (coefficient)
                          attach(coefficient, terms[starta].expon);
                   starta++;
                   startb ++;
                   break;
          case 1:  /* a指数大于b指数*/
                    attach(terms[starta].coef,terms[starta].expon);
                    starta++;
	}
	/* 把其余的A(x)相加 */
    for (; starta <= finisha;  starta++)
            attach(terms[starta].coef,terms[starta].expon);
	/* 把其余的B(x)相加 */
    for (; startb <= finishb;  startb++)
           attach(terms[startb].coef,terms[startb].expon);
    *finishd = avail -1;
}
void main()
{
	int startd,finishd;
	padd(4,1,3,2,&startd,&finishd);
}
