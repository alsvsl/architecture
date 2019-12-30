#include "omp.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include "multiple_by_rows.h"
#include "multiple_by_cols.h"
#include "multiple_by_blocks.h"

using namespace std;

int main() {
	int max_threads = 16;
	int max_dim = 16384;

	ofstream output_rows;
	output_rows.open("output_rows.txt");

	ofstream output_cols;
	output_cols.open("output_cols.txt");

	ofstream output_blocks;
	output_blocks.open("output_blocks.txt");

	for (int dim = 64; dim <= max_dim; dim *= 2) {
		output_rows << dim << " ";
		output_cols << dim << " ";
		output_blocks << dim << " ";
	}
	output_rows << endl;
	output_cols << endl;
	output_blocks << endl;

	for (int threads = 1; threads <= max_threads; threads *= 2) {
		output_rows << threads << " ";
		output_cols << threads << " ";
		output_blocks << threads << " ";
		for (int dim = 4; dim <= max_dim; dim *= 2) {
			int d1 = dim;
			int d2 = dim;
			int** a = new int* [d1];
			for (int i = 0; i < d1; i++) {
				a[i] = new int[d2];
				for (int j = 0; j < d2; j++)
					a[i][j] = rand() % 100;
			}
			int* b = new int[d2];
			for (int i = 0; i < d2; i++)
				b[i] = rand() % 100;

			auto start_time = chrono::system_clock::now();
			int* res = multiple_by_rows(a, b, d1, d2, threads);
			auto end_time = chrono::system_clock::now();

			output_rows << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " ";

			start_time = chrono::system_clock::now();
			res = multiple_by_cols(a, b, d1, d2, threads);
			end_time = chrono::system_clock::now();

			output_cols << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " ";

			start_time = chrono::system_clock::now();
			res = multiple_by_blocks(a, b, d1, d2, threads);
			end_time = chrono::system_clock::now();

			output_blocks << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " ";

			for (int i = 0; i < d1; i++)
				delete[] a[i];
			delete[] a;
			delete[] b;
			delete[] res; 
		}
		cout << endl;
		output_rows << endl;
		output_cols << endl;
		output_blocks << endl;
	}

	output_rows.close();
	output_cols.close();
	output_blocks.close();

	return 0;
}
