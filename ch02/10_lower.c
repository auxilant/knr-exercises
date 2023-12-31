#include <stdio.h>

char lower(char c);

main() {
	printf("lower('A') = %c\n", lower('A')); /* a */
	printf("lower('G') = %c\n", lower('G')); /* g */
	printf("lower('g') = %c\n", lower('g')); /* g */
	printf("lower('5') = %c\n", lower('5')); /* 5 */

	return 0;
}

char lower(char c) {
	return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
}
