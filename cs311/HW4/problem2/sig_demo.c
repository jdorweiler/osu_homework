/*

header shit here

helpful code found on pg 401 TLPI
*/
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void sigHandler(int sig){
	if(sig == SIGINT){
		printf("SIGINT has been caught, terminating the program\n");
		exit(EXIT_SUCCESS);
	}
	if(sig == SIGUSR1){
		printf("SIGUSR1 has been caught\n");
	}
	if(sig == SIGUSR2){
		printf("SIGUSR2 has been caught \n");
	}
}

int main(int argc, char **argv){
	// sig handler for SIGINT
	if(signal(SIGINT, sigHandler) == SIG_ERR){
		exit(EXIT_FAILURE);
	}
	if(signal(SIGUSR1, sigHandler) == SIG_ERR){
		exit(EXIT_FAILURE);
	}
	if(signal(SIGUSR2, sigHandler) == SIG_ERR){
		exit(EXIT_FAILURE);
	}
	// send the signals
	// SIGUSR1
	kill(getpid(), SIGUSR1);

	// SIGUSR1
	kill(getpid(), SIGUSR2);

	// SIGUSR1
	kill(getpid(), SIGINT);

	return 0;
}