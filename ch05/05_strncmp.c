int strncmp(char *s, char *t, int n) {
	if (n == 0) {
		return 0;
	}
	int i;
	for (i = 0; (i < n-1) && (*s == *t); i++, s++, t++) {
		if (*s == '\0') {
			return 0;
		}
	}
	return *s - *t;
}
