#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int max);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould";

main() {
	char line[MAXLINE];
	int found = 0;

	while (getline(line, MAXLINE) > 0)
		if (strrindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	return found;
}
