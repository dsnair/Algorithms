//Computer Problem 2.3.2

#include <stdio.h>
#include <math.h>

main() {
	double Y[21];
	int n;
	double x;
	x=1.0;
	double Z;
	
	printf("%3s\t %23s\t %23s\n","n", "Y[n]", "|Y[n]/Y[n-1]|");

	Y[0]=0.0882569642;
	Y[1]=-0.7812128213;
	printf("%3s\t  %23.14e\n %3s\t  %23.14e\n","0", Y[0],"1", Y[1]);	

	for(n=2;n<21;n++) {
           Y[n]=2.0*((double) n-1.0)*(1.0/x)*Y[n-1]-Y[n-2];
	   Z=abs(Y[n]/Y[n-1]);
	   printf("%3d\t %23.14e\t %23.14e\n", n, Y[n], Z);
	}
} 
