#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int signal_counter = 0;

typedef struct tag_name {
	int sig_pid;
    int curpid;
    int sig_no;
    int value;
}sig_income;
sig_income *signals_info;

void posix_handler(int signal, siginfo_t *siginfo, void *context) {

	//	fprintf(stderr, " %i\t%i\t%i\t%i\t%i\n",
	//		siginfo->si_pid, getpid(), signal, siginfo->si_value.sival_int);
		sig_income cursignal = { siginfo->si_pid,getpid(),signal,siginfo->si_value.sival_int};
		signals_info[signal_counter] = cursignal;
		signal_counter++;

}

void posix(int amount) {
	signals_info = (sig_income*)malloc(amount*sizeof(sig_income));

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
				if(signal_counter==amount){
					sleep(1);
					printf("parent table:\n #\tpid\tparent\tsigno\tvalue\n");
					for (i = 0; i < amount; i++) {
						fprintf(stderr, " %i\t%i\t%i\t%i\t%i\n", i, signals_info[i].sig_pid, signals_info[i].curpid, signals_info[i].sig_no, signals_info[i].value);
					}
					exit( EXIT_SUCCESS );
				}
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
