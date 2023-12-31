#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct ptrtnode {
	struct tnode *ptr;
	struct ptrtnode *left;
	struct ptrtnode *right;
};

void lowercase(char *);
struct tnode *addtree(struct tnode *, char *);
char *strdup(char *);
struct ptrtnode *createptrtree(struct tnode *, struct ptrtnode *);
struct ptrtnode *addptrtree(struct ptrtnode *, struct tnode *);
void ptrtreeprint(struct ptrtnode *);

main() {
	char c;
	char word[MAXWORD];
	struct tnode *root = NULL;
	struct ptrtnode *ptrroot = NULL;

	while ((c = getword(word, MAXWORD)) != EOF) {
		if (isalpha(c)) {
			lowercase(word);
			root = addtree(root, word);
		} 
	}

	ptrroot = createptrtree(root, ptrroot);
	ptrtreeprint(ptrroot);
	return 0;
}

void lowercase(char *word) {
	while (*word != '\0') {
		*word++ = tolower(*word);
	}
}

struct tnode *addtree(struct tnode *node, char *word) {
	int cmp;

	if (node == NULL) {
		node = (struct tnode *) malloc(sizeof(struct tnode));
		node->word = strdup(word);
		node->count = 1;
		node->left = node->right = NULL;
	} else
	if ((cmp = strcmp(word, node->word)) == 0) {
		node->count += 1;
	} else
	if (cmp < 0) {
		node->left = addtree(node->left, word);
	} else {
		node->right = addtree(node->right, word);
	}
	return node;
}

char *strdup(char *s) {
	char *p = (char *) malloc(strlen(s) + 1);
	strcpy(p, s);
	return p;
}

struct ptrtnode *createptrtree(struct tnode *node, struct ptrtnode *ptrroot) {
	if (node != NULL) {
		ptrroot = addptrtree(ptrroot, node); 
		createptrtree(node->left, ptrroot);
		createptrtree(node->right, ptrroot);
		return ptrroot;
	}
}

struct ptrtnode *addptrtree(struct ptrtnode *ptrnode, struct tnode *node) {
	int cmp;

	if (ptrnode == NULL) {
		ptrnode = (struct ptrtnode *) malloc(sizeof(struct ptrtnode));
		ptrnode->ptr = node;
		ptrnode->left = ptrnode->right = NULL;
	} else {
		cmp = ptrnode->ptr->count - node->count;
		if (cmp == 0) {
			cmp = strcmp(node->word, ptrnode->ptr->word);
		}
		if (cmp < 0) {
			ptrnode->left = addptrtree(ptrnode->left, node);
		} else {
			ptrnode->right = addptrtree(ptrnode->right, node);
		}
	}

	return ptrnode;
}

void ptrtreeprint(struct ptrtnode *ptrnode) {
	if (ptrnode != NULL) {
		ptrtreeprint(ptrnode->left);
		printf("%4d %s\n", ptrnode->ptr->count, ptrnode->ptr->word);
		ptrtreeprint(ptrnode->right);
	}
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
