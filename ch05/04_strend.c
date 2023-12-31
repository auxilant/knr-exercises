int strend(char *s, char *t) {
	char *se = s;
	char *te = t;
	while (*se) {
		se++;
	}
	while (*te) {
		te++;
	}
	if ((se - s) < (te - t)) {
		return 0;
	}
	for ( ; te >= t; te--, se--) {
		if (*te != *se) {
			return 0;
		}
	}
	return 1;
}
