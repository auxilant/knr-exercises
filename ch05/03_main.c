#include <stdio.h>

#define MAXSIZE 100

void strcat(char *s, char *t);

main() {
	char s1[MAXSIZE] = "hello, ";
	char s2[MAXSIZE] = "world";
	strcat(s1, s2);
	printf("%s\n", s1);
}
