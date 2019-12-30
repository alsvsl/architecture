#pragma once
int* multiple_by_rows(int** a, int* b, int m, int n, int threads) {
	int* result = new int[m];
	for (int i = 0; i < m; i++)
		result[i] = 0;
#pragma omp parallel shared(a, b, result) num_threads(threads)
	{
#pragma omp for nowait
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++)
				result[i] += a[i][j] * b[j];
		}
	}
	return result;
}