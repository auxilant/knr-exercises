#include <stdio.h>
#include "06_calloc.c"

main() {
	int* arr;
	arr = (int *) calloc(10, sizeof(int));

	int i;
	for (i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
}
