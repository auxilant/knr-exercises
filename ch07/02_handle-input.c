#include <stdio.h>

#define TABSTOP 8
#define MAXLINE 80

main() {
	int c, column;

	column = 1;
	while ((c = getchar()) != EOF) {
		if (c >= 32) {
			putchar(c);
			column++;
		} else
		if (c == '\n') {
			putchar(c);
			column = 1;
		} else
		if (c == '\t') {
			do {
				column++;
			} while (column % TABSTOP != 1);
			putchar(c);
		} else {
			if (column + 6 > MAXLINE) {
				putchar('\n');
				column = 1;
			}
			printf("'0x%x'", c);
			column += 6;
		}

		if (column > MAXLINE) {
			column = 1;
			putchar('\n');
		}
	}

	return 0;
}
