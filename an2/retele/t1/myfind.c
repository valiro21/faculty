#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


void findl (char *path, char *fname, char *name) {
	struct stat buf;
	stat (path, &buf);
	if (!S_ISDIR(buf.st_mode)) {
		if (strcmp (name, fname) == 0)
			printf ("%s\n", path);
		return;
	}

	int length = strlen (path);
	DIR *d = opendir (path);
	if (d == NULL) {
		printf ("%s: Directory not found\n", path);
		return;
	}

	struct dirent *en;
	while ((en = readdir(d))) {
		char *dirname = en->d_name;
		if (strcmp (dirname, ".") == 0 || strcmp (dirname, "..") == 0)
			continue;

		char *tpath = malloc(length + strlen (dirname) + 2);
		strcpy (tpath, path);
		strcat (tpath, "/");
		strcat (tpath, dirname);

		findl (tpath, dirname, name);
		free (tpath);
	}
}

void find (char *root, char *name) {
	findl (root, root, name);
}

int main (int argv, char *argc[]) {	
	char *name = argc[1];
	char *root = argc[2];

	find (root, name);

	return 0;
}
