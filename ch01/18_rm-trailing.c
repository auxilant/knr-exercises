#include <stdio.h>
#define LIMIT 1000

int getline(char line[], int maxline);

main() {
	int len;
	char line[LIMIT];

	while ((len = getline(line, LIMIT)) > 0) {
		if (len == LIMIT && line[LIMIT-2] != '\n') {
			printf("%s", line); /* too long */
		}
		while (len > 1 && (line[len-2] == ' ' || line[len-2] == '\t')) {
			line[len-1] = '\0';
			line[len-2] = '\n';
			--len;
		}
		if (len > 1) {
			printf("%s", line); /* len == 1 is blank line ("\n"); */
		}
	}

	return 0;
}

int getline(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
