//Computer Problem 6.2.1

#include<stdio.h>
#include<math.h>

#define degree 15 //degree of polynomial
#define numnode 29 //number of nodes

/* Terminal commands for GNUplot:
set output "deg15.png"
set terminal png
set grid
set title "The Case of Degree 15"
set yrange [-0.5:1.2]
set key reverse Left outside
plot "deg15.dat" using 1:2 title "f(x)", "deg15.dat"using 1:3 title "p(x)" pt 7
clear
*/

void nodes(int n, double *x);
void funcvals(int n, double *x, double *y);
void polycoeffs(int n, double *x, double *y, double *c);
double NewtonPoly(double xpoint, double *x, double *c);

int main() {
	int i, n;

	n=degree;	
	double x[n+1], y[n+1], c[n+1];
	double xval[numnode+1], yval[numnode+1], error;
	double polyval;

	nodes(n, x);
	funcvals(n, x, y);
	polycoeffs(n, x, y, c);

	n=numnode;
	nodes(n, xval);
	funcvals(n, xval, yval);
	
	printf("##%2s \t %12s \t %12s \t %17s \n", "x", "f(x)", "p(x)", "f(x)-p(x)");
	for(i=0;i<=n;i++) {
		polyval=NewtonPoly(xval[i], x, c);
		error=yval[i]-polyval;
		printf("%lf \t %lf \t %lf \t %lf \n", xval[i], yval[i], polyval, error);
	}
}

//Finding nodes in [-5,5]
void nodes(int n, double *x) {
	double step;
	int i;

	x[0]=-5.0;
	//printf("x[0]=%lf \n", x[0]);

	step=10.0/(double) n; //The range of [-5,5] is 5-(-5)=10
	for(i=1;i<=n;i++) {
		x[i]=x[i-1]+step;
		//printf("x[%d]=%lf \n", i, x[i]);
	}
}

//Evaluating the function at each node
void funcvals(int n, double *x, double *y) {
	int i;

	for(i=0;i<=n;i++) {
		y[i]=1.0/(1.0+(x[i]*x[i]));
		//printf("y[%d]=%lf \n", i, y[i]);
	}
}

//Finding coefficients for Newton interpolating polynomials by method of Divided Differences
void polycoeffs(int n, double *x, double *y, double *c) {
	int j, k;
	double w, p;

	c[0]=y[0];
	//printf("c[0] = %lf \n", c[0]);
	
	for(k=1;k<=n;k++) {
		w=1.0;
		p=0.0;

		for(j=0;j<k;j++) {
			p=p+(c[j]*w);
			w=w*(x[k]-x[j]);
		} 
		c[k]=(y[k]-p)/w;
		//printf("c[%d] = %lf \n", k, c[k]);		
	} 
} 

//Constructing Newton interpolating polynomial. Equation 4 page 310
double NewtonPoly(double xpoint, double *x, double *c) {
	int j;	
	double px, xd;

	px=c[degree];
	for(j=degree-1;j>= 0;j--) {
		xd=xpoint-x[j];
		px=c[j]+px*xd;//equation 4 page 310
	} 
	return px;
}
