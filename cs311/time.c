#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){

	struct tm *gmt;
	struct tm *local;

	time_t t = time(NULL);

	gmt = gmtime(&t);
	local = localtime(&t);

	printf("time is: %ld", t);
	// check man localtime to struct time variables
	printf("secons:\t%d\n", local->tm_sec);


	return 0;
}