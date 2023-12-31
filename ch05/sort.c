#include <stdio.h>
#include <string.h>
#include "getline.c"
#include "alloc.c"

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void sort(void *lineptr[], int left, int right,
           int (*comp)(void *, void *));
int numcmp(const char *, const char *);

main(int argc, char *argv[]) {
	int nlines;
	int numeric = 0;

	if (argc > 1 && strcmp(argv[1], "-n") == 0) {
		numeric = 1;
	}	
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		sort((void **) lineptr, 0, nlines-1, 
			(int (*)(void *, void *))(numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000

int getline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL) {
			return -1;
		} else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0) {
		printf("%s\n", *lineptr++);
	}
}

void sort(void *v[], int left, int right,
           int (*comp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int i, int j);
	if (left >= right) {
		return;
	}
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++) {
		if ((*comp)(v[i], v[left]) < 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	sort(v, left, last-1, comp);
	sort(v, last+1, right, comp);
}

void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

#include <stdlib.h>

int numcmp(const char *s1, const char *s2) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2) {
		return -1;
	} else
	if (v1 > v2) {
		return 1;
	} else {
		return 0;
	}
}
