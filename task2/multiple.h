#pragma once
int** multiple(int** a, int** b, int m, int n, int k, bool is_par) {
	int** res = new int* [m];
	for (int i = 0; i < m; i++)
		res[i] = new int[k];

#pragma omp parallel shared(a, b) if(is_par)
	{
		for (int i = 0; i < m; i++) {
#pragma omp for nowait  
			for (int j = 0; j < k; j++) {
				res[i][j] = 0;
				for (int s = 0; s < n; s++)
					res[i][j] += a[i][s] * b[s][j];
			}
		}
	}
	return res;
}