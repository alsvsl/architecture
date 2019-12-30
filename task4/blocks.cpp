#include "omp.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include "multiple_by_blocks.h"

using namespace std;

int main() {
	int max_threads = 16;
	int max_dim = 1024;

	ofstream output_blocks;
	output_blocks.open("output_blocks.txt");

	for (int dim = 64; dim <= max_dim; dim *= 2)
		output_blocks << dim << " ";
	output_blocks << endl;

	for (int threads = 1; threads <= max_threads; threads *= 2) {
		output_blocks << threads << " ";
		for (int dim = 64; dim <= max_dim; dim *= 2) {
			int d1 = dim, d2 = dim, d3 = dim;

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
			int** res = multiple_by_blocks(threads, a, b, d1, d2, d3);
			auto end_time = chrono::system_clock::now();

			output_blocks << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " ";

			for (int i = 0; i < d1; i++)
				delete[] a[i];
			for (int i = 0; i < d2; i++)
				delete[] b[i];
			delete[] a;
			delete[] b;
			delete[] res;
		}
		output_blocks << endl;
	}

	output_blocks.close();

	return 0;
}