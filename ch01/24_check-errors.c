#include <stdio.h>

#define TRUE 1
#define FALSE 0

int toggle(int state);

main() {
	int rounds, squares, curlies; /* count unclosed brackets */
	rounds = squares = curlies = 0;	
	
	char c, pc, ppc; /* current, previous and one before previous */
	c = pc = ppc = 0;
	
	int in_singles, in_doubles, in_comment;
	in_singles = in_doubles = in_comment = FALSE;
	
	while ((c = getchar()) != EOF) {
		if (in_comment == FALSE) {
			/* check if ' or " is escaped by backslash (also check if backslash is escaped) */
			if (c == '\'' && (pc != '\\' || (pc == '\\' && ppc == '\\')) && in_doubles == FALSE) {
				in_singles = toggle(in_singles);
			} else 
			if (c == '\"' && (pc != '\\' || (pc == '\\' && ppc == '\\')) && in_singles == FALSE) {
				in_doubles = toggle(in_doubles);
			} else
			if (in_singles == FALSE && in_doubles == FALSE) {
				if (c == '*' && pc == '/') {
					in_comment = TRUE;
				} else {
					if (c == '(') {
						++rounds;
					} else
					if (c == ')') {
						--rounds;
					} else
					if (c == '[') {
						++squares;
					} else
					if (c == ']') {
						--squares;
					} else
					if (c == '{') {
						++curlies;
					} else
					if (c == '}') {
						--curlies;
					} 
				}
			} 
		} else { /* in_comment == TRUE */
			if (c == '/' && pc == '*') {
				in_comment = FALSE;
			}
		}

		ppc = pc;
		pc = c;
	}

	if (rounds > 0) {
		printf("Error: unmatched '('\n");
	} else
	if (rounds < 0) {
		printf("Error: unmatched ')'\n");
	}

	if (squares > 0) {
		printf("Error: unmatched '['\n");
	} else
	if (squares < 0) {
		printf("Error: unmatched ']'\n");
	}

	if (curlies > 0) {
		printf("Error: unmatched '{'\n");
	} else
	if (curlies < 0) {
		printf("Error: unmatched '}'\n");
	}

	if (in_singles == TRUE) {
		printf("Error: unmatched \"'\"\n");
	}
	if (in_doubles == TRUE) {
		printf("Error: unmatched '\"'\n");
	}

	if (in_comment == TRUE) {
		printf("Error: unfinished comment\n");
	}
	return 0;
}

int toggle(int state) {
	if (state == FALSE) {
		return TRUE;
	}
	return FALSE;
}
