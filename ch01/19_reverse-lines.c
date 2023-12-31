#include <stdio.h>
#define LIMIT 1000

int getline(char line[], int maxline);
void reverse(char string[]);

main() {
	int len;
	char line[LIMIT];

	while ((len = getline(line, LIMIT)) > 0) {
		reverse(line);
		printf("%s", line); 
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

void reverse(char s[]) {
	int len; /* without '\n' */

	for (len = 0; s[len] != '\n' && s[len] != '\0'; ++len) ;

	int i;
	char tmp;
	for (i = 0; i < len/2; ++i) {
		tmp = s[i];
		s[i] = s[len-1-i];
		s[len-1-i] = tmp;
	}
}
