#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#define MAXBUF 50

void minprintf(char *, ...);

main(int argc, char *argv[]) {
	int a = 23;
	double d = 34.5;

	minprintf("%-5.4hi %10e %s hello %% %34.2 \n", a, d, argv[0]);
	return 0;
}

void minprintf(char *fmt, ...) {
	va_list ap;
	char *p, *p0, *sval;
	char buf[MAXBUF];
	int ival, len;
	double dval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		p0 = p++;
		if (*p == '-') {
			p++;
		}
		while (isdigit(*p)) {
			p++;
		}
		if (*p == '.') {
			p++;
		}
		while (isdigit(*p)) {
			p++;
		}
		if (*p == 'h' || *p == 'l') {
			p++;
		}
		len = p - p0 + 1;
		if (len >= MAXBUF) {
			len = MAXBUF - 1;
		}
		strncpy(buf, p0, len);
		buf[len] = '\0';

		switch (*p) {
		case 'd':
		case 'i':
		case 'x':
		case 'X':
		case 'u':
		case 'c':
			ival = va_arg(ap, int);
			printf(buf, ival);
			break;
		case 'f':
		case 'e':
		case 'E':
		case 'g':
		case 'G':
			dval = va_arg(ap, double);
			printf(buf, dval);
			break;
		case 's':
			sval = va_arg(ap, char *);
			printf(buf, sval);
			break;
		default:
			printf(buf);
			break;
		}
	}
	va_end(ap);
}
