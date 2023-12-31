#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100
#define MAXSTACK 50

char *skipinput(char *);
int getline(char [], int);

void push(double);
double pop(void);
void printstack(void);
void handleoperator(char);

double stack[MAXSTACK];
double *stackptr = stack;

main() {
	double num;
	char op;

	char line[MAXLINE];
	char *lineptr;
	while (getline(line, MAXLINE) > 0) {
		lineptr = line;
		while (lineptr < line + MAXLINE) {
			if (sscanf(lineptr, "%lf", &num) == 1) {
				lineptr = skipinput(lineptr);
				push(num);
			} else
			if (sscanf(lineptr, "%1s", &op) == 1) {
				lineptr = skipinput(lineptr);
				handleoperator(op);
			} else {
				break;
			}
		}
		printf("\t%g\n", pop());
		printstack();
	}

	return 0;
}

char *skipinput(char *ptr) {
	while (isspace(*ptr)) {
		ptr++;
	}
	while (!isspace(*ptr) && *ptr != '\0') {
		ptr++;
	}
	return ptr;
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

void push(double num) {
	if (stackptr - stack < MAXSTACK) {
		*stackptr++ = num;
	} else {
		printf("error: stack too large\n");
	}
}

double pop(void) {
	if (stackptr <= stack) {
		printf("error: stack empty\n");
		return 0;
	} 
	return *--stackptr;
}

void printstack(void) {
	double *ptr;
	for (ptr = stack; ptr < stackptr; ptr++) {
		printf("%lg ", *ptr);
	}
}

void handleoperator(char op) {
	double num1, num2;
	num2 = pop();
	num1 = pop();

	switch(op) {
	case '+':
		push(num1 + num2);
		break;
	case '-':
		push(num1 - num2);
		break;
	case '*':
		push(num1 * num2);
		break;
	case '/':
		if (num2 == 0) {
			printf("error: division by 0\n");
			return;
		}
		push(num1 / num2);
		break;
	default:
		printf("error: unknown operator %c\n", op);
		return;
	}
}
