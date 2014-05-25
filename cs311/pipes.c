#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h> //fork pipe
#include <sys/types.h>

int main(int argc, char **argv){

	int fds[2]; // file descriptors
	char buf[100];
	char *s = "hello";
	int num_read;
	
	if(pipe(fds) == -1){
		perror("Error creating pipes");
	}
	// pipe ends need to be open or close
	// depending on which way you want
	// data to flow. see close(fds[#])
	// statements below
	switch (fork()){

		case 0:
			// child case
		// close write end of pipe in chile
			close(fds[1]);
			num_read = read(fds[0], buf, 100);
			buf[num_read] = '\0';
			printf("fub = %s\n", buf);
			break;

		case -1:

			// error case

		default:
			// parent 
			// close read end of pipe in parent
			close(fds[0]);
			write(fds[1], s, 5);
	}

	return 0;
}