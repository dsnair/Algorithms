/* Solve a system of linear equations, Ax = b, where A is a random, diagonally dominant matrix, and b is A times 
a vector of ones*/

# include <stdio.h>
# include <math.h>
# include <stdlib.h>  // used for random number generation

# define n 20 /* size of matrix and vectors */

// define global variable
double matA[n][n];

// declare functions
void DiagDomMat();
double MatVecMult(double vecZ[n], int counter);
double Jacobi(double vecX[n], double vecB[n], int counter);
double Norm(double vecX[n]);

double main() {
	int i;
	double x0[n], x[n], b[n];
	double tol = 0.00005;  /* allowed error tolerance */
	int iter = 0;  // initial iteration
	double error = 10.0 * tol;
	int maxIter = 100;  // maximum allowed iterations

	DiagDomMat();

	/* obtain 'b' */
	for (i = 0; i < n; i++) {
		x0[i] = 1.0;  // initial guess solution to solve Ax = b
	}
	for (i = 0; i < n; i++) {
		b[i] = MatVecMult(x0, i);  // 'b' is 'matA' times vector of ones
	}

	while (iter <= maxIter && error > tol) {
		for (i = 0; i < n; i++) {
			x[i] = Jacobi(x0, b, i);
		}
		error = fabs((Norm(x) - Norm(x0)) / Norm(x));  // relative error
		for (i = 0; i < n; i++) {
			x0[i] = x[i];  // update old solution with new one
		}
		iter = iter + 1;
	}

	printf("The solution of Ax = b is x = \n");
	for (i = 0; i < n; i++) {
		printf("%f \n", x[i]);
	}

	printf("Number of iterations: %d \n", iter);
	printf("Error: %3f \t \n", error);
}

/* 'DiagDomMat' generates a random diagonally dominant matrix 'matA' */

void DiagDomMat() {
	int i, j, sum[n], offDiagSum[n];;
	srand(time(NULL));  // randomize seed
    for (i = 0; i < n; i++) {
    	sum[i] = 0;
    	offDiagSum[i] = 0;
    	for (j = 0; j < n; j++) {
    		matA[i][j] = rand() % 100 + 1;  // random number between [1, 100]
    		sum[i] = sum[i] + matA[i][j];  // sum of each row
    		if (j != i) {
    			// sum of off-diagonal entries in each row
    			offDiagSum[i] = offDiagSum[i] + matA[i][j];
    		}
    	}
    	// random number between [offDiagSum, sum] for diagonal dominance
    	matA[i][i] = rand() % (sum[i] + 1 - offDiagSum[i]) + offDiagSum[i];    	
    }
}

/* 'MatVecMult' multiplies a matrix 'matA' with a vector 'vecZ' */

double MatVecMult(double vecZ[n], int counter) {
	int i, j;
	double vecY[n], *p;
	for (i = 0; i < n; i++) {
		vecY[i] = 0.0;
		for (j = 0; j < n; j++) {
			vecY[i] = vecY[i] + matA[i][j] * vecZ[j];
		}
	}
	p = &vecY[counter];
	return p[0];
}

/* 'Jacobi' solves Ax = b using Jacobi iterative method */

double Jacobi(double vecX[n], double vecB[n], int counter) {
	int i, j;
	double sum, newX[n], *p;
	for (i = 0; i < n; i++) {
		sum = 0.0;
		for (j = 0; j < n; j++) {
			if (j != i) {
				sum = sum + matA[i][j] * vecX[j];
			}
		}
		newX[i] = (vecB[i] - sum) / matA[i][i];
	}
	p = &newX[counter];
	return p[0];
}

/* 'Norm' calculates the Euclidean norm of a vector */

double Norm(double vecX[n]) {
	int i;
	double *p;
	double norm = 0.0;
    for (i = 0; i < n; i++) {
    	norm = norm + vecX[i] * vecX[i];
    }
    norm = sqrt(norm);
	p = &norm;
	return *p;
}
