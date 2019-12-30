#include "omp.h"
#include "maxMinSearch.h"
#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;

int main() {
	int n = 10000; 
	int m = 10000; 
	int** a = new int* [n];

	for (int i = 0; i < n; i++) {
		a[i] = new int[m];
		for (int j = 0; j < m; j++)
			a[i][j] = rand() % 100000;
	}

	auto start = chrono::system_clock::now();
	int ans = find_max(a, n, m, false);
	auto end = chrono::system_clock::now();

	cout << "Single thread: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " ms" << endl;

	start = chrono::system_clock::now();
	ans = find_max(a, n, m, true);
	end = chrono::system_clock::now();

	cout << "Multy thread: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " ms" << endl;

	return 0;
}

