#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getch(void);

int getop(char s[]) {
	static int c;
	static int read_c = 0;
	int i = 0;

	if (read_c && c != ' ' && c != '\t') {
		;	
	} else {
		while ((c = getch()) == ' ' || c == '\t')
			;
	}
	read_c = 0;
	s[0] = c;
	s[1] = '\0';

	if (!isalnum(c) && c != '.' && c != '-' &&  c != '$' && c != '=') {
		return c;
	}

	if (c == '=') {
		s[0] = c = getch();
		c = getch();
		if (c != '\n') {
			read_c = 1;
		}
		return VAR_ASSIGNMENT;
	}

	if (c == '$') {
		--i; /* delete $ */
		while(isalpha(s[++i] = c = getch()))
			;
		s[i] = '\0';
		if (c != '\n') {
			read_c = 1;
		}
		return COMMAND;
	}

	if (isalpha(c)) {
		c = getch();
		read_c = 1;
		if (!isalpha(c)) {
			return VARIABLE;
		}
	
		if (isalpha(c)) {
			s[++i] = c;
			while(isalpha(s[++i] = c = getch()))
				;
		}
		s[i] = '\0';
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
	read_c = 1;
	return NUMBER;
}
