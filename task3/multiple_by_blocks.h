#pragma once
#include "omp.h"
int* multiple_by_blocks(int** a, int* b, int m, int n, int threads) {
	int* result = new int[m];
	for (int i = 0; i < m; i++)
		result[i] = 0;
#pragma omp parallel shared(a, b, result) num_threads(threads)
	{
		int s = omp_get_num_threads();
		int q = s;
		int block_h = m / s;
		int block_w = n / q;

#pragma omp for
		for (int blocks = 0; blocks < s * q; blocks++) {
			int i = blocks / q;
			int j = blocks % q;
			for (int k = i * block_h; k < (i + 1) * block_h; k++)
				for (int l = j * block_w; l < (j + 1) * block_w; l++)
					result[k] += a[k][l] * b[l];
		}
	}
	return result;
}

