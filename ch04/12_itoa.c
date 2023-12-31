#include <string.h>

void itoa(int n, char s[]) {
	if (n == 0) {
		s[0] = '0';
		s[1] = '\0';
		return;
	}

	if (n / 10 == 0) {
		if (n < 0) {
			s[0] = '-';
			s[1] = '0' - n;
			s[2] = '\0';
		} else {
			s[0] = '0' + n;
			s[1] = '\0';
		}
	} else {
		itoa(n / 10, s);
		s[strlen(s)] = (n < 0) ? '0' - n % 10 : '0' + n % 10;
		s[strlen(s)+1] = '\0';
	}
}
