#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

main() {
	while (gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if (tokentype != '\n') {
			printf("syntax error\n");
		}
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

void dcl(void) {
	int ns;

	for (ns = 0; gettoken() == '*'; ) {
		ns++;
	}
	dirdcl();
	while (ns-- > 0) {
		strcat(out, " pointer to");
	}
}

void dirdcl(void) {
	int type;

	if (tokentype == '(') {
		dcl();
		if (tokentype != ')') {
			printf("error: missing )\n");
		}
	} else
	if (tokentype == NAME) {
		strcpy(name, token);
	} else {
		printf("error: expected name or (dcl)\n");
	}

	while ((type = gettoken()) == PARENS || type == BRACKETS) {
		if (type == PARENS) {
			strcat(out, " function returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

#include "gettoken.c"
