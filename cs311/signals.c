#define _POSIX_SOURCE
#define _BSD_SOURCE

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

extern void psignal(int sig, const char *msg); // print signals, similar to perror
extern const char *const sys_siglist[];

void intr_sig(int signal){
	psignal(signal, "caught it");
	printf("Caught signal %d %s\n", signal, sys_siglist[signal]);
}

int main(int argc, char **argv){

	struct sigaction s;
	struct sigaction t;

	s.sa_handler = intr_sig;
	sigemptyset(&s.sa_mask); // initalize set of masks, don't catch some signals

	s.sa_flags = 0;

	sigaction(SIGINT, &s, &t);

	int i;
	for(i = 0 ;; ++i){
		printf("i = %d\n", i);
		sleep(3);
	}

	return 0;
}