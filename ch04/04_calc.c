#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define COMMAND '$'

int getop(char[]);

void push(double);
double pop(void);
void print_stack(void);
void print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);

main() {
	int type;
	double op2;
	int op2_int;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case COMMAND:
			if (strcmp(s, "printall") == 0) {
				print_stack();
			} else
			if (strcmp(s, "print") == 0) {
				print_top();
			} else
			if (strcmp(s, "dupl") == 0) {
				duplicate_top();
			} else
			if (strcmp(s, "swap") == 0) {
				swap_top();
			} else
			if (strcmp(s, "clear") == 0) {
				clear_stack();
			} else {
				printf("error: unknown command %s\n", s);
			}
			break;
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0) {
				push(pop() / op2);
			} else {
				printf("error: zero divisor\n");
			}
			break;
		case '%':
			op2_int = (int)(pop());
			if (op2_int != 0) {
				push((int)(pop()) % op2_int);
			} else {
				printf("error: zero divisor\n");
			}
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	
	return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
	} else {
		printf("error: stack full, can't push %g\n", f);
	}
}

double pop(void) {
	if (sp > 0) {
		return val[--sp];
	} else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

void print_stack(void) {
	int i;
	for (i = 0; i < sp; ++i) {
		printf("%g ", val[i]);
	}
	if (sp == 0) {
		printf("stack empty");
	}
	printf("\n");
}	

void print_top(void) {
	if (sp == 0) {
		printf("stack empty\n");
	} else {
		printf("%g\n", val[sp-1]);
	}
}

void duplicate_top(void) {
	push(val[sp-1]);
}

void swap_top(void) {
	double tmp;
	if (sp > 0) {
		tmp = val[sp-1];
		val[sp-1] = val[sp-2];
		val[sp-2] = tmp;
	}
}

void clear_stack(void) {
	sp = 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[]) {
	int c;
	int mode = 0;
	int i = 0;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if (!isdigit(c) && c != '.' && c != '-' && !isalpha(c)) {
		return c;
	}

	if (isalpha(c)) {
		mode = COMMAND;
		while(isalpha(s[++i] = c = getch()))
			;
	}
	if (mode == COMMAND) {
		s[i] = '\0';
		if (c != EOF && c != '\n') {
			ungetch(c);
		}
		return mode;
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
		mode = NUMBER;
		while (isdigit(s[++i] = c = getch()))
			;
	}
	if (c == '.') {
		mode = NUMBER;
		while (isdigit(s[++i] = c = getch()))
			;
	} 
	s[i] = '\0';
	
	if (c != EOF) {
		ungetch(c);
	}
	return mode;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
	} else {
		buf[bufp++] = c;
	}
}
