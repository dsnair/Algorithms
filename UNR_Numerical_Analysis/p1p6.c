#include <stdio.h>
#include <math.h>

# define n 50

main()
{
        int i, j, k;
        double elts, c[n], Bx[n], sum;
        double r[n], x[n], p[n], rold, rnew;
        double Bp[n], alpha, deno;
        double mod_cBx;

        printf("%2s \t %24s \n", "k", "|c-Bx|"); 

/* SET UP : 
Martix A is -2 along the diagonal, 1 on the top off-diagonal, 0 everywhere else. 
Take b=w=1/3, then column vector c=A^T*b is -2/3 in the first entry and -1/3 everywhere else.
Matrix B=A^T*A is 4 in 1st row - 1st column, other diagonal elements are 5, 
both off-diagonal entries are -2, everywhere else has 0.
*/
        //This is the initial guess vector x=0
 	for(i=0;i<n;i++) x[i]=0;

        //This is matrix c = A^T*w
	c[0]=-2.0/3.0;
        for(i=1;i<n;i++) c[i]=-1.0/3.0;
       
        //constructing matrix Bx
        for(i=1;i<=n;i++)
        {
                sum=0.;
                for(j=1;j<=n;j++)
                {
			elts=0.;
                       	if(i==1 && j==1) elts=4.0;
		       	if(i!=1 && j!=1 && i==j) elts=5.0;
		       	if(j==i+1 || j==i-1) elts=-2.0;
			sum+=elts*x[j-1];
                }
                Bx[i-1]=sum; //matrix Bx is getting its entries filled in here
        }
       
/* Applying Conjugate Gradient Method to Solve Bx=c  */
        for(i=0;i<n;i++)
        {
                r[i]=c[i]-Bx[i]; //computing the residual c-Bx
                p[i]=r[i]; //p is the direction vector
        }

        rold=0.;
        for(i=0;i<n;i++) rold+=r[i]*r[i];
               
        //constructing modulus of vector c-Bx for k=0
        k=0;
        mod_cBx=0.;

        for(i=0;i<n;i++) mod_cBx+=(c[i]-Bx[i])*(c[i]-Bx[i]);       
        mod_cBx=sqrt(mod_cBx);
        printf("%2d \t %24.14e \n", k, mod_cBx); 

        for(k=1;k<=50;k++)
        {
               //This is matrix Bp
               for(i=1;i<=n;i++)
       	       {
		        sum=0.;
		        for(j=1;j<=n;j++)
		        {
				elts=0.;
		               	if(i==1 && j==1) elts=4.0;
			       	if(i!=1 && j!=1 && i==j) elts=5.0;
			       	if(j==i+1 || j==i-1) elts=-2.0;
				sum+=elts*p[j-1];
		        }
		        Bp[i-1]=sum; //matrix Bp is getting its entries filled in here
        	}

                deno=0.;
                for(i=0;i<n;i++) deno+=p[i]*Bp[i]; //multiplying p^T*Bp

                alpha=rold/deno;
               
                rnew=0.;
                for(i=0;i<n;i++)
                {
			//iteratively computing values of x1,x2,... given the initial guess x0
                        x[i]=x[i]+alpha*p[i]; 
                        r[i]=r[i]-alpha*Bp[i]; //computing new residuals
                        rnew+=r[i]*r[i];
                }
       
                for(i=0;i<n;i++) p[i]=r[i]+(rnew/rold)*p[i]; //new direction vector
                rold=rnew;

                for(i=1;i<=n;i++)
        	{
		        sum=0.;
		        for(j=1;j<=n;j++)
		        {
				elts=0.;
		               	if(i==1 && j==1) elts=4.0;
			       	if(i!=1 && j!=1 && i==j) elts=5.0;
			       	if(j==i+1 || j==i-1) elts=-2.0;
				sum+=elts*x[j-1];
		        }
			//matrix Bx is getting its entries filled in here with better guess vectors
		        Bx[i-1]=sum; 
        	}
       	        
                //constructing modulus of vector c-Bx for k = 1 to n
                mod_cBx=0.;
                for(i=0;i<n;i++) mod_cBx+=(c[i]-Bx[i])*(c[i]-Bx[i]);
                mod_cBx=sqrt(mod_cBx);
                printf("%2d \t %24.14e \n", k, mod_cBx); 
        }
        //Printing the solution
	printf("The solution is \n");
        for(i=0;i<n;i++) printf("%2d %.14lf \n", i, x[i]);
}
