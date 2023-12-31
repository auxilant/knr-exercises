#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define DEFAULTTAIL 10
#define MAXLINES 5000
#define MAXLEN 1000
#define BUFFERSIZE 10000
#define ERROR -1

int getline(char s[], int lim);

main(int argc, char *argv[]) {
	int tail;
	if (argc == 1) {
		tail = DEFAULTTAIL;
	} else
	if (argc == 2 && argv[1][0] == '-') {
		tail = -atoi(argv[1]);
	} else {
		printf("error: wrong arguments\n");
		return ERROR;
	}

	int linecount = 0;
	char *lineptr[MAXLINES];
	char **tailptr = lineptr;

	char linebuffer[BUFFERSIZE];
	char *freeptr = linebuffer;
	int len, tailsize, shift;
	char line[MAXLEN];

	int i;

	while ((len = getline(line, MAXLEN)) > 0) {
		line[len-1] = '\0';
		if (BUFFERSIZE - (freeptr - linebuffer) < len) {
			tailsize = freeptr - *(tailptr+1);
			shift = *(tailptr+1) - linebuffer;
			for (i = 0; i < tailsize; i++) {
				linebuffer[i] = linebuffer[i + shift];
			}
			freeptr -= shift;
		} 
		strcpy(freeptr, line);
		lineptr[linecount++] = freeptr;
		freeptr += len;
		if (freeptr - linebuffer > BUFFERSIZE) {
			printf("error: lines too large\n");
			return ERROR;
		}

		if (linecount > tail) {
			tailptr++;
		}
	}

	for (i = 0; i < tail; i++) {
		printf("%s\n", *tailptr++);
	}

	return 0;
}
