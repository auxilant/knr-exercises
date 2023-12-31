#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXSIZE 10000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], char *storageptr, char *storage, int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

main() {
	int nlines;
	char storage[MAXSIZE] = "";
	char *storageptr = storage;
	
	if ((nlines = readlines(lineptr, storageptr, storage, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000

int getline(char *, int);

int readlines(char *lineptr[], char *storageptr, char *storage, int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines) {
			return -1;
		} else {
			line[len-1] = '\0';
			lineptr[nlines++] = storageptr;
			strcat(storageptr, line);
			storageptr += len;
			if (storageptr - storage > MAXSIZE) {
				return -1;
			}
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0) {
		printf("%s\n", *lineptr++);
	}
}

void qsort(char *v[], int left, int right) {
	int i, last;
	void swap(char *v[], int i, int j);
	if (left >= right) {
		return;
	}
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++) {
		if (strcmp(v[i], v[left]) < 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

void swap(char *v[], int i, int j) {
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
