#include "sumlib.h"
#include <stdio.h>
#include <math.h>

#define K_MAX  14
#define PI     4*atan(1)

double v (int i) { return 1.0/ (i*i);}

int main(int argc, char** argv){
	int n, t1, t2, n_max;
	double s, temp_sum;
	double* list;
	
	s = (PI*PI)/6;
	printf("s=%f\n", s);

	n_max = pow(2, K_MAX);	
	list = create_vector(n_max, v);
	
	for(int k = 0; k <= K_MAX; k++){
		n = pow(2, k);
		temp_sum = sum_vector(list, n);        
		printf("n=%d, s_n=%f, s-s_n=%f\n", n, temp_sum, s-temp_sum);	
	}

	free_vector(list);
	return 0;
}
