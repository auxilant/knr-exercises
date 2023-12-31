#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_COLWIDTH 4

void myqsort(int *arr, int left, int right);

main(int argc, char *argv[]) {
	int use_defaults;
	if (argc == 1) {
		argc = 2;
		use_defaults = 1;
	} else {
		use_defaults = 0;
	}

	int tabstops[argc-1];
	int *tsptr = tabstops;
	if (use_defaults) {
		tabstops[0] = DEFAULT_COLWIDTH + 1;
	} else {
		int argc0 = argc;
		while (--argc0 > 0) {
			if ((*tsptr++ = atoi(*++argv)) <= 0) {
				printf("error: use positive integer arguments\n");
				return -1;
			} 
		}
		myqsort(tabstops, 0, argc-2);
	}

	char c;
	int column = 0;
	int i;
	tsptr = tabstops;
	int nextts = *tsptr;

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			column = 0;
			tsptr = tabstops;
			nextts = *tsptr;
			putchar(c);
			continue;
		} else {
			column++;
		}

		if (column == nextts) {
			if (tsptr - tabstops < argc - 2) {
				tsptr++;
				nextts = *tsptr;
			} else {
				nextts += DEFAULT_COLWIDTH;
			}
		}
		if (c == '\t') {
			for (i = 0; i < nextts - column; i++) {
				putchar(' ');
			}
			column = nextts - 1;
		} else {
			putchar(c);
		}
	}

	return 0;
}
