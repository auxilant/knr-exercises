#include <stdio.h>

#define SIZE 10

main() {
	int n, array[SIZE], getint(int *);

	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++) {
		printf("%d ", array[n]);
	}
	putchar('\n');
}


