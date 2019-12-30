#pragma once
#include "omp.h"

int* multiple_by_tapes(int threads, int* a, int* b, int dim) {
	int i, j, k, sum;
	int* res = new int[dim * dim];

#pragma omp parallel for private(j,k,sum) num_threads(threads)
	for (i = 0; i < dim; i++) {
		for (k = 0; k < dim; k++) {
			sum = 0;
			for (j = 0; j < dim; j++)
				sum += a[i * dim + j] * b[j * dim + k];
			res[i * dim + k] = sum;
		}
	}
	return res;
}