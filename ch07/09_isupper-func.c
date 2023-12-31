#include <stdio.h>
#include <string.h>

int isupper(char);

main() {
	int i,j;
	char *str = "-13asdDFSD";
	int len = strlen(str);
	for (i = 0; i < 10000000; i++) {
		for (j = 0; j < len; j++) {
			isupper(str[j]);
		}
	}
}

int isupper(char c) {
	if (c >= 'A' && c <= 'Z') {
		return 1;
	}
	return 0;
}
