#include <stdio.h>
#include <string.h>
#include "getline.c"
#include "alloc.c"

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void sort(void *lineptr[], int left, int right,
           int (*comp)(void *, void *), int reversed);
int numcmp(char *, char *);
int strocmp(char *, char *);
int fieldcmp(char *, char *);

/* options */
int numeric = 0;
int reverse = 0;
int foldcase = 0;
int directory = 0;
int fieldsort = 0;

int argn;
char **args; 

main(int argc, char **argv) {
	int nlines;
	char c;

	if (argc > 1 && (strcmp(argv[1], "-F") == 0)) {
		fieldsort = 1;
		if (argc == 2) {
			printf("error (-F): no fields chosen\n");
			return 1;
		}
		argn = argc;
	    args = argv;
		int i;
		for (i = 2; i < argc; i++) {
			if (argv[i][0] == '-') {
				if (i == 2) {
					printf("error (-F): bad format (choose field first)\n");
					return 1;
				}
				char *c0 = argv[i];
				while (c = *++argv[i]) {
					if (c != 'n' && c != 'r' && c != 'f' && c != 'd') {
						printf("error: illegal option %c\n", c);
						return 1;
					}
				}
				argv[i] = c0;
			} else
			if (atoi(argv[i]) <= 0) {
				printf("error: illegal argument %s\n", argv[i]);
				return 1;
			}
		}
	}
	
	if (!fieldsort) {
		while (--argc > 0 && **++argv == '-') {
			while (c = *++*argv) {
				switch (c) {
				case 'n':
					numeric = 1;
					break;
				case 'r':
					reverse = 1;
					break;
				case 'f':
					foldcase = 1;
					break;
				case 'd':
					directory = 1;
					break;
				default:
					printf("error: illegal option %c\n", c);
					return 1;
				}
			}
		}
		if (argc > 0) {
			printf("error: illegal arguments\n");
			return 1;
		}
	}
	
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		sort((void **) lineptr, 0, nlines-1, 
			(int (*)(void *, void *))(fieldsort ? fieldcmp : (numeric ? numcmp : strocmp)),
			reverse);
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
           int (*comp)(void *, void *), int reversed) {
	int i, last;
	void swap(void *v[], int i, int j);
	if (left >= right) {
		return;
	}
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++) {
		if ( (!reversed && ((*comp)(v[i], v[left]) < 0)) ||
		     (reversed && ((*comp)(v[i], v[left]) > 0)) ) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	sort(v, left, last-1, comp, reversed);
	sort(v, last+1, right, comp, reversed);
}

void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

#include <stdlib.h>
#include <ctype.h>

int numcmp(char *s1, char *s2) {
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

int charcmp(char s1, char s2) {
	if (!foldcase) {
		return s1 - s2;
	}
	if (islower(s1) && isupper(s2)) {
		return s1 - s2 - 'a' + 'A';
	}
	if (isupper(s1) && islower(s2)) {
		return s1 - s2 - 'A' + 'a';
	}
	return s1 - s2;
}

void movetonextchar(char **s) {
	if (directory) {
		do {
			(*s)++;
		} while (!isalnum(**s) && !isspace(**s) && (**s != '\0'));
	} else {
		(*s)++;
	}
}

int strocmp(char *s1, char *s2) {
	if (directory) {
		s1--; movetonextchar(&s1);
		s2--; movetonextchar(&s2);
	}
	int diff = charcmp(*s1, *s2);
	while (diff == 0 && *s1 != '\0') {
		movetonextchar(&s1);
		movetonextchar(&s2);
	}	
	return diff;
}

void changeoptions(char *options) {
	if (strcmp(options, "-") == 0) {
		numeric = 0;
		reverse = 0;
		foldcase = 0;
		directory = 0;
		return;
	}

	char c;
	while (c = *++options) {
		switch (c) {
		case 'n':
			numeric = 1;
			break;
		case 'r':
			reverse = 1;
			break;
		case 'f':
			foldcase = 1;
			break;
		case 'd':
			directory = 1;
			break;
		}
	}
}

char *fieldptr(char *s, int field) {
	char* ptr = s;
	int i;
	for (i = 1; i <= field; i++) {
		if (i != 1) {
			while (!isspace(*ptr)) {
				ptr++;
			}
		}
		while (isspace(*ptr)) {
			ptr++;
		}
	}
	return ptr;
}

int fieldcmp(char *s1, char *s2) {
	int result = 0;
	char **fargs = args + 2;
	int field = atoi(*fargs++);
	changeoptions("-");
	int i;
	char *s1ptr, *s2ptr;
	for (i = 1; i < argn - 2; i++, fargs++) {
		if (**fargs == '-') {
			changeoptions(*fargs);
		} else {
			s1ptr = fieldptr(s1, field);
			s2ptr = fieldptr(s2, field);
			result = numeric ? numcmp(s1ptr, s2ptr) : strocmp(s1ptr, s2ptr);
			if (reverse) {
				result *= -1;
			}
			if (result != 0) {
				return result;
			}
			field = atoi(*fargs);
			changeoptions("-");
		}
	}
	s1ptr = fieldptr(s1, field);
	s2ptr = fieldptr(s2, field);
	result = numeric ? numcmp(s1ptr, s2ptr) : strocmp(s1ptr, s2ptr);
	if (reverse) {
		result *= -1;
	}
	return result;
}
