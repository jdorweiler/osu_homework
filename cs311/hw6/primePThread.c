/*
#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 6

Build with: 
make

test with 
make validate
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
#include <pthread.h>
#include <semaphore.h>

// from http://www.tek-tips.com/faqs.cfm?fid=3999
 #define SetBit(A,k)     ( A[(k/32)] |= (1 << (k%32)) )
 #define ClearBit(A,k)   ( A[(k/32)] &= ~(1 << (k%32)) )            
 #define TestBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )

struct data{
	unsigned long twinLower;
	unsigned long twinUpper;
	unsigned long startPrime;
	int *prime_fd;
	int thread_id;
};

int quiet = 0;
int verbose = 0;
int test = 0;
void *addr;
unsigned long max_prime = UINT_MAX;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static sem_t sem;

/*
	run through the bitmap and check for twin primes
	mark non twin primes to zero
*/
void *twinSearch(void *arg){

	struct data *d = (struct data*)arg;
	unsigned long lowerBound = d->twinLower;
	unsigned long upperBound = d->twinUpper;
	int *primes = d->prime_fd;
	unsigned int i;

	if(lowerBound > 3){
			lowerBound -= 3;
		}
	for(i = lowerBound; i < upperBound+2; i++){
		if(!(TestBit(primes,i) && TestBit(primes, (i+2)))){
			ClearBit(primes, i);
		}
		else{
			i+=2;
		}
	}
	return NULL;
}

void *markNonPrimes(void *arg){
	struct data *d = (struct data*)arg;
	unsigned long start = d->startPrime;
	unsigned long j;
	int *primes = d->prime_fd;

	//printf("marking mutiples of %lu\n", start);
	pthread_mutex_lock(&mtx);
	for(j = start*start; j < max_prime-2; j += start){
	//printf("not prime: %u\n", j);
		if(TestBit(primes, j)){
			ClearBit(primes, j);
		}
	}
	pthread_mutex_unlock(&mtx);
	sem_post(&sem);
	return NULL;
}


int main(int argc, char **argv){

	unsigned char *bitmap;
	unsigned int bitmap_size;
	int *primes;
	unsigned long i;
	unsigned int twinUpper;
	unsigned int twinLower;
	unsigned int stepSize;
	int num_proc = 1;
	char option;

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

	bitmap_size = max_prime / 8 + 1;

	// get shared memory
	addr = malloc(bitmap_size*sizeof(int));
	//printf("addr %x", addr);

	bitmap = (unsigned char*)addr;
	primes = (int*)(bitmap + bitmap_size);

	sem_init(&sem, 0, 1);

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
		printf("Generating a list of primes\n");
	}

	struct data d[num_proc];
	pthread_t thread[num_proc];

	int threadNumber = 0;
	// start prime search
	for(i = 2; i < sqrtl(max_prime); i++){
		// found a non prime start thread 
		// at this point
		if(TestBit(primes, i)){
			sem_wait(&sem);
			//printf("found prime %lu\n",i);
			threadNumber = threadNumber%num_proc;
			d[threadNumber].startPrime = i;
			d[threadNumber].prime_fd = primes;
			if(0 != pthread_create(&thread[threadNumber],
								NULL,
								markNonPrimes,
								(void*)&d[threadNumber])){
				perror("cannot create thread");
				exit(EXIT_FAILURE);
			}
			threadNumber++;
		}
	}

		// wait for forked processes to finish
	for(i = 0; i < num_proc; i++){
		pthread_join(thread[i], NULL);
	}


	if(verbose){
		printf("Finding Twin primes\n");
	}

	twinLower = 1;
	stepSize = max_prime / num_proc;
	twinUpper = stepSize;

	// search the bitmap for twin primes using n processes
	for(i = 0; i < num_proc; i++){
		if(verbose){
			printf("creating process twin search threads\n");
		}
		d[i].twinLower = twinLower;
		d[i].twinUpper = twinUpper;
		d[i].thread_id = i;
		d[i].prime_fd = primes;

		if(0 != pthread_create(&thread[i],
								NULL,
								twinSearch,
								(void*)&d[i])){
			perror("cannot create thread");
			exit(EXIT_FAILURE);
		}
		twinLower = twinUpper;
		twinUpper += stepSize;
	}

	// wait for forked processes to finish
	for(i = 0; i < num_proc; i++){
		pthread_join(thread[i], NULL);
	}

	if(verbose){
		printf("Printing list of twin primes\n");
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

	sem_destroy(&sem);
	free(addr);

	return 0;
}