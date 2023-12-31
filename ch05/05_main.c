#include <stdio.h>

#define MAXSIZE 100

char *strncpy(char *s, char *t, int n);
char *strncat(char *s, char *t, int n);
int *strncmp(char *s, char *t, int n);

main() {
	char s1[MAXSIZE] = "hello, ";
	char s2[MAXSIZE] = "worlddddddd";
	char s3[MAXSIZE];

	printf("%s\n", strncat(s1, s2, 5));
	printf("%s\n", strncpy(s3, s2, 5));
	printf("%d\n", strncmp("abcd", "abce", 3));
	printf("%d\n", strncmp("abxd", "abce", 3));
	printf("%d\n", strncmp("abcd", "abxe", 3));
}
