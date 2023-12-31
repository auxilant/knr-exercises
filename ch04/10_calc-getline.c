#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXOP 100
#define VARIABLES 26

#define NUMBER '0'
#define COMMAND '$'
#define FUNCTION '~'
#define VARIABLE '?'
#define VAR_ASSIGNMENT '='
#define LAST_PRINTED '_'

int getop(char[]);
int getline(char[], int);

void push(double);
double pop(void);
void print_stack(void);
void print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);

main() {
	int type;
	double op1, op2;
	int op2_int;
	char s[MAXOP];
	int i;
	double vars[VARIABLES];
	double last_printed = 0;
	for (i = 0; i < VARIABLES; ++i) {
		vars[i] = 0;
	}

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
		case '^':
			op2 = pop();
			op1 = pop();
			if (op1 == 0 && op2 <= 0) {
				printf("error: domain error\n");
			} else
			if (op1 < 0) {
				push(pow(op1,(int)op2)); /* if op1<0 and op2 isn't int, would be error */
			} else {
				push(pow(op1, op2));
			}
			break;
		case FUNCTION:
			if (strcmp(s, "sin") == 0) {
				push(sin(pop()));
			} else
			if (strcmp(s, "cos") == 0) {
				push(cos(pop()));
			} else
			if (strcmp(s, "tan") == 0) {
				push(tan(pop()));
			} else
			if (strcmp(s, "exp") == 0) {
				push(exp(pop()));
			} else
			if (strcmp(s, "sqrt") == 0) {
				push(sqrt(pop()));
			} else
			if (strcmp(s, "log") == 0) {
				push(log(pop()));
			} else {
				printf("error: unknown function %s\n", s);
			}
			break;
		case VARIABLE:
			if (islower(s[0])) {
				push(vars[s[0] - 'a']);
			} else
			if (isupper(s[0])) {
				push(vars[s[0] - 'A']);
			} else {
				printf("error: bad variable %s: (use letters a-z)\n", s);
			}
			break;
		case VAR_ASSIGNMENT:
			if (islower(s[0])) {
				vars[s[0] - 'a'] = pop();
			} else
			if (isupper(s[0])) {
				vars[s[0] - 'A'] = pop();
			} else {
				printf("error: bad variable %s: (use letters a-z)\n", s);
			}
			break;
		case LAST_PRINTED:
			push(last_printed);
			break;
		case '\n':
			printf("\t%.8g\n", last_printed = pop());
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
	if (sp > 1) {
		tmp = val[sp-1];
		val[sp-1] = val[sp-2];
		val[sp-2] = tmp;
	}
}

void clear_stack(void) {
	sp = 0;
}

#include <ctype.h>
 
#define MAXLINE 100

char line[MAXLINE];
int reading_line = 0;
int pos;

int getop(char s[]) {
	if (!reading_line) {
		reading_line = 1;
		if (getline(line, MAXLINE) == 0) {
			return EOF;
		}
		pos = 0;
	}
	int c;
	int i = 0;

	while ((s[0] = c = line[pos++]) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if (!isalnum(c) && c != '.' && c != '-' &&  c != '$' && c != '=') {
		if (c == '\n') {
			reading_line = 0;
		}
		return c;
	}

	if (c == '=') {
		s[0] = c = line[pos++];
		c = line[pos++];
		if (c != '\n') {
			pos--;
		} else {
			reading_line = 0;
		}
		return VAR_ASSIGNMENT;
	}

	if (c == '$') {
		--i; /* delete $ */
		while(isalpha(s[++i] = c = line[pos++]))
			;
		s[i] = '\0';
		if (c != '\n') {
			pos--;
		} else {
			reading_line = 0;
		}
		return COMMAND;
	}

	if (isalpha(c)) {
		c = line[pos++];
		pos--;
		if (!isalpha(c)) {
			return VARIABLE;
		}

		while(isalpha(s[++i] = c = line[pos++]))
			;
		s[i] = '\0';
		pos--;
		return FUNCTION;
	}

	if (c == '-') {
		if ((c = line[pos++]) == ' ' || c == '\t') {
			return '-';
		} else {
			s[0] = '-';
			s[1] = c;
			++i;
		}
	}
	if (isdigit(c)) {
		while (isdigit(s[++i] = c = line[pos++]))
			;
	}
	if (c == '.') {
		while (isdigit(s[++i] = c = line[pos++]))
			;
	} 
	s[i] = '\0';
	pos--;
	return NUMBER;
}

int getline(char s[], int lim) {
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		s[i++] = c;
	}
	if (c == '\n') {
		s[i++] = c;
	}

	s[i] = '\0';
	return i;
}
