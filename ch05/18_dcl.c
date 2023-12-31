#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

#define ERROR 1
#define SUCCESS 0

enum { NAME, PARENS, BRACKETS };

void movetonewline(void);
int dcl(void);
int dirdcl(void);

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
		if (dcl() == ERROR) {
			movetonewline();
			continue;
		}
		if (tokentype != '\n') {
			printf("syntax error\n");
			movetonewline();
			continue;
		}
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

void movetonewline(void) {
	if (tokentype == '\n') {
		return;
	}
	while (gettoken() != '\n')
		;
}

int dcl(void) {
	int ns;

	for (ns = 0; gettoken() == '*'; ) {
		ns++;
	}
	if (dirdcl() == ERROR) {
		return ERROR;	
	}
	while (ns-- > 0) {
		strcat(out, " pointer to");
	}
	return SUCCESS;
}

int dirdcl(void) {
	int type;

	if (tokentype == '(') {
		if (dcl() == ERROR) {
			return ERROR;
		}
		if (tokentype != ')') {
			printf("error: missing )\n");
			return ERROR;
		}
	} else
	if (tokentype == NAME) {
		strcpy(name, token);
	} else {
		printf("error: expected name or (dcl)\n");
		return ERROR;
	}

	while ((type = gettoken()) == PARENS || type == BRACKETS || type == '[') {
		if (type == '[') {
			printf("error: missing ]\n");
			return ERROR;
		}
		if (type == PARENS) {
			strcat(out, " function returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}

	return SUCCESS;
}

#include "getch.c"

int gettoken(void) {
	int c, getch(void);
	void ungetch(int);
	char *p = token;
	
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else 
	if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; ) {
			if (*(p-1) == '\n') {
				ungetch('\n');
				return tokentype = '['; /* error */
			}
		}
		*p = '\0';
		return tokentype = BRACKETS;
	} else
	if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); ) {
			*p++ = c;
		}
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else {
		return tokentype = c;
	}
}
