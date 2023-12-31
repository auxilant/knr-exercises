char *strncat(char *s, char *t, int n) {
	char *orig_s = s;
	while (*s) {
		s++;
	};
	
	int i;
	for (i = 0; (i < n) && *t; ++i) {
		*s++ = *t++;
	}
	*s = '\0';

	return orig_s;
}
