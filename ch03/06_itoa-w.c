#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int width);
void reverse(char s[]);

main() {
	const int limit = 30;
	char s[limit];
	
	itoa(-3621, s, 8);
	printf("%d = '%s'\n", -3621, s);	
	itoa(42345, s, 3);
	printf("%d = '%s'\n", 42345, s);

	return 0;
}

void itoa(int n, char s[], int width) {
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

	while (i < width) {
		s[i++] = ' ';
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
