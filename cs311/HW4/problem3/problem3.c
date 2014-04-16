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

void printTable();

int main(int argc, char **argv){

	char buf[BLOCKSIZE];
	char option;
	char *fileName;

	while (( option = getopt(argc, argv, "qxtvVdAw")) != -1){
		switch(option){
			case 'q':
				// quickly append

				break;
			case 'x':
				// extract named members

				break;
			case 't':
				// print out a table of contents
				printTable();

				break;
			case 'v':
				// verbose table
	
				break;
			case 'V':
				// verbose table

				break;			
			case 'd':
				// delete named files

				break;
			case 'A':
				// quickly append regular files

				break;
			case 'w':
				// add modified files

				break;
			default:
				printf(stderr, "That is not an option\n");
				exit(EXIT_FAILURE);
			}
	}

	return 0;
}

void printTable(){

}