#include <stdio.h>

#define MAXLIMIT 1000

int getline(char *, int);

main() {
	char s[MAXLIMIT];
	int len = getline(s, MAXLIMIT);
	printf("%d %s\n", len, s);
}
