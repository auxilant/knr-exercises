#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

#define ERROR 1
#define SUCCESS 0

enum { NAME, PARENS, BRACKETS };

void movetonewline(void);
void getqualifiers(void);
void getdatatype(void);
int dcl(void);
int dirdcl(void);
void paramlist(void);

void ungettoken(void);
int gettoken(void);
int ttype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char qualifiers[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

main() {
	while (gettoken() != EOF) {
		getqualifiers();
		getdatatype();
		ungettoken();
		out[0] = '\0';

		if (dcl() == ERROR) {
			movetonewline();
		} else
		if (ttype != '\n') {
			printf("syntax error\n");
			movetonewline();
		} else {
			printf("%s: %s %s %s\n", name, qualifiers, out, datatype);
		}
	}
	return 0;
}

void getqualifiers() {
	qualifiers[0] = '\0';
	while (ttype == NAME &&
	       (strcmp(token, "const") == 0 || strcmp(token, "volatile") == 0 ||  
	        strcmp(token, "register") == 0 || strcmp(token, "static") == 0 ||
	        strcmp(token, "extern") == 0 || strcmp(token, "auto") == 0 ) ) { 
		strcat(qualifiers, token);
		strcat(qualifiers, " ");
		gettoken();
	}
}

void getdatatype() {
	datatype[0] = '\0';
	while (ttype == NAME &&
	       (strcmp(token, "void") == 0 || strcmp(token, "char") == 0 ||  
	       strcmp(token, "short") == 0 || strcmp(token, "int") == 0 ||
	       strcmp(token, "long") == 0 || strcmp(token, "float") == 0 ||
	       strcmp(token, "double") == 0 || strcmp(token, "signed") == 0 ||
	       strcmp(token, "unsigned") == 0 ) ) { 
		strcat(datatype, token);
		strcat(datatype, " ");
		gettoken();
	}
}

void movetonewline(void) {
	if (ttype == '\n') {
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
	if (ttype == '(') {
		if (dcl() == ERROR) {
			return ERROR;
		}
		if (ttype != ')') {
			printf("error: missing )\n");
			return ERROR;
		}
	} else
	if (ttype == NAME) {
		strcpy(name, token);
	} else {
		printf("error: expected name or (dcl)\n");
		return ERROR;
	}

	while ((ttype = gettoken()) == PARENS || ttype == BRACKETS || ttype == '(' || ttype == '[') {
		if (ttype == '[') {
			printf("error: missing ]\n");
			return ERROR;
		}

		if (ttype == '(') {
			strcat(out, " function with parameters: ");
			paramlist();
			if (ttype != ')') {
				printf("error: missing )\n");
				return ERROR;
			}
			strcat(out, " returning");
		} else
		if (ttype == PARENS) {
			strcat(out, " function returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}

	return SUCCESS;
}

void paramlist(void) {
	while ((ttype = gettoken()) != ')' && ttype != '\n' && ttype != EOF) {
		strcat(out, token);
		strcat(out, " ");
	}
}

#include "getch.c"

int tokenungoten;

void ungettoken(void) {
	tokenungoten = 1; 
}

int gettoken(void) {
	if (tokenungoten) {
		tokenungoten = 0;
		return ttype;
	}

	int c, getch(void);
	void ungetch(int);
	char *p = token;
	
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return ttype = PARENS;
		} else {
			ungetch(c);
			return ttype = '(';
		}
	} else 
	if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; ) {
			if (*(p-1) == '\n') {
				ungetch('\n');
				return ttype = '['; /* error */
			}
		}
		*p = '\0';
		return ttype = BRACKETS;
	} else
	if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); ) {
			*p++ = c;
		}
		*p = '\0';
		ungetch(c);
		return ttype = NAME;
	} else {
		*p++ = c;
		*p = '\0';
		return ttype = c;
	}
}
