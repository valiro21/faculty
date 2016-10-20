#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

struct dirlist {
	struct dirlist *next;
	char *path, *name;
	int type;
};

void findl (
	char *path,  //the full path of the entity from the root directory
	char *fname, //the name of the entity
	char *name) { //the name that we need to find

	int length = strlen (path);
	DIR *d = opendir (path); //open the directory
	if (d == NULL) {
		//if this is not a directory
		printf ("%s: %s\n", path, strerror(errno));
		return;
	}

	struct dirent *en;
	struct dirlist *start = NULL, *end = NULL;
	int count = 0;
	
	//get next item in the directory
	while ((en = readdir(d))) {
		count++;
		char *dirname = en->d_name;
		//skip . and ..
		if (strcmp (dirname, ".") == 0 || strcmp (dirname, "..") == 0)
			continue;
		
		//get the full path of the next item
		//allocalte space needed for the new path
		char *tpath = malloc(length + strlen (dirname) + 2);
		strcpy (tpath, path);
		if (tpath[length-1] != '/')
			strcat (tpath, "/");
		strcat (tpath, dirname);
		
		//add the new path to a pointer list
		if (start == NULL) {
			//out list is empty, create the first node
			start = (struct dirlist *)malloc (sizeof (struct dirlist));
			start->name = (char *)malloc(strlen (dirname) + 2);

			// set the name and path
			strcpy (start->name, dirname);
			start->type = en->d_type;
			start->path = tpath;
			end = start;
			start->next = NULL;
		}
		else {
			// out list is not empty, add a new node

			// allocate space for the new node
			end->next = (struct dirlist *)malloc (sizeof (struct dirlist));
			end = end->next;
	
			// set the name and path
			end->name = malloc(strlen (dirname) + 2);
			strcpy (end->name, dirname);
			end->type = en->d_type;
			end->path = tpath;
			end->next = NULL;
		}
	}
	closedir (d); //close the directory to not keep file descriptors

	// iterate through the list and use find recursively or compare with the name given
	struct dirlist *now = start, *prev;
	while (now != NULL) {
		if (now->type == DT_DIR) {
			// this is a directory
			findl (now->path, now->name, name);
		}
		else {
			//this is a file. compare with the given name
			if (strstr (now->name, name) != NULL)
				printf ("%s\n", now->path);
		}

		// remove node
		prev = now;
		now=now->next;
		free (prev->path); //deallocate space
		prev->path=NULL;
		free (prev->name); //deallocate space
		prev->name=NULL;
		free (prev); //deallocate space
		prev = NULL;
	}
}

void find (char *root, char *name) {
	findl (root, root, name);
}

int main (int argv, char *argc[]) {	
	if (argv != 3) {
		printf ("Invalid number of arguments. Expected 3 but got %d instead!\n", argv);
		return -1;
	}
	char *name = argc[1];
	char *root = argc[2];

	find (root, name);

	return 0;
}
