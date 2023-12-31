#include <stdio.h>

#define TABWIDTH 4

main() {
	int i;
	char c;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			for (i = 0; i < TABWIDTH; ++i) {
				putchar(' ');
			}
		} else {
			putchar(c);
		}
	}

	return 0;
}
