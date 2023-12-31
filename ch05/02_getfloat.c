#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getfloat(double *pn) {
	int c, sign;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
		if(!isdigit(c) && c != '.'){
			ungetch(c);
			(sign == 1) ? ungetch('+') : ungetch('-');
			return 0;
		}
	}

	for (*pn = 0.0; isdigit(c); c = getch()) {
		*pn = 10.0 * *pn + (c - '0');
	}
	if (c == '.') {
		c = getch();
	}
	double multiplier = 1.0;
	for ( ; isdigit(c); c = getch()) {
		*pn = 10.0 * *pn + (c - '0');
		multiplier *= 0.1;
	}
	*pn *= sign * multiplier;

	ungetch(c);
	return c;
}
