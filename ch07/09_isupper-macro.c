#include <stdio.h>
#include <string.h>

#define isupper(c) (c > 'A' && c < 'Z') ? 1 : 0

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
