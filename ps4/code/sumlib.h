
#ifndef SUMLIB_H
#define SUMLIB_H

#include <stdlib.h>

/*  Allocates a vector of size containing doubles  */
double* allocate_vector(int size);

/*  Fills the vector with results from a function, with start 
    as the initial value and offset as jump   */
void fill_vector(double* vector, int start, int size, double (*func_p)(int), int offset);

/*   Sums up the elements of the vector   */
double sum_vector(double* vec, int size);

/*   Cleans up memeory of the vector   */
void free_vector(double* vec);


#endif
