#include "omp.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include "search.h"

using namespace std;

int main() {
	auto str = "rhrjke wl xs";
	auto substr = "xs";

	auto start_time = chrono::system_clock::now();
	int res = search(str, substr, false);
	auto end_time = chrono::system_clock::now();

	cout << "Single thread: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " ms" << endl;

	start_time = chrono::system_clock::now();
	res = search(str, substr, true);
	end_time = chrono::system_clock::now();

	cout << "Multy thread: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " ms" << endl;

	return 0;
}