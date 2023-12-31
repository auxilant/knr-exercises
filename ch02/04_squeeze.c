#include <stdio.h>

void squeeze(char string[], char chars_to_delete[]);
int getline(char string[], int limit);

main() {
	const short limit = 1000;
	char s1[limit], s2[limit];

	getline(s1, limit);
	getline(s2, limit);
	
	squeeze(s1,s2);
	printf("%s\n", s1);

	return 0;
}

void squeeze(char s1[], char s2[]) {
	int i, i_new, j;

	for (i = i_new = 0; s1[i] != '\0'; ++i) {
		for (j = 0; s2[j] != '\0' && s2[j] != s1[i]; ++j) ;
		if (s2[j] == '\0') {
			s1[i_new++] = s1[i];
		}
	}
	s1[i_new++] = '\0';
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
