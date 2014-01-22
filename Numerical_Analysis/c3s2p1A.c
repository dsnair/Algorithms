//Computer Problem 3.2.1A

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.1415926535897932384626433832795

main() 
{
	double x, x0;
	int j, N;
	double f, df;
	double epsilon, delta;
		
	delta=.00000001;
	N=100;
	printf("The nearest root to x0=4.5 is\n");
	printf("%1s\t  %6s\t %10s\n","#", "x", "f(x)");
	
	x0=4.5;
	x=x0;	
	for(j=1;j<=N;j++) 
	{
		f=atan(x)-x+pi;
		df=(1/(x*x+1))-1;
		x=x0-f/df;
		epsilon=fabs(x-x0);
		x0=x;
		printf("%d\t %.9lf\t %.9lf\n", j, x, f);
		if(epsilon<delta) j=N+1;
	}	
}
