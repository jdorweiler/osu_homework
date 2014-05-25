// see man fork -- creating a child process
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h> //fork
#include <sys/types.h>


int main(int argc, char **argv){

	pid_t p;
	pid_t child;
	int status;

	// spawn a child process
	switch((p = fork())){
							//fork(); // returns 0 success in the child, -1 error, returns pid to partent if successful, see man fork return value
		case 0:
			// child case
		printf("Child Process id is %d parent id: %d\n", getpid(), getppid());
		//execlp("ls","ls", (char*)NULL);
		sleep(10);
		break;

		case -1:
			// error case
			perror("could not create child process");
			exit(-1);

		default:
			// parent case
		printf("parten Process id is %d\n", getpid());
		child = wait(&status);
		printf("Waited on child %d\n", child);
			break;
	}

	// both child and parent continue here
	return 0;
}