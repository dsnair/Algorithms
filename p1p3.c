#include <stdio.h>
#include <math.h>

# define n 1000

main()
{
        long  i, j;
        double elts, b[n], Hx[n], sum;
        double r[n], x[n], p[n], rold, rnew;
        double Hp[n], alpha, deno;
        double mod_wx, mod_bHx;
        int k;

        printf("%2s \t %24s \t %24s \n", "k", "|w-x|", "|b-Hx|"); // 's' is for strings

/* Set-up */

        //constructing initial guess column vector x=0
        for(i=0;i<n;i++) x[i]=0;

        //constructing matrix b = Hw
        for(i=1;i<=n;i++)
        {
                sum=0.;
                for(j=1;j<=n;j++)
                {                      
                        elts=(1./3.)*(1./(double)(i+j-1));//multiplying individual elements of H & w
                        sum+=elts; //adding up these elements to finish the matrix multiplication
                }
                b[i-1]=sum; //matrix b is getting its entries filled in here
        }
       
        //constructing matrix Hx
        for(i=1;i<=n;i++)
        {
                sum=0.;
                for(j=1;j<=n;j++)
                {
                        elts=x[j-1]*(1./(double)(i+j-1));//multiplying individual elements of H & x                 
                        sum+=elts; //adding up these elements to finish the matrix multiplication
                }
                Hx[i-1]=sum; //matrix Hx is getting its entries filled in here
        }
       
/* Conjugate Gradient Method for Hilbert Matrix 1/(i+j-1) */
        for(i=0;i<n;i++)
        {
                r[i]=b[i]-Hx[i]; //computing the residual b-Hx
                p[i]=r[i]; //p is the direction vector
        }

        rold=0.;
        for(i=0;i<n;i++) rold+=r[i]*r[i];
               
        //constructing modulus of vectors w-x and b-Hx for k=0
        k=0;
        mod_wx=0.;
        mod_bHx=0.;
        for(i=0;i<n;i++)
        {
        	mod_wx+=((1./3.)-x[i])*((1./3.)-x[i]);
        	mod_bHx+=(b[i]-Hx[i])*(b[i]-Hx[i]);
        }
        mod_wx=sqrt(mod_wx);
        mod_bHx=sqrt(mod_bHx);
        printf("%2d \t %24.14e \t %24.14e \n", k, mod_wx, mod_bHx);//'e' is for scientific notation in double

        for(k=1;k<=50;k++)
        {
                // constructing matrix Hp
                for(i=1;i<=n;i++)
                {
                        sum=0.;
                        for(j=1;j<=n;j++)
                        {
                                elts=p[j-1]*(1./(double)(i+j-1));//multiplying individual elements of H & p
                                sum+=elts; //adding up these elements to finish the matrix multiplication
                        }
                        Hp[i-1]=sum; //matrix Hp is getting its entries filled in here
                }

                deno=0.;
                for(i=0;i<n;i++) deno+=p[i]*Hp[i]; //multiplying p^T*Hp

                alpha=rold/deno;
               
                rnew=0.;
                for(i=0;i<n;i++)
                {
			//iteratively computing values of x1,x2,... given the initial guess x0
                        x[i]=x[i]+alpha*p[i]; 
                        r[i]=r[i]-alpha*Hp[i]; //computing new residuals
                        rnew+=r[i]*r[i];
                }
       
                for(i=0;i<n;i++) p[i]=r[i]+(rnew/rold)*p[i]; //new direction vector
                rold=rnew;

                for(i=1;i<=n;i++)
                {
                        sum=0.;
                        for(j=1;j<=n;j++)
                        {
                                elts=x[j-1]*(1./(double)(i+j-1));//multiplying individual elements of H & x
                                sum+=elts; //adding up these elements to finish the matrix multiplication
                        }
                        Hx[i-1]=sum;//matrix Hx is getting its entries filled in here
                }
               
                //constructing modulus of vectors w-x and b-Hx
            	mod_wx=0.;
                mod_bHx=0.;
                for(i=0;i<n;i++)
                {
                        mod_wx+=((1./3.)-x[i])*((1./3.)-x[i]);
                        mod_bHx+=(b[i]-Hx[i])*(b[i]-Hx[i]);
                }
                mod_wx=sqrt(mod_wx);
                mod_bHx=sqrt(mod_bHx);
                if(k==1 || k==2 || k==3 || k==50) printf("%2d \t %24.14e \t %24.14e \n", k, mod_wx, mod_bHx); 
        }
        //checking if the solution is x=1/3 at a chosen position
        printf("x = %.14lf \n %.14lf \n %.14lf ... \n", x[0], x[19], x[772]);
}
