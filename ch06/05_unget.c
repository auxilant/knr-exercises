#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 101

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
void printtable(void);

main() {
	install("aaa", "111");	
	install("bbb", "222");	
	install("ccc", "000");	
	install("ccc", "333");	
	install("ddd", "444");
	install("skjfkdsjfksjd", "lskjfdl");
	install("fnnvc", "vnsdlkj");

	undef("bbb");
	undef("ccc");
	
	printtable();
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

void printtable(void) {
	int i;
	struct nlist *np;

	for (i = 0; i < HASHSIZE; i++) {
		for (np = hashtab[i]; np != NULL; np = np->next) {
			printf("%s %s\n", np->name, np->defn);
		}
	}
}
