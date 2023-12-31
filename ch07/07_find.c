#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

typedef struct {
	unsigned int except : 1;
	unsigned int number : 1;
	unsigned int filename : 1;
} Options;

char line[MAXLINE];

int printmatches(FILE *fp, char *filename, char *pattern, Options options);

main(int argc, char *argv[]) {
	int c;
	char *prog = argv[0];
	char *pattern;
	int filenum = 0, i;
	char **filenames = NULL;
	FILE *fp;
	Options options = {0, 0, 0};

	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0]) {
			switch (c) {
			case 'x':
				options.except = 1;
				break;
			case 'n':
				options.number = 1;
				break;
			case 'f':
				options.filename = 1;
				break;
			default:
				fprintf(stderr, "%s: illegal option %c\n", prog, c);
				argc = 0;
				break;
			}
		}
	}

	if (argc < 1) {
		fprintf(stderr, "Usage: %s -x -n -f [filenames] pattern\n", prog);
		exit(1);
	}

	if (argc > 1) {
		filenum = argc - 1;
		filenames = argv;
		while (--argc > 0) {
			argv++;
		}
	}
	pattern = *argv;

	if (filenum > 0) {
		for (i = 0; i < filenum; i++) {
			if ((fp = fopen(filenames[i], "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s\n", prog, *filenames);
				exit(2);
			}
			printmatches(fp, filenames[i], pattern, options);
		}
	} else {
		printmatches(stdin, NULL, pattern, options);
	}

	return 0;
}

int printmatches(FILE *fp, char *filename, char *pattern, Options options) {
	long linenum = 0;
	int found = 0; 
	while (fgets(line, MAXLINE, fp)) {
		linenum++;
		if ((strstr(line, pattern) != NULL) != options.except) {
			if (options.filename) {
				printf("%s: ", filename ? filename : "stdin");
			}
			if (options.number) {
				printf("%ld: ", linenum);
			}
			printf("%s", line);
			found++;
		}
	}
	return found;
}
