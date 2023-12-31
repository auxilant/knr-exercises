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
	
	int maxcount;
	maxcount = 0;
	for (i = 0; i <= LIMIT; ++i) {
		if (wc[i] > maxcount) {
			maxcount = wc[i];
		}

		if (i < LIMIT) {
			printf("%2d ", i+1);
		} else {
			printf(" > ");
		}
	}
	putchar('\n');

	for (j = 0; j <= maxcount; ++j) {
		for (i = 0; i <= LIMIT; ++i) {
			if (wc[i] > j) {
				printf(" # ");
			} else
			if (wc[i] == j && j > 0) {
				printf("%2d ", wc[i]);
			} else {
				printf("   ");
			}
		}
		putchar('\n');
	}
}
