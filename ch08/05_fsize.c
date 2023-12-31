#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void fsize(char *);
void dirwalk(char *, void (*func)(char *));

main(int argc, char **argv) {
	printf("  mode link  UID  GID  inodeno filesize  name\n");
	if (argc == 1) {
		fsize(".");
	} else {
		while (--argc > 0) {
			fsize(*++argv);
		}
	}
	return 0;
}

void fsize(char *name) {
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if (S_ISDIR(stbuf.st_mode)) {
		dirwalk(name, fsize);
	}
	printf("%6o %4hd %4hd %4hd %8ld %8ld  %s\n", 
			stbuf.st_mode, stbuf.st_nlink, stbuf.st_uid, stbuf.st_gid, stbuf.st_ino, stbuf.st_size, name);
}

#define MAX_PATH 1024

void dirwalk (char *dir, void (*func)(char *)) {
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0 ||
			strcmp(dp->d_name, "..") == 0) {
			continue;
		}
		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
			fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
		} else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*func)(name);
		}
	}
	closedir(dfd);
}
