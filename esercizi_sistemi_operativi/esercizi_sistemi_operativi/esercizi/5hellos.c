#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* printHelloFrom(){
	printf("Hello From: %u\n", pthread_self());
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){

	if(argc < 2){
		printf("Devi inserire numero thread da creare!");
		return -1;
	}
	int nThreads = atoi(argv[1]);
	pthread_t threads[nThreads];
	printf("creating: %d threads\n", nThreads);
	for(int i = 0; i < nThreads; i++){
		printf("Creating thread number: %d\n", i);
		pthread_create(&threads[i], NULL, printHelloFrom, NULL);

	}

	printf("\nDone\n");
	pthread_exit(NULL);
}