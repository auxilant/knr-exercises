#include "malloc.c"

void *calloc(unsigned n, unsigned size) {
	char *ptr;
	ptr = (char *) malloc(n * size);

	int i;
	for (i = 0; i < n * size; ++i) {
		*(ptr + i) = (char *) 0;
	}
	return (void *)ptr;
}
