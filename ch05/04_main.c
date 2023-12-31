#include <stdio.h>

#define MAXSIZE 100

int strend(char *s, char *t);

main() {
	char s1[MAXSIZE] = "hello, world";
	char s2[MAXSIZE] = "world";
	char s3[MAXSIZE] = "vorld";
	printf("%d = 1\n", strend(s1, s2));
	printf("%d = 0\n", strend(s2, s1));
	printf("%d = 1\n", strend(s1, s1));
	printf("%d = 0\n", strend(s1, s3));
}
