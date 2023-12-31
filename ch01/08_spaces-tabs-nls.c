#include <stdio.h>

int main() {
	int c, ns, nt, nn;
	ns = 0; nt = 0; nn = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			++ns;
		}
		if (c == '\t') {
			++nt;
		}
		if (c == '\n') {
			++nn;
		}
	}

	printf("Spaces: %d\n", ns);
	printf("Tabs: %d\n", nt);
	printf("Newlines: %d\n", nn);
}	
