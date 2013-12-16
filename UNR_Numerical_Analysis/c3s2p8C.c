//Computer Problem 3.2.8C

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

main() 
{
	double complex z, z0;
	int j, N;
	double complex f, df;
	double epsilon, delta;
	double Rez, Imz;

	z0=1+0*I;
	delta=.00000001;
	N=200;
	z=z0;
	printf("%1s\t  %6s\t  %6s\n","#", "Real","Imaginary");
	
	for(j=1;j<=N;j++) 
	{
		f=cpow(z,4)+cpow(z,2)+2+3*I;
		df=4*cpow(z,3)+2*z;
		z=z0-f/df;
		epsilon=cabs(z-z0);
		z0=z;
		Rez=creal(z);	
		Imz=cimag(z);
		printf("%d \t %lf \t %lf i \n", j, Rez, Imz);	 
		if(epsilon<delta) j=N+1;
	}	
}
