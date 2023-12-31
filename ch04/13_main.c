#include <stdio.h>

#define MAXSIZE 1000

int getline(char[], int);
void reverse(char[]);

main() {
	char line[MAXSIZE];

	getline(line, MAXSIZE);
	reverse(line);
	printf("%s\n", line);

	return 0;
}
