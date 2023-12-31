#include <stdio.h>

#define LIMIT 20

main() {
	int c, currentwl, i, j;
	int wc[LIMIT+1]; /* wc[LIMIT] for longer words, wc[n-1] for length n */

	currentwl = 0;
	for (i = 0; i <= LIMIT; ++i) {
		wc[i] = 0;
	}

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (currentwl > 0) {
				if (currentwl <= LIMIT) {
					++wc[currentwl-1];
				} else {
					++wc[LIMIT];
				}
				currentwl = 0;
			}
		} else {
			++currentwl;
		}
	}

	for (i = 0; i <= LIMIT; ++i) {
		if (i < LIMIT) {
			printf("%2d ", i+1);
		} else {
			printf(" > ");
		}

		for (j = 0; j < wc[i]; ++j) {
			putchar('#');
		}
		if (wc[i] > 0) {
			printf(" %d", wc[i]);
		}
		putchar('\n');
	}
}
