#include <stdio.h>

#define TRUE 1 /* inside quotes / comments */
#define FALSE 0 /* outside quotes / comments */

int toggle(int state);
void testfunc(void); /* never called *//* used for testing itself */

main() {
	char c, pc, ppc; /* current, previous and one before previous */
	c = pc = ppc = 0;
	int in_single_quotes, in_double_quotes, in_comment, just_left_comment;
	in_single_quotes = in_double_quotes = in_comment = just_left_comment = FALSE;

	while ((c = getchar()) != EOF) {
		if (in_comment == FALSE) {
			/* check if ' is escaped by backslash (also check if backslash is escaped) */
			if (c == '\'' && (pc != '\\' || (pc == '\\' && ppc == '\\')) && in_double_quotes == FALSE) {
				in_single_quotes = toggle(in_single_quotes);
				putchar(c);
			} else /* similarly for double quotes */
			if (c == '\"' && (pc != '\\' || (pc == '\\' && ppc == '\\')) && in_single_quotes == FALSE) {
				in_double_quotes = toggle(in_double_quotes);
				putchar(c);
			} else
			if (in_single_quotes == FALSE && in_double_quotes == FALSE) {
				if (c == '*' && pc == '/') {
					in_comment = TRUE;
				} else
				if (c != '/') { /* hold '/' in case it's the beginning of comment */
					putchar(c); 
					if (pc == '/') {
						if (just_left_comment == TRUE) {
							just_left_comment = FALSE;
						} else {
							putchar(pc); /* c != '*', so now we can print '/' */
						}
					}
				}
			} else { /* either in single or double quotes */
				putchar(c);
			}
		} else { /* in_comment == TRUE */
			if (c == '/' && pc == '*') {
				in_comment = FALSE;
				just_left_comment = TRUE;
			}
		}

		/* shift previous characters to prepare for the next one */
		ppc = pc;
		pc = c;
	}

	return 0;
}

int toggle(int state) {
	if (state == FALSE) {
		return TRUE;
	}
	return FALSE;
}

void testfunc() {
	printf("a\"b\'c\\"); /* 1 */
	printf("/*hello, world*/"); /* 2 */
}
