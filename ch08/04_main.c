#define fseek fseek0
#include <stdio.h>
#undef fseek
#include "04_fseek.c"

int fseek(FILE *fp, long offset, int origin);

main(int argc, char *argv[]) {
	if (argc != 2) {
		return 1;
	}
	
	FILE *fp;
	fp = fopen(argv[1], "w");
	
	fprintf(fp, "world, hello ");
	fseek(fp, 0, 0);
	fprintf(fp, "hello");
	fseek(fp, 2, 1);
	fprintf(fp, "world");
	fseek(fp, 0, 2);
	fprintf(fp, "\n");

	fclose(fp);
	return 0;
}
