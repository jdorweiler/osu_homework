#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMTHREADS 8
#define VECLEN 100000

double sum;

struct data{
	double *a;
	double *b;
	int veclen;
	int offset;
};

pthread_t threads[NUMTHREADS];
pthread_mutex_t mutex_sum;

void *dotprod(void *arg){
	int start;
	int end;
	int length;
	double *x;
	double *y;
	double sub_sum;

	struct data *d = (struct data*)arg;
	length = d->veclen;
	start = d->offset * length;
	end = start + length;
	x = d->a;
	y = d->b;

	sub_sum = 0.0;

	for(int i = start; i < end; i++)
		sum += x[i] * y[i];
	
	pthread_mutex_lock(&mutex_sum);
	sum += sub_sum;
	printf("Thread %d did %d to %d: sub sum = %f, global sum = %f\n",
		d->offset, start, end, sub_sum, sum);
	pthread_mutex_unlock(&mutex_sum);
	pthread_exit((void*)0);

}
int main(int argc, char **argv){

	double *a = (double*)malloc(NUMTHREADS * VECLEN * sizeof(double));
	double *b = (double*)malloc(NUMTHREADS * VECLEN * sizeof(double));

	struct data d[NUMTHREADS];

	pthread_attr_t attr;

	for(int i = 0; i < VECLEN * NUMTHREADS; ++i){
		a[i] = 1.0;
		b[i] = 1.0;
	}

	sum = 0.0;

	pthread_mutex_init(&mutex_sum, NULL);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(int i = 0; i < NUMTHREADS; i++){
		d[i].a = a;
		d[i].b = b;
		d[i].offset = i;
		d[i].veclen = VECLEN;
		pthread_create(&threads[i], &attr, dotprod, (void*)&d[i]);
	}

	pthread_attr_destroy(&attr);

	for(int i = 0; i < NUMTHREADS; i++){
		pthread_join(threads[i], NULL);
	}

	printf("sum = %f\n", sum);

	free(a);
	free(b);
	pthread_mutex_destroy(&mutex_sum);

	return 0;
}