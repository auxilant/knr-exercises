#include <stdio.h>

main() {
	int c;

	while ((c = getchar()) != EOF ) {
		if (c == '\t') {
			printf("\\t");
		} 
		if (c != '\t') {
			if (c == '\b') {
				printf("\\b");
			}
			if (c != '\b') {
				if (c == '\\') {
					printf("\\\\");
				}
				if (c != '\\') {
					putchar(c);
				}
			}
		}
	}
}
