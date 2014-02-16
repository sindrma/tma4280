#include "sumlib.h"
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>

#ifdef HAVE_OPENMP
#include <omp.h>
#endif

#ifdef HAVE_MPI
#include <mpi.h>
#endif

#define K_MAX  14
#define K_MIN  3
#define PI     4*atan(1)

/*  The v-funtion  */
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
	// Initialize some needed values...
	int n, t1, t2, n_max, k, num_elem, i;
	double s, temp_sum, total_sum, start, end;
	double* list;
	char test[20]; 

	int rank, size, tag;	
	
	#ifdef HAVE_MPI
	// MPI variables
	MPI_Status status;	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	tag = 100;
	#else
	size = 1;
	rank = 0;
	#endif
	
	// Set start-time
	start = WallTime();
	
	// Initialize and set the actual s value	
	s = (PI*PI)/6;
		
	// Calculate the maximal value of n
	n_max = pow(2, K_MAX);	

	// Find the number of lists needed
	#ifdef HAVE_MPI
	num_elem = n_max/size;   
	#else
	num_elem = n_max;
	#endif
	
	
	// Allocate vector for all nodes
	list = allocate_vector(num_elem);	
	
	#ifdef HAVE_MPI
	if(rank == 0){
		// Send of work...
		for(i=1; i < size; i++){
			fill_vector(list, i, num_elem, v, size);
			MPI_Send(list, num_elem, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);
		}
		// Make vector for node 0	
		fill_vector(list, 0, num_elem, v, size);

	} else{
		// Receive work
		MPI_Recv(list, num_elem, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
		printf("node %d received something...", rank);
	}
	#else
	// If serial/OpenMP, fill the whole list
	fill_vector(list, 0, num_elem, v, 1);
	#endif
	

	for(k = K_MIN; k <= K_MAX; k++){
		// Find number of elements to sum up
		#ifdef HAVE_MPI
		n = pow(2,k) / num_elem;
		#else
		n = pow(2,k);
		#endif
		// Sum the elements
		temp_sum = sum_vector(list, n);
		// Report answer
		#ifdef HAVE_MPI
		MPI_Reduce(&temp_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		#else	
		total_sum = temp_sum;
		#endif
		if(rank == 0)  printf("n=%d, s_n=%e, s-s_n=%e\n", n, total_sum, s-total_sum);	
	}

	// Report end-time
	printf("elapsed time: %lf\n", WallTime()-start);
	
	// Free memory
	free_vector(list);
	
	#ifdef HAVE_MPI
	// Finalize MPI
	MPI_Finalize();
	#endif
	return 0;
}


