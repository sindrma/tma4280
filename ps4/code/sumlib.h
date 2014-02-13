
#ifndef SUMLIB_H
#define SUMLIB_H

#include <stdlib.h>

double* create_vector(int size, double (*func_p)(int));
double sum_vector(double* vec, int size);
void free_vector(double* vec);


#endif
