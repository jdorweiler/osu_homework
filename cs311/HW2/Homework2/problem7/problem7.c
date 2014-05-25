/*
#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 2
# C program using getopt()
# helpful info/code from https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
# use: ./problem7 -htf
*/
#include <stdio.h>
#include <getopt.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	char c;
	struct utsname uname_pointer;
	time_t time_raw_format;
	struct stat s;

	while (( c = getopt(argc, argv, "htf:")) != 1){
		switch(c){
			case 'h':
				// print host name
				uname(&uname_pointer);
				printf("Hostname = %s \n", uname_pointer.nodename);
				break;

			case 't':
				// current time
				time(&time_raw_format);
				printf("The current local time: %s", ctime(&time_raw_format));
				break;
		
			case 'f':
				// print file size
				if(stat(optarg, &s) == 0){
					printf("Size of file '%s' is %d bytes\n", 
					optarg, (int) s.st_size);
				} else {
					printf("File '%s' not found\n", optarg);
				}
				break;
			}
		return;
	}	
	
	return 0;
}