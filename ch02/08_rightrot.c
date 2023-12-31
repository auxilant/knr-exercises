#include <stdio.h>

#define SIZEOF_UINT 32

unsigned rightrot(unsigned x, int n);

main() {
	/* tests */
	printf("rightrot(124, 2) = %u\n", rightrot(124, 2)); /* 41 */
	printf("rightrot(8,4) = %u\n", rightrot(8,4)); /* 2147483648 */
	printf("rightrot(11, 3) = %u\n", rightrot(11, 3)); /* 1610612737 */
	printf("rightrot(2452, 0) = %u\n", rightrot(2452, 0)); /* 2452 */

	return 0;
}

unsigned rightrot(unsigned x, int n) {
	unsigned x1;

	x1 = x << (SIZEOF_UINT - n);
	x = x >> n;

	return (x | x1);
}
