#include <stdio.h>
#include <ctype.h>

main(int argc, char *argv[]) {
	while (*argv[0] != '\0') {
		argv[0]++;
	}
	argv[0] -= 5;

	int (*func)(int);

	if (strcmp(argv[0], "lower") == 0) {
		func = tolower;
	} else
	if (strcmp(argv[0], "upper") == 0) {
		func = toupper;
	} else {
		printf("bad program name\n");
	}

	int c;
	while ((c = getchar()) != EOF) {
		putchar(func(c));
	}
}
