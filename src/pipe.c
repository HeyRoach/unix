#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void pipe_handler(int signal, siginfo_t *siginfo, void *context) {
	printf("siginfo:\n*signal: %s %i \n*uid: %i \n*pid: %i \n",
		"SIGPIPE", siginfo->si_signo, siginfo->si_uid, siginfo->si_pid);
	exit( EXIT_SUCCESS );
}

void pipe_test() {
	printf("pipe mode started\n");

	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &pipe_handler;

	int fd[2];
	pipe(fd);

	pid_t pid = fork();
	if (pid != 0) {
		sigaction(SIGPIPE, &sa, NULL);

		if(waitpid(pid)){
			close(fd[0]);
			write(fd[1], "test", 12);
			close(fd[1]);
		}

	} else {
		close(fd[0]);
		close(fd[1]);
		exit( EXIT_SUCCESS );
	}
}
