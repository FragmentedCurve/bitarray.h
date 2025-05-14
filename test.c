#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bitarray.h"

#define ARRAYLEN  333

int
main(int argc, char** argv)
{
	bitarray_t* a;

	assert(bitarray_sizeof(0) == 0);
	assert(bitarray_sizeof(1) == 1);
	assert(bitarray_sizeof(_BITARRAY_SIZE) == 1);
	assert(bitarray_sizeof(_BITARRAY_SIZE * 2 + 3) == 3);

	a = calloc(bitarray_sizeof(ARRAYLEN), 1);
	if (!a) {
		printf("malloc failed.\n");
		return -1;
	}

	assert(bitarray_get(a,   2) == 0);
	assert(bitarray_get(a,  16) == 0);
	assert(bitarray_get(a, ARRAYLEN - 1) == 0);

	bitarray_on(a,   0);
	bitarray_on(a,   2);
	bitarray_on(a,  16);
	bitarray_on(a, ARRAYLEN - 1);

	assert(bitarray_get(a,   0) == 1);
	assert(bitarray_get(a,   2) == 1);
	assert(bitarray_get(a,  16) == 1);
	assert(bitarray_get(a, ARRAYLEN - 1) == 1);

	bitarray_off(a,   2);
	bitarray_off(a, ARRAYLEN - 1);

	assert(bitarray_get(a,   2) == 0);
	assert(bitarray_get(a,  16) == 1);
	assert(bitarray_get(a, ARRAYLEN - 1) == 0);

	bitarray_set(a,   0, 1);
	bitarray_set(a,  16, 0);
	bitarray_set(a, ARRAYLEN - 1, 1);

	assert(bitarray_get(a,   0) == 1);
	assert(bitarray_get(a,  16) == 0);
	assert(bitarray_get(a, ARRAYLEN - 1) == 1);

	printf("passed\n");

	return 0;
}
