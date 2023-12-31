#include <stdio.h>
#include "08_bfree.c"

main() {
	double* arr, *arr2;
	int i;
	arr = (double *) malloc(1000 * sizeof(double));
	for (i = 0; i < 1000; i++) {
		arr[i] = i;
	}
	bfree(arr, 100 * sizeof(double));
	arr2 = (double *) malloc(100 * sizeof(double)); 
	for (i = 0; i < 100; i++) {
		arr2[i] = -i;
	}

	for (i = 0; i < 1000; i++) {
		printf("%g ", arr[i]);
	}

	putchar('\n');
}
