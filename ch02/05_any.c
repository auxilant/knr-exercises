#include <stdio.h>

int any(char string[], char chars_to_locate[]);
int getline(char string[], int limit);

main() {
	const short limit = 1000;
	char s1[limit], s2[limit];

	getline(s1, limit);
	getline(s2, limit);

	printf("%d\n", any(s1,s2));
	return 0;
}

int any(char s1[], char s2[]) {
	int i, j;

	for (i = 0; s1[i] != '\0'; ++i) {
		for (j = 0; s2[j] != '\0'; ++j) {
			if (s1[i] == s2[j]) {
				return i;
			}
		}
	}

	return -1;
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
