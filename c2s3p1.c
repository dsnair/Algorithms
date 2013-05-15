//Computer Problem 2.3.1

#include <stdio.h>
#include <math.h>

main() {
	double A[21], B[21], C[21];
	int n;

	A[0]=pow(2.0,-23);
	A[1]=1.0;
	B[0]=1.0;
	B[1]=1.0;

	for(n=2;n<20;n++) {
			A[n]=n*A[n-1]+A[n-2];
			B[n]=n*B[n-1]+B[n-2];
			C[n]=A[n]/B[n];
	}

	printf("%3s\t %23s\t  %23s\t  %23s\n","n","A[n]","B[n]","A[n]/B[n]");

	for(n=0;n<20;n++) {
	   printf("%3d\t  %23.14e\t  %23.14e\t  %23.14e\n", n, A[n], B[n], C[n]);
	}
} 
