#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100

struct lnode {
	int line;
	struct lnode *next;
};

struct tnode {
	char *word;
	struct lnode *lines;
	struct tnode *left;
	struct tnode *right;
};

char *blockedwords[] = {"a", "an", "the", "and", "is", "isn't", "was", "wasn't", "in", "to", "of", "s"};

void lowercase(char *);
int isblocked(char *);
struct tnode *addtree(struct tnode *, char *, int);
char *strdup(char *);
void addlinenumber(struct tnode *, int);
void treeprint(struct tnode *);
void listprint(struct lnode *);

main() {
	int linenumber = 1;
	char c;
	char word[MAXWORD];
	struct tnode *root = NULL;

	while ((c = getword(word, MAXWORD)) != EOF) {
		if (isalpha(c)) {
			lowercase(word);
			if (!isblocked(word)) {
				root = addtree(root, word, linenumber);
			}
		} else
		if (c == '\n') {
			linenumber++;
		}
	}

	treeprint(root);
	return 0;
}

void lowercase(char *word) {
	while (*word != '\0') {
		*word++ = tolower(*word);
	}
}

int isblocked(char *word) {
	int i;
	for (i = 0; i < sizeof(blockedwords)/sizeof(char *); i++) {
		if (strcmp(word, blockedwords[i]) == 0 ) {
			return 1;
		}
	}
	return 0;
}

struct tnode *addtree(struct tnode *node, char *word, int linenumber) {
	int cmp;

	if (node == NULL) {
		node = (struct tnode *) malloc(sizeof(struct tnode));
		node->word = strdup(word);
		node->lines = (struct lnode *) malloc(sizeof(struct lnode));
		node->lines->line = linenumber;
		node->lines->next = NULL;
		node->left = node->right = NULL;
	} else
	if ((cmp = strcmp(word, node->word)) == 0) {
		addlinenumber(node, linenumber);
	} else
	if (cmp < 0) {
		node->left = addtree(node->left, word, linenumber);
	} else {
		node->right = addtree(node->right, word, linenumber);
	}
	return node;
}

char *strdup(char *s) {
	char *p = (char *) malloc(strlen(s) + 1);
	strcpy(p, s);
	return p;
}

void addlinenumber(struct tnode *node, int linenumber) {
	struct lnode *listptr = node->lines;

	while (listptr->next != NULL) {
		listptr = listptr->next;
	}
	if (listptr->line != linenumber) {
		listptr = listptr->next = (struct lnode *) malloc(sizeof(struct lnode));
		listptr->line = linenumber;
		listptr->next = NULL;
	}
}

void treeprint(struct tnode *node) {
	if (node != NULL) {
		treeprint(node->left);
		printf("%s ", node->word);
		listprint(node->lines);
		putchar('\n');
		treeprint(node->right);
	}
}

void listprint(struct lnode *node) {
	while (node->next != NULL) {
		printf("%d, ", node->line);
		node = node->next;
	}
	printf("%d", node->line);
}

#include "getch.c"

int getword(char *word, int lim) {
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()) && c != '\n') 
		;
	if (c != EOF) {
		*w++ = c;
	}
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++) {
		if (!isalnum(*w = getch()) && *w != '\'') {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}
