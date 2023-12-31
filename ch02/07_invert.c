#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

main() {
	/* tests */
	printf("invert(24, 2, 3) = %u\n", invert(24, 2, 3)); /* 31 */	
	printf("invert(0, 6, 5) = %u\n", invert(0, 6, 5)); /* 124 */
	printf("invert(120, 3, 0) = %u\n", invert(120, 3, 0)); /* 120 */

	return 0;
}

unsigned invert(unsigned x, int p, int n) {
	unsigned mask;
	mask = ~(~0 << n) << (p+1-n);

	return x ^ mask;
}
