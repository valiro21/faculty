#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define FIFO_NAME "FIFO_FILE"

int main (int argv, char *argc[]) {
	char s[301];
	printf ("Waiting for a writer ... ");
	fflush (stdout);
	int fd = open (FIFO_NAME, O_RDONLY); // open fifo - this also waits for a writer
	printf ("We have a writer! Bytes will be printed below: v\n");
	fflush (stdout);
	int num;
	do {
		if ((num = read (fd, s, 300)) == -1) {
			perror (strerror (errno));
		}
		else {
			s[num]='\0';
			printf ("We got %d bytes: \"%s\"\n", num, s);
		}
	}while (num);
	return 0;
}

