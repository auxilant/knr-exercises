char *strncpy(char *s, char *t, int n) {
	int i;
	int pad_zeros = 0;
	for (i = 0; i < n; ++i) {
		*s++ = pad_zeros ? '\0' : *t++;
		if (*t == '\0') {
			pad_zeros = 1;
		}
	}
	return s - n;
}
