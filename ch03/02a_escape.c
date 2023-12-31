#include <stdio.h>

void escape(char output[], char input[]);

main() {
	const int limit = 1000;
	char s_in[limit+1], s_out[limit+1];
	char c;
	int i = 0;

	while ( ((c = getchar()) != EOF) && (i < limit) ) {
		s_in[i++] = c;
	}
	s_in[i] = '\0';

	escape(s_out, s_in);
	printf("%s", s_out);

	return 0;
}

void escape(char s_out[], char s_in[]) {
	int i, j;
	
	for (i = j = 0; s_in[i] != '\0'; ++i) {
		switch(s_in[i]) {
		case '\n':
			s_out[j] = '\\';
			s_out[++j] = 'n';
			break;
		case '\t':
			s_out[j] = '\\';
			s_out[++j] = 't';
			break;
		default:
			s_out[j] = s_in[i];
			break;
		}
		++j;
	}
	s_out[j] = '\0';
}
