#include <stdio.h>

#define SIZE 10

main() {
	int n, getfloat(double *);
	double array[SIZE];

	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++) {
		printf("%g ", array[n]);
	}
	putchar('\n');
}


