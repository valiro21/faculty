#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

struct list {
	char *name;
	struct list *next;
};

struct list_header {
	struct list *start;
	struct list *end;
	struct list_header *next;
	int size;
	int pid;
	int pipe[2];
};

struct list_header* newListHeader () {
	struct list_header *l = (struct list_header *) malloc (sizeof (struct list_header));
	l->start = l->end = NULL;
	l->next = NULL;
	l->size = l->pid = l->pipe[0] = l->pipe[1] = 0;
	return l;
}

struct list* newList () {
	struct list *l = (struct list *) malloc (sizeof (struct list));
	l->name = NULL;
	l->next = NULL;
	return l;
}

struct llist {
	struct list_header *start;
	struct list_header *end;
};

struct llist* newLlist () {
	struct llist *l = (struct llist *)malloc (sizeof (struct llist));
	l->start = l->end;
	return l;
}

void merge_list (struct list_header *l1, struct list_header *l2) {
	int p[2] = l2->pipe;
	int rd = p[0], wt = p[1];
	close (wt);
	while (x = readNumber (rd) != -1) {
		for (int i = 0; i < x; i++) {
			ch = getCharArray (rd);
			l1.add (ch);
		}
	}
	close (rt);
}

void add_name (struct list_header *ch, char *name) {
	if (ch == NULL) return;
	
	struct list *e = newList();
	e->name = (char *)malloc (strlen (name) + 1);
	strcpy (e->name, name);
	e->next = NULL;
	
	if (ch->end == NULL) {
		//printf ("NULL\n");
		ch->start = ch->end = e;
	}
	else {
		ch->end->next = e;
		ch->end = e;
	}
}

void add (struct llist *ch, struct list_header *l) {
	if (ch == NULL) return;
	
	if (ch->end == NULL) {
		ch->start = l;
		ch->end = l;
	}
	else {
		ch->end->next = l;
		ch->end = l;
	}
}

void print (struct list_header *l) {
	struct list *now = l->start;
	printf ("%s %d\n", now->name, now->next);
	
	while (now != NULL) {
		printf ("%s ", now->name);
		now = now->next;
	}
	printf ("\n");
}

void printll (struct llist *l) {
	struct list_header *now = l->start;
	//printf ("%s %d\n", now->name, now->next);

	while (now != NULL) {
		print(now);
		now = now->next;
	}
	printf ("\n");
}

void findl (char *path, char *name, struct list_header *l) {
	struct stat buf;
	stat (path, &buf);
	if (!S_ISDIR(buf.st_mode)) {
		printf ("%d\n", l);
		l->next = NULL;
		add_name (l, path);
		return;
	}

	int length = strlen (path);

	DIR *d = opendir (path);
	if (d == NULL) {
		printf ("%s: Directory not found", path);
		return;
	}

	struct dirent *en;
	
	struct llist *li = newLlist();
	while ((en = readdir(d))) {
		char *dirname = en->d_name;
		if (strcmp (dirname, ".") == 0 || strcmp (dirname, "..") == 0)
			continue;

		char *tpath = malloc(length + strlen (dirname) + 2);
		strcpy (tpath, path);
		strcat (tpath, "/");
		strcat (tpath, dirname);
			
		int pid;
		struct list_header *tmp = newListHeader();
		if ((pid = fork()) == -1) {
			printf ("Failed fork!\n");
			return;
		}

		//printf ("%d %s\n", tmp.pid, tpath);
		int p[2];
		pipe (p);
		list_header * tmp = newListHeader ();
		if (pid == 0) {
			// child
			findl (tpath, name, p[0]);
			exit(0);
		}
		else {
			// parent 
			add (l, tmp);
		}
		return;
	}

	struct list_int *now = li->start;
	while (now != NULL) {
		int status, opt = 0;
		waitpid (now->pid, &status, opt);
		merge_list (l, now);
		now = now->next;
	}
	free (li);
	//print (l);
}

void find (char *root, char *name) {
	struct list_header *l = newListHeader ();
	findl (root, name, l);
	print (l);
}

int main (int argv, char *argc[]) {	
	char *name = argc[1];
	char *root = argc[2];

	find (root, name);

	return 0;
}
