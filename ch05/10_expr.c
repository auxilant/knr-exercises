#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTACK 100
#define ERROR 1

main(int argc, char *argv[]){
	double stack[MAXSTACK];
	double *freeptr = stack;

	int is_number;

	while (--argc > 0) {
		if (strlen(*++argv) == 1 && (**argv=='+' || **argv=='-' || **argv=='x' || **argv=='/')) {
			is_number = 0;
		} else {
			is_number = 1;
		}

		if (is_number) {
			if (freeptr - stack >= MAXSTACK) {
				printf("error: too many operands\n");
				return ERROR;
			}
			*freeptr++ = atof(*argv);
		} else {
			if (freeptr - stack < 2) {
				printf("error: wrong use of operator\n");
				return ERROR;
			}
			switch(**argv) {
			case '+':
				freeptr--;
				*(freeptr - 1) += *freeptr;
				break;
			case '-':
				freeptr--;
				*(freeptr - 1) -= *freeptr;
				break;
			case 'x':
				freeptr--;
				*(freeptr - 1) *= (*freeptr);
				break;
			case '/':
				if (*--freeptr == 0) {
					printf("error: division by 0\n");
					return ERROR;
				}
				*(freeptr - 1) /= *freeptr;
				break;
			}
		}
	}

	if (freeptr - stack != 1) {
		printf("error: incomplete expression\n");
		return ERROR;
	}
	printf("%g\n", *stack);

	return 0;
}
