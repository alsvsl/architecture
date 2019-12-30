#pragma once
#include<string>
#include "omp.h"

int search(const char* str, const char* substr, bool is_parallel) {
	int res = -1;
#pragma omp parallel shared(str, substr) if(is_parallel)
	{
#pragma omp for
		for (int i = 0; i <= strlen(str) - strlen(substr); i++) {
			int count = 0;
			for (int j = 0; j < strlen(substr); j++) {
				if (str[i + j] != substr[j])
					break;
				count++;
			}
			if (count == strlen(substr))
				res = i;
		}
	}
	return res;
}