#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 10

void *print_hello_world(void *tid){
	printf("Hello world from %d0\n", tid);
	pthread_exit(NULL);
}

int main(int argc, const char *argv[]){

	pthread_t threads[NUMBER_OF_THREADS];
	int status, i;
	for(int i = 0; i < NUMBER_OF_THREADS; i++){
		printf("Main here, creating thread %d0\n", i),
		status = pthread_create(&threads[i], NULL, print_hello_world, (void *)i);
		if(status != 0){
			printf("Pthread returned errorr code %d0", status);
			exit(-1);
		}
	}
	exit(NULL);

}