#include <stdio.h>
#include "07_malloc.c"

main() {
	int* arr;
	arr = (int *) malloc(10 * sizeof(int));

	int i;
	for (i = 0; i < 10; i++) {
		arr[i] = i;
		printf("%d ", arr[i]);
	}
	putchar('\n');
}
