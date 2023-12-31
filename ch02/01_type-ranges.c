#include <stdio.h>
#include <limits.h>
#include <float.h>

main() {
	printf("char: %d to %d\n", CHAR_MIN, CHAR_MAX);
	printf("signed char: %d to %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("unsigned char: %d to %d\n", 0, UCHAR_MAX);

	printf("short: %d to %d\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short: %u to %u\n", 0, USHRT_MAX);

	printf("int: %d to %d\n", INT_MIN, INT_MAX);
	printf("unsigned int: %u to %u\n", 0, UINT_MAX);
	
	printf("long: %li to %li\n", LONG_MIN, LONG_MAX);
	printf("unsigned long: %lu to %lu\n", 0, ULONG_MAX);

	printf("float (positive): %.10e to %.10e\n", FLT_MIN, FLT_MAX);
	printf("double (positive): %.10e to %.10e\n", DBL_MIN, DBL_MAX);
	printf("long double (positive): %.10Le to %.10Le\n", LDBL_MIN, LDBL_MAX);
	
	return 0;
}

