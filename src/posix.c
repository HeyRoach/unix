#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//	char *mas_sig[];

void posix_handler(int signal, siginfo_t *siginfo, void *context) {

	fprintf(stderr, " %i\t%i\t%i\t%i\t%i\n",
		siginfo->si_pid, getpid(), signal, siginfo->si_value.sival_int);


}

void posix(int amount) {

	printf("posix mode started\n");

	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &posix_handler;

	pid_t pid = fork();
	if(pid!=0) {

		int i;
		for (i = SIGRTMIN; i < SIGRTMAX; i++) {
			if(sigaction(i, &sa, NULL)==-1){
			perror("Error: ");
			exit( EXIT_FAILURE);
			}
		}

		while(1){
			sleep(1);
			if(signal_counter==amount)
				exit( EXIT_SUCCESS );
		}

	}else{
		union sigval value;
		int random_signo;
		time_t t;
		srand((unsigned) time(&t));
		printf("child table:\n #\tpid\tparent\tsigno\tvalue\n");

		sigset_t mask;
		if(sigfillset(&mask)==-1){
			perror("Error: ");
			exit(EXIT_FAILURE);
		}
		if(sigprocmask(SIG_BLOCK, &mask, NULL)==-1){
			perror("Error: ");
			exit(EXIT_FAILURE);
		}

		int k = 0;
		for (k = 0; k < amount; k++) {
			random_signo = rand()%(SIGRTMAX-SIGRTMIN) + SIGRTMIN;
			value.sival_int = rand()%100 + 1;

			if(sigqueue(getppid(), random_signo, value)==-1)
			{
				perror("Error: ");
 		 	    exit(EXIT_FAILURE);

			}

			printf(" %i\t%i\t%i\t%i\t%i\n",
				k, getpid(), getppid(), random_signo, value.sival_int);
		}
		sigprocmask(SIG_UNBLOCK, &mask, NULL);

		exit( EXIT_SUCCESS );
	}
}
