#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calc.h"

#define MAXOP 100
#define VARIABLES 26

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
