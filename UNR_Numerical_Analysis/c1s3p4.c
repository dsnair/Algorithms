//Computer Problem 1.3.4

#include <stdio.h>
#include <math.h>

/* In terminal type:
gcc -o filename filename.c -lm //This compiles the code
./filename >> filename.out //This creates an output file
./filename.out //This prints the output file in terminal
*/

main() {
	double beta=pow(1.0-sqrt(3.0),-1);
	double alpha=pow(2.0,-23);
	double x[101], y[101], z[101];
	int n;

	x[1]=1.0;
	x[2]=1.0-sqrt(3.0);

	for(n=3;n<=100;n++) {
	      x[n]=2*(x[n-1]+x[n-2]);
	}

	for (n=1;n<=100;n++) {
		y[n]=beta*pow(1.0-sqrt(3.0),n);
		z[n]=alpha*pow(1.0+sqrt(3.0),n)+y[n];
	}

	printf("%3s\t %23s\t  %23s\t  %23s\t  %23s\n","n","x[n]","y[n]","z[n]","x[n]-z[n]"); // '\n' is for new line

	for(n=1;n<=100;n++) {
	   printf("%3d\t  %23.14e\t  %23.14e\t  %23.14e\t  %23.14e\n",n,x[n],y[n],z[n],x[n]-z[n]); // '\t' is for tab
	}
} 
