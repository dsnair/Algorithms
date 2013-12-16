#include <stdio.h>
#include <math.h>

main()
{
	int k;	
	long n, i, j;
	double elts, sum1, sum2, matrix;

	printf("%s \t %s \t %10s \n", "k", "n", "matrix");

	for(k=1;k<=4;k++)
	{
		n=(long)pow(10.0, (float)k);	
		sum2=0.;

		for(i=1;i<=n;i++)
		{
			sum1=0.;
			for(j=1;j<=n;j++)
			{
				//computing individual elements of Hw
				elts=(1./3.)*(1./(double)(i+j-1));
				//adding up previous elements to finish the matrix multiplication of H and w
				sum1+=elts;
			}
		sum2+=(1./3.)*sum1;//multiplying w^T with Hw
		}
		matrix=sum2;//this is the matrix w^T*Hw
		printf("%d \t %ld \t %.14e \n", k, n, matrix);
	}
}
