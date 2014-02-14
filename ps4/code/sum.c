#include "sumlib.h"
#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#include <omp.h>

#define K_MAX  14
#define PI     4*atan(1)

double v (int i) { return 1.0/ (i*i);}

/* Taken from the lecturers common.c library */
double WallTime ()
{
	#ifdef HAVE_MPI
 	 return MPI_Wtime();
	#elif defined(HAVE_OPENMP)
 	 return omp_get_wtime();
	#else
 	 struct timeval tmpTime;
 	 gettimeofday(&tmpTime,NULL);
 	 return tmpTime.tv_sec + tmpTime.tv_usec/1.0e6;
	#endif
}

int main(int argc, char** argv){
	int n, t1, t2, n_max;
	double s, temp_sum, start, end;
	double* list;
	
	s = (PI*PI)/6;
	printf("s=%lf\n", s);

	n_max = pow(2, K_MAX);	
	list = create_vector(n_max, v);
	
	start = WallTime();
			
	for(int k = 0; k <= K_MAX; k++){
		n = pow(2, k);
		temp_sum = sum_vector(list, n);        
		printf("n=%d, s_n=%lf, s-s_n=%lf\n", n, temp_sum, s-temp_sum);	
	}
	printf("elapsed time: %lf\n", WallTime()-start);
	
	free_vector(list);
	return 0;
}
