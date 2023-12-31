#include <stdio.h>
#include "calc.h"

#define MAXVAL 100

static int sp = 0;
static double val[MAXVAL];

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
