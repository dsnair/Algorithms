//Computer Problem 3.2.9

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.1415926535897932384626433832795

double fn(double x, int k)
{
	double d;
	d=atan(x)-x+k*pi;
	return d;
}

main() 
{
	double x[2],x_guess[2], x0;
	double epsilon, delta;
	int N, i, k, j;
	double f, g;
			 
	delta=0.0000001;
	N=100;
	
	for(k=1;k<=10;k++)
	{
		// a negligible value is added to move the guess over to the right hand side of the asymptote
		x_guess[0]=(2*k-1)*pi/2.+0.0000001;
		// a negligible value is subtracted to move the guess over to the inside hand side of the asymptote
		x_guess[1]=(2*k+1)*pi/2.-0.0000001;
		
		for(j=0;j<2;j++)
		{
			x[j]=x_guess[j];
			x0=x_guess[j];	

			for(i=1;i<=N;i++) 
			{
				f=fn(x[j],k);
				g=(fn(x[j]+fn(x[j],k),k)-fn(x[j],k))/fn(x[j],k);// this is the denominator for Steffensen's method
				x[j]=x[j]-f/g;
				epsilon=fabs(x[j]-x0);
				x0=x[j];			
				if(epsilon<delta) i=N+1;
						
			}	
		}
		// either x[0] or x[1] is a finite value. print this value.
		if (fabs(x[0])<10000000.)
		{
			printf("The solution for k=%i is x=%.10f  \n", k, x[0]);	
		}
		else printf("The solution for k=%i is x=%.10f  \n", k, x[1]);		
	}	
}
