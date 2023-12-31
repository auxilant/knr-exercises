#include <stdio.h>

#define CHARACTERS 128
#define FIRST_PRINTABLE 32

main() {
	int c, i, j;
	int cfreq[CHARACTERS];

	for (i = 0; i < CHARACTERS; ++i) {
		cfreq[i] = 0;
	}

	while ((c = getchar()) != EOF) {
		if (c >= 0 && c < CHARACTERS) {
			++cfreq[c];
		}
	}

	for (i = 0; i <= CHARACTERS; ++i) {
		if (cfreq[i] > 0) {
			if (i == '\t') {
				printf("'\\t' ");
			} else
			if (i == '\n') {
				printf("'\\n' ");
			} else
			if (i >= FIRST_PRINTABLE) {
				printf(" '%c' ", i);
			}

			for (j = 0; j < cfreq[i]; ++j) {
				putchar('#');
			}
			printf(" %d\n", cfreq[i]);
		}
	}
}
