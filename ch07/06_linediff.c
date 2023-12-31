#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100

main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "%s: expected two filenames\n", argv[0]);
		exit(1);
	}

	FILE *fp1, *fp2;
	fp1 = fopen(argv[1], "r");
	if (fp1 == NULL) {
		fprintf(stderr, "%s: can't open %s\n", argv[0], argv[1]);
		exit(2);
	}
	fp2 = fopen(argv[2], "r");
	if (fp2 == NULL) {
		fprintf(stderr, "%s: can't open %s\n", argv[0], argv[2]);
		exit(2);
	}

	char line1[MAXLINE], line2[MAXLINE];
	char *ptr1, *ptr2;
	int linenumber = 0;
	do {
		if (linenumber == 0 || line1[strlen(line1)-1] == '\n') {
			linenumber++;
		}
		ptr1 = fgets(line1, MAXLINE, fp1);
		ptr2 = fgets(line2, MAXLINE, fp2);
	} while (ptr1 != NULL && ptr2 != NULL && strcmp(line1, line2) == 0);

	if (ptr1 == NULL && ptr2 == NULL) {
		printf("no differences found\n");
	} else {
		printf("line %d:\n", linenumber);
		if (ptr1) {
			printf("%s: %s\n", argv[1], line1);
		}
		if (ptr2) {
			printf("%s: %s\n", argv[2], line2);
		}
	}

	exit(0);
}
