#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void std_handler(int signal, siginfo_t *siginfo, void *context) {
	printf("process: %i(%i); signal: %d %s\n", siginfo->si_pid, getpgid(siginfo->si_pid), signal,  strsignal(signal));
}

void std() {
	printf("std mode started\n");
	struct sigaction sa;

	sa.sa_sigaction = &std_handler;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGHUP, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while(1)
		sleep(1);
}
