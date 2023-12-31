#include <string.h>

/* strrindex: return rightmost index of t in s, -1 if none */
int strrindex(char s[], char t[]) {
	int i, j, k;

	for (i = strlen(s)-1; i >= 0; i--) {
		for (j = i, k = 0; t[k] != 0 && s[j] == t[k]; j++, k++) 
			;
		if (k > 0  && t[k] == '\0') {
			return i;
		}
	}

	return -1;
}
