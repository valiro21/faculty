#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

void signalhandle (int signal) {
	printf ("Happy face!");
	return;
}

int main (int argv, char *argc[]) {
	if (signal (SIGUSR1, signalhandle) == SIG_ERR) {
		perror (strerror (errno));
		return errno;
	}

	pause ();

	return 0;
}
