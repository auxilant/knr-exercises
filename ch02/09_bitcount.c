#include <stdio.h>

int bitcount(unsigned x);

main() {
	printf("bitcount(0) = %d\n", bitcount(0)); /* 0 */	
	printf("bitcount(15) = %d\n", bitcount(15)); /* 4 */
	printf("bitcount(79) = %d\n", bitcount(79)); /* 5 */
	printf("bitcount(10925) = %d\n", bitcount(10925)); /* 8 */

	return 0;
}

int bitcount(unsigned x) {
	int bits = 0;
	
	while (x != 0) {
		x &= (x-1);
		++bits;
	}

	return bits;
}
