#include "sumlib.h"


double* allocate_vector(int size){
	double* vec = (double*) malloc(sizeof(double)*size);
	return vec;
}

void fill_vector(double* vector, int start, int size, double (*func_p)(int), int offset){
	int i, j;	
	#pragma omp paralell for schedule(static) private(j) 
	for(i = 0; i < size; i++){
		j = start + i*offset + 1;
		vector[i] = (*func_p)(j);
	}		
}

double sum_vector(double* vec, int size){
	int i;
	double sum = 0;
	#pragma omp parallel for schedule(static) reduction(+:sum)
	for(i = 0; i < size; i++){
		sum += vec[i];
	}
	return sum;
}

void free_vector(double* vec){
	free(vec);
}


