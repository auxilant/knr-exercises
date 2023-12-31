#include <stdio.h>

#define TABWIDTH 4

main() {
	char c;
	int consec_spaces;
	consec_spaces = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			++consec_spaces;
			if (consec_spaces == TABWIDTH) {
				putchar('\t');
				consec_spaces = 0;
			}
		} else {
			while (consec_spaces > 0) {
				putchar(' ');
				--consec_spaces;
			}
			putchar(c);
		}
	}

	return 0;
}
