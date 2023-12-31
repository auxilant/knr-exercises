#include <stdio.h>
#include <limits.h>

void itoa(int n, char s[]);

main() {
	const int limit = 30;
	char s[limit];
	
	const int n = INT_MIN;
	itoa(n, s);
	printf("%d = %s\n", n, s);	

	return 0;
}
