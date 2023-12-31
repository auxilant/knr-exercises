#include <stdio.h>

main() {
	int c, pc;

	while ((c = getchar()) != EOF) {
		if (c != ' ') {
			putchar(c);
			pc = c;
		}
		if (c == ' ') {
			if (pc != ' ') {
				putchar(c);
				pc = c;
			}
		}
	}
}
