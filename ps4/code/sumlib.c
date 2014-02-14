#include "sumlib.h"


double* create_vector(int size, double (*func_p)(int)){
	/* Creates an array with elements specified by the passed function and values*/
	double* vec = (double*) malloc(sizeof(double)*size);
	#pragma omp paralell for schedule(static) private(i) 
	for(int i = 0; i < size; i++){
		vec[i] = (*func_p)(i+1);
	}
	return vec;		
}

double sum_vector(double* vec, int size){
	double sum = 0;
	#pragma omp parallel for schedule(static) reduction(+:sum)
	for(int i = 0; i < size; i++){
		sum += vec[i];
	}
	return sum;
}

void free_vector(double* vec){
	free(vec);
}


