/*
#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 3
# seek through file
# use: ./homework3 -f illiad.txt -O -372 -o 4914 -l 372 -V -e 500
# compile with make file: make
*/
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>

#define BLOCKSIZE sizeof(char)

int main(int argc, char **argv){

	char buf[BLOCKSIZE];
	char option;
	char *fileName;

	int in_fd;
	int length;
	int verbose = 0;
	int offset = 0;
	int offset2 =0;
	int elen = 0;

	while (( option = getopt(argc, argv, "vVf:l:o:O:e:")) != -1){
		switch(option){
			case 'V':
				// verbose
				verbose = 1;
				break;
			case 'v':
				// verbose
				verbose = 1;
				break;
			case 'f':
				// name of the file
				fileName = optarg;
				break;
			case 'l':
				// length of bytes read
				if(atoi(optarg) < 1){
					printf("invalid lenght\n");
					exit(EXIT_FAILURE);
				}
				length = atoi(optarg)*2;
				break;
			case 'o':
				// offset 1
				if(atoi(optarg) < 0){
					printf("invalid offset\n");
					exit(EXIT_FAILURE);
				}
				offset = atoi(optarg);
				break;			
			case 'O':
				// offset 2
				offset2 = atoi(optarg);
				break;
			case 'e':
				// number of bytes from the end
				if(atoi(optarg) < 0){
					printf("positive elen values only\n");
					exit(EXIT_FAILURE);
				}
				elen = atoi(optarg);
				break;
			}
	}

	if(verbose){ printf("------ Opening file %s ------\n", fileName);}

	in_fd = open(fileName, O_RDONLY);
	if(in_fd == -1){
		perror("cant open input file");
		exit(EXIT_FAILURE);
	}

	if(verbose){ printf("<Offset1>--------------------------------------------------\n");}
	lseek(in_fd, offset, SEEK_SET);
	int i;
	for(i = 0; i < length; ++i){
		i += read(in_fd, buf, BLOCKSIZE);
		write(STDOUT_FILENO, buf, BLOCKSIZE);
	}
	printf("\n");
	
	lseek(in_fd, offset2, SEEK_CUR);
	if(verbose){ printf("<Offset2>--------------------------------------------------\n");}
	for(i = 0; i < length; ++i){
		i += read(in_fd, buf, BLOCKSIZE);
		write(STDOUT_FILENO, buf, BLOCKSIZE);
	}
	printf("\n");
	if(elen){
		if(verbose){ printf("<end bytes>------------------------------------------------\n");}
		lseek(in_fd, -elen, SEEK_END);
		for(i = 0; i < length; ++i){
			i += read(in_fd, buf, BLOCKSIZE);
			write(STDOUT_FILENO, buf, BLOCKSIZE);
		}
		printf("\n");
	}

	return 0;
}