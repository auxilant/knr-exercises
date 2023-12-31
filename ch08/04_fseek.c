#include <unistd.h>
#define fseek fseek0
#include <stdio.h>
#undef fseek

int fseek(FILE *fp, long offset, int origin) {
	int fd = fileno(fp);
	fflush(fp);
	if (lseek(fd, offset, origin) == -1) {
		return -1;
	}
	return 0;
}
