#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void child_handler(int signal, siginfo_t *siginfo, void *context) {
	printf("siginfo:\n*signal: %s %i \n*uid: %i \n*pid: %i \n*status: %i \n*code: %i\n",
		"SIGCHLD", siginfo->si_signo, siginfo->si_uid, siginfo->si_pid, siginfo->si_status, siginfo->si_code);
	exit( EXIT_SUCCESS );
}

void child() {
	printf("child mode started\n");

	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &child_handler;

	pid_t pid = fork();
	if (pid != 0){
		printf("parent: PID=%d, GID=%d\n", getpid(), getpgid(getpid()));
		printf("child:  PID=%d, GID=%d\n", pid, getpgid(pid));
		sigaction(SIGCHLD, &sa, NULL);
		while(1){
			sleep(1);
		}
	}else{
		time_t t;
		srand((unsigned) time(&t));
		int time_sleep = rand() % 6 + 1;
		printf("sleep: %is\n", time_sleep);
		sleep(time_sleep);
		exit( EXIT_SUCCESS );
	}

}
