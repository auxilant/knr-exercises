#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, int y);

main() { 
	/* tests */
	printf("setbits(24, 1, 2, 5) = %u\n", setbits(24, 1, 2, 5)); /* 27 */
	printf("setbits(37, 3, 4, 6) = %u\n", setbits(37, 3, 4, 6)); /* 41 */
	printf("setbits(71, 4, 3, 5) = %u\n", setbits(71, 4, 3, 5)); /* 71 */
	printf("setbits(71, 7, 2, 3) = %u\n", setbits(71, 7, 2, 3)); /* 199 */
	printf("setbits(75, 3, 0, 5) = %u\n", setbits(75, 3, 0, 5));  /* 75 */

	return 0;
}

unsigned setbits(unsigned x, int p, int n, int y) {
	unsigned x1, mask;

	if (y-1 > p) { 
		x1 = x >> (y-1-p);
	} else {
		x1 = x << (p-y+1);
	}

	mask = ~(~0 << n) << (p+1-n); 
	x1 = x1 & mask;
	x = x & ~mask;

	return x | x1;
}

