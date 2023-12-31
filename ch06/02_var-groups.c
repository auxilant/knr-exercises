#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct varnode {
	char *var;
	struct varnode *left;
	struct varnode *right;
};

struct tnode {
	char *group;
	struct tnode *left;
	struct tnode *right;
	struct varnode *vars;
};

int isvartype(char *);

struct tnode *addtree(struct tnode*, char *, int);
struct varnode *addvartree(struct varnode*, char *);
struct tnode *talloc(void);
struct varnode *varalloc(void);
char *strdup(char *);
char *strndup (char *, int);

void treeprint(struct tnode *);
void vartreeprint(struct varnode *);

int getword(char *, int);

main(int argc, char *argv[]) {
	int n;

	switch (argc) {
	case 1:
		n = 6;
		break;
	case 3:
		if (strcmp(argv[1], "-n") == 0) {
			n = atoi(argv[2]);
			if (n <= 0) {
				printf("error: not a positive integer\n");
				return 1;
			}
		} else {
			printf("error: bad arguments (use -n <number>)\n");
			return 1;
		}
		break;
	default:
		printf("error: bad arguments (use -n <number>)\n");
		return 1;
	}

	int maybevariable = 0;
	int skipgetword = 0;

	struct tnode *root = NULL;
	char c;
	char word[MAXWORD], nextword[MAXWORD];

	while (c != EOF) {
		if (skipgetword) {
			skipgetword = 0;
			strcpy(word, nextword);
		} else {
			c = getword(word, MAXWORD);
		}

		if (maybevariable) {
			c = getword(nextword, MAXWORD);
			if (c == '(' || c == '=' || c == ';') {
				maybevariable = 0;
			}
			if (c != '(' && isalnum(word[0]) && !isvartype(word) && strlen(word) >= n) {
				root = addtree(root, word, n);
			}
			if (strlen(nextword) > 0) {
				skipgetword = 1;
			}
		} else
		if (isvartype(word)) {
			maybevariable = 1;
		}
	}

	treeprint(root);
	return 0;
}

int isvartype(char *word) {
	if (strcmp(word, "char") == 0 || strcmp(word, "short") == 0 ||
        strcmp(word, "int") == 0 || strcmp(word, "long") == 0 ||
        strcmp(word, "float") == 0 || strcmp(word, "double") == 0 ||
        strcmp(word, "signed") == 0 || strcmp(word, "unsigned") == 0 ) {
		return 1;
	}
	return 0;
}

struct tnode *addtree(struct tnode* node, char *var, int n) {
	int comp;

	if (node == NULL) {
		node = talloc();
		node->group = strndup(var, n);
		node->left = node->right = NULL;
		node->vars = NULL;
		node->vars = addvartree(node->vars, var);
	} else 
	if ((comp = strncmp(var, node->group, n)) == 0) {
		node->vars = addvartree(node->vars, var);
	} else
	if (comp < 0) {
		node->left = addtree(node->left, var, n);
	} else {
		node->right = addtree(node->right, var, n);
	}
	return node;
}

struct varnode *addvartree(struct varnode* node, char *var) {
	int comp;

	if (node == NULL) {
		node = varalloc();
		node->var = strdup(var);
		node->left = node->right = NULL;
	} else
	if ((comp = strcmp(var, node->var)) < 0) {
		node->left = addvartree(node->left, var);
	} else
	if (comp > 0) {
		node->right = addvartree(node->right, var);
	}
	return node;
}

struct tnode *talloc(void) {
	return (struct tnode *) malloc (sizeof (struct tnode));
}

struct varnode *varalloc(void) {
	return (struct varnode *) malloc (sizeof (struct varnode));
}

char *strdup(char *s) {
	char *p;
	
	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL) {
		strcpy(p, s);
	}
	return p;
}

char *strndup(char *s, int n) {
	char *p;
	
	p = (char *) malloc(n + 1);
	if (p != NULL) {
		strncpy(p, s, n);
	}
	return p;
}

void treeprint(struct tnode* node) {
	if (node != NULL) {
		treeprint(node->left);
		vartreeprint(node->vars);
		putchar('\n');
		treeprint(node->right);
	}
}

void vartreeprint(struct varnode* node) {
	if (node != NULL) {
		vartreeprint(node->left);
		printf("%s ", node->var);
		vartreeprint(node->right);
	}
}

#include "getch.c"

int getword(char *word, int lim) {
	int c, cprev, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c == '"') {
		while ((c = getch()) != '"') {
			if (c == '\\') {
				getch();
			}
		}
	} else
	if (c == '\'') {
		while ((c = getch()) != '\'') {
			if (c == '\\') {
				getch();
			}
		}
	} else
	if (c == '#') {
		while ((c = getch()) != '\n')
			;
	} else
	if (c == '/') {
		if ((c = getch()) == '*') {
			while ((c = getch()) != '/' || cprev != '*') {
				cprev = c;
			}
		} 
		else {
			ungetch(c);
			c = '/';
		}
	}

	if (c != EOF) {
		*w++ = c;
	}

	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++) {
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}
