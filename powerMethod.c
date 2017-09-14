/* Calculate the largest eigenvalue of a matrix (improved) */

# include <stdio.h>
# include <math.h>
# include <stdlib.h>  // used for random number generation
# include <time.h>  // used to obtain program run time

# define n 20 /* size of matrix and vectors */

// define global variable
double matA[n][n];

// declare functions
void GenMatrix();
double MatVecMult(double vecZ[n], int counter);
double Normalize(double vecY[n], int counter);
double Rayleigh(double unitY[n]);

double main() {	
	double lambda0 = 1.0;  /* initial eigenvalue guess */
	double tol = 0.00005;  // allowed error tolerance
	int iter = 0;  // initial iteration
	double vecZ[n], y[n], yhat[n], lambda;
	clock_t start, stop;
	int i;

	// set error as a multiple of tolerance so the loop is performed at least once
	double error = 10.0 * tol;
	
	// set maxIter to avoid infinite looping if the error tolerance isn't reached
	int maxIter = 100;  // maximum allowed iterations	
	
	start = clock();

	GenMatrix();		
	
	for (i = 0; i < n; i++) {
		vecZ[i] = 2.0;  /* set initial eigenvector guess */
	}

	for (i = 0; i < n; i++) {
		y[i] = MatVecMult(vecZ, i);
	}

	printf("%3s \t %18s \n", "lambda", "error");

	while (iter <= maxIter && error > tol) {
		for (i = 0; i < n; i++) {
			yhat[i] = Normalize(y, i);
		}
		lambda = Rayleigh(yhat);	
		error = fabs((lambda - lambda0) / lambda);  /* relative error */		
		printf("%3f \t %13f \n", lambda, error);
		lambda0 = lambda;  // update old eigenvalue with new one
		for (i = 0; i < n; i++) {
			y[i] = MatVecMult(yhat, i);  // update old eigenvector with new one
		}
		iter = iter + 1;
	}

	printf("Number of iterations: %d \n", iter);

	stop = clock();
	printf("Elapsed time: %f seconds \n", (double)(stop - start) / CLOCKS_PER_SEC);
}

/* randomly generate matrix 'matA' */

void GenMatrix() {
	int i, j;
	srand(time(NULL));  // randomize seed
    for (i = 0; i < n; i++) {
    	for (j = 0; j < n; j++) {
    		matA[i][j] = rand() % 100 + 1;  // random number between [1, 100]        	
    	}        
    }
}

/* 'MatVecMult' multiplies matrix 'matA' with column vector 'vecZ' to obtain column vector 'vecY' */

double MatVecMult(double vecZ[n], int counter) {
	int i, j;
	double vecY[n], *p;
	for (i = 0; i < n; i++) {
		vecY[i] = 0.0;  // initialize vecY to 0
		for (j = 0; j < n; j++) {
			vecY[i] = vecY[i] + matA[i][j] * vecZ[j];
		}
	}
	p = &vecY[counter];
	return p[0];
}

/* 'Normalize' first calculates the infinity-norm of column vector 'vecY' i.e., 
max(vecY). Then, it normalizes 'vecY' to find a unit vector 'unitY' along its 
direction. */

double Normalize(double vecY[n], int counter) {
	int i;
	double unitY[n], *p;
	/* calculate norm */
	double maxVal = vecY[0];  // assume 1st element is the maximum
    for (i = 1; i < n; i++) {
    	if (vecY[i] > maxVal) {
    		maxVal = vecY[i];
    	}
    }
    /* find unit vector */
    for (i = 0; i< n; i++) {
		unitY[i] = vecY[i] / maxVal;
	}
	p = &unitY[counter];
	return p[0];
}

/* 'Rayleigh' calculates the Rayleigh quotient i.e.,
((unitY)^t * matA * unitY) / ((unitY)^t * unitY) to estimate eigenvalue 'lambda' */

double Rayleigh(double unitY[n]) {
	int i, j;
	double prod[n], lambda, *p;
	double num = 0.0, deno = 0.0;
	/* multiply row vector (unitY)^t with matrix 'matA' to obtain column vector 'prod' */
	for (j = 0; j < n; j++) {
		prod[j] = 0.0;
		for (i = 0; i < n; i++) {
			prod[j] = prod[j] + unitY[i] * matA[i][j];
		}
	}
	/* multiply column vector 'prod' with row vector 'unitY' to obtain scalar 'num' */
	for (i = 0; i < n; i++) {
		num = num + prod[i] * unitY[i];
	}
	/* multiply (unitY)^t * unitY to get scalar 'deno' */
	for (i = 0; i < n; i++) {
		deno = deno + unitY[i] * unitY[i];
	}
	/* obtain eigenvalue */
	lambda = num / deno;
	p = &lambda;
	return *p;
}
