#include <stdio.h>
#include <stdlib.h>

double* calculateProduct(double matrix[3][3], double vector[3], int row, int col){
	/* Does no checking of dimensions. */
	double* product = (double*)malloc(sizeof(double)*3);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			product[i] += matrix[i][j] * vector[j];
		}
	}
	return product;
	
}

int main(int argc, char** argv){
	double matrix[3][3] = {{0.3, 0.4, 0.3},
			       {0.7, 0.1, 0.2},
 			       {0.5, 0.5, 0.0}};
	double vector[3] = {1.0, 1.0, 1.0};
	double* result = calculateProduct(matrix, vector, 3, 3);
	for(int i = 0; i < 3; i++){
		printf("%f\n", result[i]);
	}
	return 0; 
}
