#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main (int argv, char *argc[]) {
	int out = open ("B.TXT", O_CREAT | O_EXCL);
	if (errno) {
		out = open ("B.TXT", O_RDWR);
	}
	write (out, "A", 1);
	lseek (out, 0, SEEK_SET);
	write (out, "B", 1);
	close (out);
	return 0;
}
