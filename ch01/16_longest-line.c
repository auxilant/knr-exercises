#include <stdio.h>
#define MAXLINE 50

#define COMPLETE 1
#define INCOMPLETE 0

int getline(char line[], int maxline);
void copy(char to[], char from[]);

main() {
	int len, longlen, max;
	int linestate; /* complete or incomplete */
	char linestart[MAXLINE], line[MAXLINE], longest[MAXLINE];

	max = 0;
	longlen = 0;
	linestate = COMPLETE;
	while ((len = getline(line, MAXLINE)) > 0) {
		if (len < MAXLINE-1 || line[MAXLINE-2] == '\n') {
			if (linestate == COMPLETE) {
				copy(linestart, line);
			}
			linestate = COMPLETE;
		} else {
			if (linestate == COMPLETE) {
				linestate = INCOMPLETE;
				copy(linestart, line);
			}
		}
		longlen = longlen + len;

		if (linestate == COMPLETE) {
			if (longlen > max) {
				max = longlen;
				copy(longest, linestart);
			}
			longlen = 0;
		}
	}
	if (max > 0)
		printf("%d\n%s\n", max, longest);
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

void copy(char to[], char from[]) {
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0') {
		++i;
	}
}
