//Computer Problem 3.5.5

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define D 20 //This is the degree of wilkinson's polynomial

double complex f(double complex *coeff, int degree, double complex x);
double complex df(double complex *coeff, int degree, double complex x);
double complex newton(double complex x, double complex  poly, double complex deriv);
double distance(double complex  x, double complex x0);
void horner(double complex *coeff, double complex root, int degree);
double complex guess();
double complex rho(double complex *coeff, int degree);

main() 
{
	double complex x;
	double complex x0, root;
	int i, j, degree;
	double complex poly, deriv;
	double complex epsilon, delta, radius;
	double complex coeff[D+1], soln[D+1];

	x0=guess();
	delta=.000000001L+0.0*I;
	x=x0;
	degree=D;
	
	//These are the coefficients of wilkinson's polynomial
	coeff[0]=2432902008176640000.0L+0.0L*I;
	coeff[1]=-8752948036761600000.0L+0.0L*I;
	coeff[2]=13803759753640704000.0L+0.0L*I;
	coeff[3]=-12870931245150988800.0L+0.0L*I;
	coeff[4]=8037811822645051776.0L+0.0L*I;
	coeff[5]=-3599979517947607200.0L+0.0L*I;
	coeff[6]=1206647803780373360.0L+0.0L*I;
	coeff[7]=-311333643161390640.0L+0.0L*I;
	coeff[8]=63030812099294896.0L+0.0L*I;
	coeff[9]=-10142299865511450.0L+0.0L*I;
	coeff[10]=1307535010540395.0L+0.0L*I;
	coeff[11]=-135585182899530.0L+0.0L*I;
	coeff[12]=11310276995381.0L+0.0L*I;
	coeff[13]=-756111184500.0L+0.0L*I;
	coeff[14]=40171771630.0L+0.0L*I;
	coeff[15]=-1672280820.0L+0.0L*I;
	coeff[16]=53327946.0L+0.0L*I;
	coeff[17]=-1256850.0L+0.0L*I;
	coeff[18]=20615.0L+0.0L*I;
	coeff[19]=-210.0L+0.0L*I;
	coeff[20]=1.0L+0.0L*I;

	for(i=0;i<D;i++)
	{
		x=guess();
		epsilon=2.0;
		radius=rho(coeff, degree);
		j=1;
		while(cabsl(epsilon)>cabsl(delta))
		{
			//Print an error if the guess produces NAN or inf or is greater than the radius given by Theorem 3.5.3
			if(j%1000==0 || cabsl(x)>2.0*(cabsl(radius)) || isnan(cabsl(x)) || isinf(cabsl(x)))
			{
				printf("Make a new guess\n");			
				x=radius*(2.0*random()/RAND_MAX-1.0);
				x0=2.0*x;
			}
			poly=f(coeff, degree, x);
			deriv=df(coeff, degree, x);
			x0=x;
			x=newton(x, poly, deriv);
			epsilon=distance(x,x0);
			j++;
		}
		root=x;
		soln[i]=root;
		printf("solution(%d): %25.14Le +%25.14Le*I\n", i,creall(soln[i]),cimagl(soln[i]));
		horner(coeff, root, degree);
		degree=degree-1;
	}
}

double distance(double complex x, double complex x0)
{
	double d;
	d=cabsl(x-x0);
	return d;	
}

//This function constructs the polynomial with the given coefficients
double complex f(double complex *coeff, int degree, double complex x)
{
	double complex sum;
	int k;
	sum=0;	

	for(k=0;k<=degree;k++)
	{
		sum+=coeff[k]*cpow(x,(double complex ) k);
	}
	return sum;		
}

//This function takes the derivative of the polynomial
double complex df(double complex *coeff, int degree, double complex x)
{
	double complex sum;
	int k;
	sum=0;	

	for(k=1;k<=degree;k++)					
	{
		sum+=coeff[k]*k*cpow(x,(double complex ) (k-1));
	}
	return sum;
}

//This function applies the Newton method on the polynomial
double complex newton(double complex x, double complex poly, double complex deriv)
{
	x=x-poly/deriv;
	return x;
}

//This function is inspired from the pseudocode for Horner's Algorithm given on page 112	
void horner(double complex  *coeff, double complex  root, int degree)
{
	int k;
	double complex coeff2[degree+1-1];

	coeff2[degree-1]=coeff[degree];

	for(k=degree-2;k>=0;k--)	
	{
		coeff2[k]=coeff[k+1]+root*coeff2[k+1];
	}

	coeff[degree]=0;

	for(k=0;k<=degree;k++)
	{
		coeff[k]=coeff2[k];
	}		
}

//Enter a guess for the application of Newton's method
double complex guess()
{
	double complex x0;
	x0=1.001+0.15*I;
	return x0;
}

//This function applies Theorem 3.5.3
double complex rho(double complex *coeff, int degree)
{
	int k;
	double complex max, radius;
			
	max=cabsl(coeff[0]);

	for(k=1;k<degree;k++)
	{
		if(cabsl(coeff[k])>cabsl(max))
		  max=cabsl(coeff[k]);
	}
	radius=1.0+(1.0/cabsl(coeff[degree]))*max;
	return radius;
}
