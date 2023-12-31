#include <stdio.h>
#include <ctype.h>

#define NOT_DIGIT -1

unsigned long int htoi(char s[]);
int getline(char string[], int limit);

main() {
	const line_limit = 100;
	char hex[line_limit];

	getline(hex, line_limit);
	printf("%lu\n", htoi(hex)); 

	return 0;
}

unsigned long int htoi(char hex[]) {
	unsigned long int result = 0;
	short digit = 0;

	int i = 0;
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
		i = 2;
	}

	while (digit >= 0) { 
		if (isdigit(hex[i])) {
			digit = hex[i] - '0';
		} else
		if ((hex[i] >= 'a' && hex[i] <= 'f')) {
			digit = hex[i] - 'a' + 10;
		} else
		if ((hex[i] >= 'A' && hex[i] <= 'F')) {
			digit = hex[i] - 'A' + 10;
		} else {
			digit = NOT_DIGIT;
		

		if (digit >= 0) {
			result = result * 16 + digit;
			++i;
		}
	}

	return result;
}

int getline(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
