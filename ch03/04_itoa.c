#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[]);
void reverse(char s[]);

main() {
	const int limit = 30;
	char s[limit];
	
	const int n = INT_MIN;
	itoa(n, s);
	printf("%d = %s\n", n, s);	

	return 0;
}

void itoa(int n, char s[]) {
	int i, sign, digit;

	sign = n;
	i = 0;
	do {
		digit = (sign >= 0) ? n % 10 : -(n % 10);
		s[i++] = digit + '0';
	} while ((n /= 10) != 0);

	if (sign < 0) {
		s[i++] = '-';
	}	
	s[i] = '\0';
	reverse(s);
}

void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
