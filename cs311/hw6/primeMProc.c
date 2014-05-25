/*
#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 6

Run: ./primeTest.bash
*/
#define _BSD_SOURCE

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

// from http://www.tek-tips.com/faqs.cfm?fid=3999
 #define SetBit(A,k)     ( A[(k/32)] |= (1 << (k%32)) )
 #define ClearBit(A,k)   ( A[(k/32)] &= ~(1 << (k%32)) )            
 #define TestBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )

int quiet = 0;
int verbose = 0;
int test = 0;

/*
	Create a shared memory using object_size
*/
void *mount_shmem(char *path, int object_size){
	int shmem_fd;
	void *addr;

	shmem_fd = shm_open(path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	if(shmem_fd == -1){
		printf( "Failed to open shared memory object");
		exit(EXIT_FAILURE);
	}

	if(ftruncate(shmem_fd, object_size) == -1){
		printf( "failed to resize shared memory object");
	}

	addr = mmap(NULL, object_size, PROT_READ | PROT_WRITE, MAP_SHARED,
				shmem_fd, 0);

	if(addr == MAP_FAILED){
		printf( "Failed to map shared memory object");
		exit(EXIT_FAILURE);
	}

	return addr;
}

void forkProcess(
	unsigned int lowerBound, 
	unsigned int upperBound,
	unsigned int upperLimit,
	int *primes
	)
{

	int child_pid;

	//child process runs here
	if((child_pid = (fork())) == 0){
		unsigned int i;
		unsigned int j;
		// calculate primes and write to shared memory
		for(i = lowerBound; i < upperBound-10; i++){
			if(TestBit(primes, i)){
				for(j = i*i; j < upperLimit; j += i){
					ClearBit(primes, j);
				}
			}
			//printf("%u\n", j);
		}
		_exit(EXIT_SUCCESS);
	}
}

/*
	run through the bitmap and check for twin primes
	mark non twin primes to zero
*/
void forkTwinSearch(
	unsigned int lowerBound, 
	unsigned int upperBound,
	unsigned int upperLimit,
	int *primes
	)
{

	int child_pid;

	//child process runs here
	if((child_pid = (fork())) == 0){
		unsigned int i;
		if(lowerBound > 3){
			lowerBound -= 3;
		}
		for(i = lowerBound; i < upperBound+2; i++){
			//printf("checking %d\n",i);
			//printf("%ul\n",TestBit(primes,i));
			if(!(TestBit(primes,i) && TestBit(primes, (i+2)))){
				//printf("not twin: %d\n",i);
				ClearBit(primes, i);
			}
			else{
				i+=2;
			}
		}
		_exit(EXIT_SUCCESS);
	}
}


int main(int argc, char **argv){

	unsigned char *bitmap;
	unsigned int bitmap_size;
	int *primes;
	unsigned long i, j;
	unsigned int twinUpper;
	unsigned int twinLower;
	//unsigned int lowerBound;
	//unsigned int upperBound;
	unsigned int stepSize;
	int num_proc = 1;
	unsigned long max_prime = UINT_MAX;
	char option;
	unsigned long  object_size = 1024 * 1024 * 2000;

	while ((option = getopt(argc, argv, "qm:cvt")) != -1){
		switch(option){
			case 'q':
				// don't show list of primes to stdout
				quiet = 1;
				break;
			case 'm':
				// set maximum size of twin primes to check
				max_prime = atol(optarg);
				if(max_prime == UINT_MAX){
					max_prime -= 2;
				}
				else{
					max_prime += 2;
				}
				break;
			case 'c':
				// concurrency, default this to 1
				if(optarg)
					num_proc = atol(optarg);
				break;
			case 'v':
				// concurrency, default this to 1
				verbose = 1;
				break;
			case 't':
				// concurrency, default this to 1
				test = 1;
				break;
			}
	}

	bitmap_size = max_prime / 32 + 1;

	// get shared memory
	void *addr = mount_shmem("/jd", object_size);
	//printf("addr %x", addr);

	bitmap = (unsigned char*)addr;
	primes = (int*)(bitmap + bitmap_size);

	if(verbose){
		printf("Running with %d processes and max %lu\n", num_proc, max_prime);
		printf("Setting shared memory to 1\n");
	}

	// fill the shared memory with numbers 2-max_prime
	for(i = 0; i < max_prime; i++){
		SetBit(primes, i);
	}
	
	if(verbose){
		printf("Setting shared memory now set to 1\n");
	}

	for(i = 2; i < sqrtl(max_prime); i++){
		if(TestBit(primes, i)){
			for(j = i*i; j < max_prime; j += i){
				//printf("not prime: %u\n", j);
				ClearBit(primes, j);
			}
		}
	}

/*	somewhat failed attempt to calculate primes using 
	multiple processes.  This has some bug around 
	UINT_MAX, but works fine below that, come back to this later

	lowerBound= 2;
	stepSize = sqrtl(max_prime) / num_proc;
	upperBound = stepSize;

	// create n processes to generate a list of primes
	for(i = 0; i < num_proc; i++){
		if(verbose){
			printf("creating process, from %d to %d with step size %d\n",
					lowerBound, upperBound, stepSize);
		}
		forkProcess(lowerBound, upperBound, max_prime, primes);
		lowerBound = upperBound;
		upperBound += stepSize;
		if(upperBound < 0){
			upperBound = UINT_MAX;
		}
	}

	// wait for forked processes to finish
	for(i = 0; i < num_proc; i++){
		wait(NULL);
	}
*/

	if(verbose){
		printf("Finding Twin primes\n");
	}

	twinLower = 1;
	stepSize = max_prime / num_proc;
	twinUpper = stepSize;

	// search the bitmap for twin primes using n processes
	for(i = 0; i < num_proc; i++){
		if(verbose){
			printf("creating process twin search processes\n");
		}
		forkTwinSearch(twinLower, twinUpper, max_prime, primes);
		twinLower = twinUpper;
		twinUpper += stepSize;
	}

	// wait for forked processes to finish
	for(i = 0; i < num_proc; i++){
		wait(NULL);
	}

	int newLine = 0;
	if(quiet){
		if(test){
			for(i = 3; i < max_prime-3; i++){
					if(TestBit(primes, i)){
						printf("%lu\n", i);
						i+=2;
					}
			}
		}
		else {
			// print the first two pairs out manually
			// since they don't follow the pattern 
			// below. for printing in pairs only
			if(TestBit(primes, 3)){
				printf("%d ", 3);
				printf("%d\n", 5);
				printf("%d ", 5);
				printf("%d\n", 7);
			}
			for(i = 8; i < max_prime-3; i++){
				if(TestBit(primes, i)){
					printf("%lu ", i);
					newLine++;
					if(newLine > 1){
						printf("\n");
						newLine = 0;
					}

				}
			}
		}
	}

	munmap(addr, sizeof(int));
	shm_unlink("/jd");
	return 0;
}