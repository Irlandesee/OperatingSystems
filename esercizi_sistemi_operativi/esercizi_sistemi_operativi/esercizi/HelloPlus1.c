#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int x;


void* printHelloWithAddition(){
	printf("Hello from %u\n", pthread_self());
	x++;
	printf("x is now: %d\n", x);
	pthread_exit(NULL);
}


int main(int argc, char* argv[]){

	x = 0;
	if(argc < 2){
		printf("Devi inserire numero thread da creare!");
		return -1;
	}
	int nThreads = atoi(argv[1]);
	pthread_t threads[nThreads];
	printf("Creating : %d threads.\n", nThreads);
	for(int i = 0; i < nThreads; i++){
		printf("Creating thread number: %d\n", i);
		pthread_create(&threads[i], NULL, printHelloWithAddition, NULL);

	}
	printf("\nDone\n");
	pthread_exit(NULL);
}