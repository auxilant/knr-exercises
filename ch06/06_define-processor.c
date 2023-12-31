#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "getch.c"

#define HASHSIZE 101
#define MAXNAME 100
#define MAXLINE 250

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *);
char *strdup(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void freenlist(struct nlist *np);
void undef(char *);

int getch(void);
void ungetch(int);

int getidentifier(char *, int);
int getline(char *, int);

enum State {
	NORMAL,
	LINESTART,
	LOOKINGFORDIRECTIVE,
	DEFINE,
	UNDEF,
};

main() {
	char c, name[MAXNAME], linebeginning[MAXNAME], replacement[MAXLINE];
	struct nlist *tableptr;
	enum State state = LINESTART;

	while ((c = getidentifier(name, MAXNAME)) != EOF) {
		switch (state) {
		case LINESTART:
			*linebeginning = '\0';
			if (c == ' ' || c == '\t') {
				strcat(linebeginning, name);
				c = getidentifier(name, MAXNAME);
			}

			if (c == '#') {
				state = LOOKINGFORDIRECTIVE;
				strcat(linebeginning, "#");
			} else {
				state = NORMAL;
				printf("%s", linebeginning);
			}
			break;
		case LOOKINGFORDIRECTIVE:
			if (c == ' ' || c == '\t') {
				strcat(linebeginning, name);
				c = getidentifier(name, MAXNAME);
			}

			if (strcmp(name, "define") == 0) {
				state = DEFINE;
			} else
			if (strcmp(name, "undef") == 0) {
				state = UNDEF;
			} else {
				state = NORMAL;
				printf("%s", linebeginning);
			}
			break;
		case DEFINE:
			if (c != ' ' && c != '\t') {
				printf("\nERROR: expected space after define\n");
				return 1;
			}

			c = getidentifier(name, MAXNAME);
			if (c != '_' && !isalpha(c)) {
				printf("\nERROR: bad identifier\n");
				return 1;
			}
			c = getidentifier(replacement, MAXLINE);
			if (c != ' ' && c != '\t') {
				printf("\nERROR: expected space after identifier\n");
				return 1;
			}	
			getline(replacement, MAXLINE);
			install(name, replacement);
			state = LINESTART;
			break;
		case UNDEF:
			if (c != ' ' && c != '\t') {
				printf("\nERROR: expected space after undef\n");
				return 1;
			}

			c = getidentifier(name, MAXNAME);
			if (c != '_' && !isalpha(c)) {
				printf("\nERROR: bad identifier\n");
				return 1;
			}
			undef(name);

			do {
				c = getidentifier(name, MAXNAME);
			} while (c == ' ' || c == '\t');
			if (c != '\n') {
				printf("\nERROR: unexpected characters after undef\n");
				return 1;
			}
			state = LINESTART;
			break;
		}

		if (state == NORMAL) {
			if (strlen(name) > 0) {
				tableptr = lookup(name);
				if (tableptr == NULL) {
					printf("%s", name);
				} else {
					printf("%s", tableptr->defn);
				}
			} else {
				putchar(c);
			}
		}
		
		if (c == '\n') {
			state = LINESTART;
		}
	}

	return 0;
}

unsigned hash(char *s) {
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++) {
		hashval = *s + 31 * hashval;
	}
	return hashval % HASHSIZE;
}

char *strdup(char *s) {
	char* p;
	p = (char *) malloc(strlen(s) + 1);
	strcpy(p, s);
	return p;
}

struct nlist *lookup(char *s) {
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0) {
			return np;
		}
	}
	return NULL;
}

struct nlist *install(char *name, char *defn) {
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL) {
			return NULL;
		}
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else {
		free((void *) np->defn);
	}

	if ((np->defn = strdup(defn)) == NULL) {
		return NULL;
	}
	return np;
}

void freenlist(struct nlist *np) {
	free((void *) np->name);
	free((void *) np->defn);
	free((void *) np);
}

void undef(char *name) {
	struct nlist *np, *npnext;
	unsigned hn;

	hn = hash(name);
	np = hashtab[hn];
	if (np == NULL) {
		return;
	}

	if (strcmp(name, np->name) == 0) {
		hashtab[hn] = NULL;
		freenlist(np);
		return;
	}

	while (strcmp(name, np->next->name) != 0) {
		np = np->next;
	}
	np->next = np->next->next;
	freenlist(np->next);
}


int getidentifier(char *name, int limit) {
	int c = getch();
	int c0 = c;

	if (c == ' ' || c == '\t') {
		while (--limit > 0 && (c == ' ' || c == '\t')) {
			*name++ = c;
			c = getch();
		}
		if (limit > 0) {
			ungetch(c);
		}
	} else
	if (isalpha(c) || c == '_') {
		while (--limit > 0 && (isalnum(c) || c == '_')) {
			*name++ = c;
			c = getch();
		}
		if (limit > 0) {
			ungetch(c);
		}
	}
	*name = '\0';

	return c0;
}

int getline(char *line, int limit) {
	int c;
	char *startptr = line;

	while (--limit > 0 && c != '\n' && c != EOF) {
		c = *line++ = getch();
	}
	if (c == '\n') {
		line--;
	}
	*line = '\0';

	return line - startptr;
}
