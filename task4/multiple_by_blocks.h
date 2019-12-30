#pragma once
#include "omp.h"

int** multiple_by_blocks(int threads, int** a, int** b, int d1, int d2, int d3) {
	int** res = new int* [d1];
	for (int i = 0; i < d1; i++)
		res[i] = new int[d3];
	for (int i = 0; i < d1; i++)
		for (int j = 0; j < d3; j++)
			res[i][j] = 0;
#pragma omp parallel num_threads(threads)
	{
		int dim = omp_get_num_threads();
		int a_h = d1 / dim;
		int a_w = d2 / dim;
		int b_w = d3 / dim;

#pragma omp for
		for (int a_block_count = 0; a_block_count < dim * dim; a_block_count++) {
			int i_block = a_block_count / dim;
			int j_block = a_block_count % dim;
			for (int t_block = 0; t_block < dim; t_block++) {
				for (int i = i_block * a_h; i < (i_block + 1) * a_h; i++)
					for (int j = j_block * a_w; j < (j_block + 1) * a_w; j++)
						for (int t = t_block * b_w; t < (t_block + 1) * b_w; t++)
							res[i][t] += a[i][j] * b[j][t];
			}
		}
	}
	return res;
}