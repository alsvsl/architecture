#include "omp.h"
#include <iostream>
#include "multiple.h"
#include <chrono>
#include <cstdlib>

using namespace std;

int main() {
	int d1 = 1000;
	int d2 = 1000;
	int d3 = 1000;

	int** a = new int* [d1];
	for (int i = 0; i < d1; i++) {
		a[i] = new int[d2];
		for (int j = 0; j < d2; j++)
			a[i][j] = rand() % 100;
	}

	int** b = new int* [d2];
	for (int i = 0; i < d2; i++) {
		b[i] = new int[d3];
		for (int j = 0; j < d3; j++)
			b[i][j] = rand() % 100;
	}

	auto start_time = chrono::system_clock::now(); 
	int** res1 = multiple(a, b, d1, d2, d3, false);
	auto end_time = chrono::system_clock::now();

	cout << "Single thread: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " ms" << endl;

	start_time = chrono::system_clock::now();
	int** res2 = multiple(a, b, d1, d2, d3, true);
	end_time = chrono::system_clock::now();

	cout << "Multy thread: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " ms" << endl;

	return 0;

}