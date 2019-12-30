#include "omp.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include "multiple_by_tapes.h"

using namespace std;

int main() {
	int max_n_threads = 16;
	int max_dim = 1024;

	ofstream output_tapes;
	output_tapes.open("output_tapes.txt");

	for (int dim = 64; dim <= max_dim; dim *= 2)
		output_tapes << dim << " ";
	output_tapes << endl;

	for (int threads = 1; threads <= max_n_threads; threads *= 2) {
		output_tapes << threads << " ";
		for (int dim = 64; dim <= max_dim; dim *= 2) {
			int* a = new int[dim * dim];

			int* b = new int[dim * dim];

			for (int i = 0; i < dim; i++) {
				for (int j = 0; j < dim; j++) {
					a[i * dim + j] = rand() % 100;
					b[i * dim + j] = rand() % 100;
				}
			}

			auto start_time = chrono::system_clock::now();
			int* res = multiple_by_tapes(threads, a, b, dim);
			auto end_time = chrono::system_clock::now();

			output_tapes << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " ";

			delete[] a;
			delete[] b;
			delete[] res;
		}
		output_tapes << endl;
	}

	output_tapes.close();

	return 0;
}