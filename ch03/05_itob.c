#include <stdio.h>
#include <string.h>
#include <limits.h>

void itob(int n, char s[], int base);
void reverse(char s[]);

main() {
	const int limit = 30;
	char s[limit];
	
	itob(INT_MIN, s, 10);
	printf("%d base %d = %s\n", INT_MIN, 10, s); 
	itob(0, s, 10);
	printf("%d base %d = %s\n", 0, 10, s); 
	itob(255, s, 16);
	printf("%d base %d = %s\n", 255, 16, s); 
	itob(-12, s, 8);
	printf("%d base %d = %s\n", -12, 8, s); 
 
	return 0;
}

void itob(int n, char s[], int base) {
	int i, sign, digit;

	if (base < 2 || base > 36) return;

	sign = n;
	i = 0;
	do {
		digit = (sign >= 0) ? n % base : -(n % base);
		s[i++] = (digit > 10) ? digit + 'A' - 10 : digit + '0';
	} while ((n /= base) != 0);

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
