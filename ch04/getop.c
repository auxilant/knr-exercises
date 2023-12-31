#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getch(void);
void ungetch(int);

int getop(char s[]) {
	int c;
	int i = 0;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if (!isalnum(c) && c != '.' && c != '-' &&  c != '$' && c != '=') {
		return c;
	}

	if (c == '=') {
		s[0] = c = getch();
		c = getch();
		if (c != '\n') {
			ungetch(c);
		}
		return VAR_ASSIGNMENT;
	}

	if (c == '$') {
		--i; /* delete $ */
		while(isalpha(s[++i] = c = getch()))
			;
		s[i] = '\0';
		if (c != '\n') {
			ungetch(c);
		}
		return COMMAND;
	}

	if (isalpha(c)) {
		c = getch();
		ungetch(c);
		if (!isalpha(c)) {
			return VARIABLE;
		}

		while(isalpha(s[++i] = c = getch()))
			;
		s[i] = '\0';
		ungetch(c);
		return FUNCTION;
	}

	if (c == '-') {
		if ((c = getch()) == ' ' || c == '\t') {
			return '-';
		} else {
			s[0] = '-';
			s[1] = c;
			++i;
		}
	}
	if (isdigit(c)) {
		while (isdigit(s[++i] = c = getch()))
			;
	}
	if (c == '.') {
		while (isdigit(s[++i] = c = getch()))
			;
	} 
	s[i] = '\0';
	ungetch(c);
	return NUMBER;
}
