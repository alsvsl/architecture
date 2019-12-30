#pragma once
#include <limits.h>
using namespace std;

int find_min(int* a, int m) {
	int min = INT_MAX;
	for (int i = 0; i < m; i++) {
		if (a[i] < min)
			min = a[i];
	}
	return min;
}

int find_max(int** a, int n, int m, bool is_parallel) {
	int* min_a = new int[n];

#pragma omp parallel if(is_parallel)
	{
#pragma omp for
		for (int i = 0; i < n; i++)
			min_a[i] = find_min(a[i], m);
	}

	int max = INT_MIN;
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		if (min_a[i] > max)
			max = min_a[i];
	}
	return max;
}