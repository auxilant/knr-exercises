#include <stdio.h>
#include <ctype.h>

void expand(char input[], char output[]);

main() {
	const int limit = 1000;
	char s_in[limit+1], s_out[limit+1];
	char c;
	int i = 0;

	while ( ((c = getchar()) != EOF) && (i < limit) ) {
		s_in[i++] = c;
	}
	s_in[i] = '\0';

	expand(s_in, s_out);
	printf("%s", s_out);

	return 0;
}

void expand(char s_in[], char s_out[]) {
	int i, j;
	const char expand_operator = '-';
	int expand_detected;
	int start, end;
	char c;

	for (i = j = 0; s_in[i] != '\0'; ) {
		expand_detected = 0;

		if (s_in[i+1] == expand_operator) {
			start = s_in[i];
			end = s_in[i+2];
			if ( (islower(start) && islower(end)) ||
			     (isupper(start) && isupper(end)) ||
			     (isdigit(start) && isdigit(end)) ) {
				expand_detected = 1;
			}
		}
			
		if (expand_detected) {
			if (start < end) {
				for (c = start; c <= end; ++c) {
					s_out[j++] = c;
				}
			} else {
				for (c = start; c >= end; --c) {
					s_out[j++] = c;
				}
			}
			i += 3;
		} else {
			s_out[j] = s_in[i];
			++i;
			++j;
		}
	}
	s_out[j] = '\0';
}
