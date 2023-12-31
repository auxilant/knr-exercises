#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#define MAXBUF 50

int minscanf(char *fmt, ...);

main(){
	int a, b;
	float f;
	minscanf("ssss %d %*d %% %f", &a, &f);
	printf("%d %f\n", a, f);
	return 0;
}

int minscanf(char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	int items = 0;
	int suppress;

	int *iptr;
	unsigned int *uiptr;
	float *fptr;
	char *cptr;

	int len;
	char c;
	char buf[MAXBUF];
	char *p, *p0;
	for (p = fmt; *p; p++) {
		if (*p == ' ' || *p == '\t') {
			continue;
		}

		if (*p == '%') {
			p0 = p++;
			if (*p == '%') {
				while (isspace(c = getchar()))
					;
				if (*p != c) {
					return items;
				} else {
					continue;
				}
			}

			if (*p == '*') {
				suppress = 1;
				p++;
			} else {
				suppress = 0;
			}
			while (isdigit(*p)) {
				p++;
			}
			if (*p == 'h' || *p == 'l' || *p == 'L') {
				p++;
			}
			len = p - p0 + 1;
			if (len >= MAXBUF) {
				len = MAXBUF - 1;
			}
			strncpy(buf, p0, len);
			buf[len] = '\0';
			
			if (suppress) {
				scanf(buf);
				continue;
			}
			switch(*p) {
			case 'd':
			case 'i':
			case 'o':
			case 'x':
				iptr = va_arg(ap, int *);
				scanf(buf, iptr);
				items++;
				break;
			case 'u':
				uiptr = va_arg(ap, unsigned int *);
				scanf(buf, uiptr);
				items++;
				break;
			case 'e':
			case 'f':
			case 'g':
				fptr = va_arg(ap, float *);
				scanf(buf, fptr);
				items++;
				break;
			case 'c':
			case 's':
				cptr = va_arg(ap, char *);
				scanf(buf, cptr);
				items++;
				break;
			default:
				return items;
			}
		} else {
			do {
				if (*p != getchar()) {
					return items;
				}
			} while (!isspace(*(p+1)) && *(p+1) == '%');
		}
	}

	return items;
}
