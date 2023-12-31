#include <stdio.h>
#define THRESHOLD 80

#define COMPLETE 1
#define INCOMPLETE 0

int getline(char line[], int maxline);

main() {
	int linestate, len;
	char line[THRESHOLD+1]; /* +1 for '/0' */

	linestate = COMPLETE;
	while ((len = getline(line, THRESHOLD+1)) > 0 ) {
		if (len == THRESHOLD && line[THRESHOLD-1] != '\n') {
			linestate = INCOMPLETE;
			printf("%s", line);
		} else {
			if (linestate == INCOMPLETE) {
				printf("%s", line);
			}
			linestate = COMPLETE;
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
