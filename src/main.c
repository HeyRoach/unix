#include <lab1.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static struct option long_options[] = {
	{"mode", required_argument, 0, 0},
	{"amount", required_argument, 0, 0},
	{"signal", required_argument, 0, 0},
	{"pid", required_argument, 0, 0},
};

int main(int argc, char *argv[], char **environ) {
	printf("current pid = %i\n", getpid());

	int opt = 0;
	int option_index = 0;

	char *mode = NULL;
	int amount = NULL;
	int signal = NULL;
	int pid = NULL;

	opt = getopt_long(argc, argv, "", long_options, &option_index);
	if(opt==-1){
		fprintf(stderr, "Error: no options\n");
		exit( EXIT_FAILURE );
	}

	while(opt!=-1){
		if (!strcmp(long_options[option_index].name, "mode")){
			mode  = optarg;
			printf("mode = %s\n", mode);
		}
		else if (!strcmp(long_options[option_index].name, "amount")){
			amount  = atoi(optarg);
  		  	printf("amount = %i\n", amount);
	  	}
		else if (!strcmp(long_options[option_index].name, "pid")){
			pid  = atoi(optarg);
  		  	printf("target pid = %i\n", pid);
	  	}
		else if (!strcmp(long_options[option_index].name, "signal")){
			signal = atoi(optarg);
  		  	printf("signal = %i\n", signal);
	  	}
		opt = getopt_long(argc, argv, "", long_options, &option_index);
	}

	if (!strcmp(mode, "std")){
		std();
	}
	else if (!strcmp(mode, "child")){
		child();
	}
	else if (!strcmp(mode, "pipe")){
		pipe_test();
	}
	else if (!strcmp(mode, "posix")){
		if(!amount){
			fprintf(stderr, "Error: invalid amount\n");
			exit( EXIT_FAILURE );
		}
		posix(amount);
	}
	else if (!strcmp(mode, "kill")){
		if(!signal || !pid){
			fprintf(stderr, "Error: invalid signal or pid\n");
			exit( EXIT_FAILURE );
		}
		kill(pid, signal);
	}else{
		fprintf(stderr, "Error: incorrect mode\n");
		exit( EXIT_FAILURE );
	}

	return EXIT_SUCCESS;
}
