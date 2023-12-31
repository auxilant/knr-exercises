#include <stdio.h>

#define LINE_LIMIT 20
#define TAB_WIDTH 8
#define COMPLETE 1
#define INCOMPLETE 0

int getline(char line[], int size);

int linestate;

main() {
	int len;
	extern int linestate;
	char line[LINE_LIMIT];

	while ((len = getline(line, LINE_LIMIT)) > 0) {
		if (linestate == INCOMPLETE) {
			while (len > 0 && (line[len-1] == ' ' || line[len-1] == '\t')) {
				line[len-1]='\0';
				--len;
			}
			printf("%s\n", line);
		} else {
			printf("%s", line);
		}
	}

	return 0;
}

int getline(char line[], int size) {
	int i;
	extern int linestate;
	char c;
	linestate = INCOMPLETE;

	for (i = 0; (i < size-1) && ((c = getchar()) != EOF) && (c != '\n'); ++i) {
		if (c == '\t') {
			size = size + 1 - TAB_WIDTH;
		}
		line[i] = c;
	}
	if (c == '\n') {
		line[i] = c;
		++i;
		linestate = COMPLETE;
	}
	line[i] = '\0';
	return i;
}
