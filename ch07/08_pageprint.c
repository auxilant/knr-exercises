#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PAGEHEIGHT 25
#define PAGEWIDTH 80

char line[PAGEWIDTH+1];

int printpage(FILE *fp, char *filename, int page);
void delimiter(char c, int width);
void detab(char *line);

main(int argc, char *argv[]) {
	char *prog = argv[0];
	FILE *fp;
	int i, page;

	if (argc == 1) {
		fprintf(stderr, "%s: no files to print\n", prog);
		exit(1);
	}

	for (i = 1; i < argc; i++) {
		if ((fp = fopen(argv[i], "r")) == NULL ) {
			fprintf(stderr, "%s: can't open %s\n", prog, argv[i]);
			exit(2);
		}
		page = 1;
		if (i == 1) {
			delimiter('-', PAGEWIDTH);
		}
		while (printpage(fp, argv[i], page++))
			;
	}

	return 0;
}

int printpage(FILE *fp, char *filename, int page) {
	int i, readable = 1;
	printf("%s, page %d\n", filename, page);
	for (i = 1; i < PAGEHEIGHT; i++) {
		if (!readable) {
			putchar('\n');
			continue;
		}
		if (fgets(line, PAGEWIDTH+1, fp) == NULL) {
			readable = 0;
			putchar('\n');
			continue;
		}
		detab(line);
		printf("%s", line);
		if (line[strlen(line)-1] != '\n') {
			putchar('\n');
		}
	}
	delimiter('-', PAGEWIDTH);
	return readable;
}

void delimiter(char c, int width) {
	int i;
	for (i = 0; i < width; i++) {
		putchar(c);
	}
	putchar('\n');
}

void detab(char *line) {
	while (*line != '\0') {
		if (*line == '\t') {
			*line = ' ';
		}
		line++;
	}
}
