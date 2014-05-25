#include <pthread.h>
#include <stdio.h>
#include <sys/times.h>
#include <mt.h>
#include <stdlib.h>
#include <unistd.h>

struct data
{
	unsigned long max;
	int thread_id;
};

void *print_down(void *arg){

	struct data *d = (struct data*)arg;
	unsigned long max = d->max;
	int thread_id = d->thread_id;

	for(long i = max; i >= 0; --i)
		printf("thread %d: %ld\n", thread_id, i)

	return NULL;
}

int main(int argc, char **argc){

	init genrand(47ul);

	struct data d[10];

	pthread_t thread[10];

	for (int i = 0; i < 10; ++i){
		d[i].max = genrand_int32() % 25;
		d[i].thread_id = i;

		if(0 == pthread_create(&thread[i],
								NULL,
								print_down,
								(void*)&d[i])){
			perror("cannot create thread");
			exit(EXIT_FAILURE);
		}
	}

	for(int i = 0; i < 10; ++i){
		pthread_join(thread[i]. NULL);
	}
	return 0;
}