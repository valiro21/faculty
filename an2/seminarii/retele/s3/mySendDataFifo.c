#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_NAME "FIFO_FILE"

int main (int argc, char *argv[]) {
	char s[301];
	mknod (FIFO_NAME, S_IFIFO | 0666, 0);

	printf ("Waiting for a reader ... ");
	fflush (stdout);
	int fd = open (FIFO_NAME, O_WRONLY); //open fifo file - this also waits for a reader
	printf ("We have a reader!\nPlease input something to write: v\n");
	fflush(stdout);

	int num;
	while(scanf("%s", s) != -1) {
		if ((num = write (fd , s, strlen (s))) < 0) {
			// print error string
			perror (strerror(errno));
		}
		else {
			printf ("We wrote %d bytes to fifo\n", num);
		}

	}

	return 0;
}
