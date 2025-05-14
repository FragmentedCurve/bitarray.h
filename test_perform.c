#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bitarray.h"

#define ARRAY_SIZE 0xfffffff

int
main(int argc, char** argv)
{
	size_t i;
	clock_t start, end;
	bitarray_t* arr;

	arr = calloc(bitarray_sizeof(ARRAY_SIZE), 1);
	if (!arr) {
		printf("malloc failed.\n");
		return -1;
	}

	start = clock();
	for (i = 0; i < ARRAY_SIZE; ++i) {
		bitarray_on(arr, i);
	}
	end = clock();

	printf("Write Time: %ld\n", end - start);

	start = clock();
	for (i = 0; i < ARRAY_SIZE; ++i) {
		bitarray_get(arr, i);
	}
	end = clock();

	printf("Read Time: %ld\n", end - start);

	return 0;
}
