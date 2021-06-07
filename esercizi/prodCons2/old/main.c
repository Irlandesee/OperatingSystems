#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 100
#define EMPTY_EVEN 50
#define EMPTY_ODD 50
#define EVEN_FLAG 20
//#define RAND_MAX 1000

//variabili condivise
int buffer[BUFFER_SIZE];
int randomNumberGenerated;


//semaphori
sem_t *empty_even;
sem_t *empty_odd;
sem_t *mutex_even;
sem_t *mutex_odd;
sem_t *mutex_flag;
sem_t *mutex_randomNumber;

//nomi semafori
static const char* emptyEven = "emptyEven";
static const char* emptyOdd = "emptyOdd";
static const char* mutexEven = "mutexEven";
static const char* mutexOdd = "mutexOdd";
static const char* mutexFlag = "mutexFlag";
static const char* mutexRandom = "mutexRandom";

void nextInt(){
	sem_wait(mutexRandom);
	randomNumberGenerated = rand() % 1000;
	printf("Generated random number: %d\n", randomNumberGenerated);
	sem_post(mutexRandom);
}

bool isEven(int n){
	if((n % 2) == 0)
		return true;
	return false;
}

void createSemaphores(){
	mutex_even = sem_open(mutexEven, O_CREAT, 0777, 1);
	if(mutex_even == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating mutex: %s\n", mutexEven);
		exit(EXIT_FAILURE);
	}
	mutex_odd = sem_open(mutexOdd, O_CREAT, 0777, 1);
	if(mutex_odd == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating mutex: %s\n", mutexOdd);
		exit(EXIT_FAILURE);
	}
	mutex_flag = sem_open(mutexFlag, O_CREAT, 0777, 0);
	if(mutex_flag == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating mutex: %s\n", mutexFlag);
		exit(EXIT_FAILURE);
	}
	empty_even = sem_open(emptyEven, O_CREAT, 0777, 50);
	if(empty_even == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating semaphore %s\n", emptyEven);
		exit(EXIT_FAILURE);
	}
	empty_odd = sem_open(emptyOdd, O_CREAT, 0777, 50);
	if(empty_odd == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating semaphore %s\n", emptyOdd);
		exit(EXIT_FAILURE);
	}
	mutex_randomNumber = sem_open(mutexRandom, O_CREAT, 0777, 1);
	if(mutex_randomNumber == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating mutex: %s\n", mutexRandom);
		exit(EXIT_FAILURE);
	}
	printf("******* Done Creating Semaphores ********\n");
}

void destroySemaphores(){
	sem_unlink(mutexEven);
	sem_unlink(mutexOdd);
	sem_unlink(mutexFlag);
	sem_unlink(emptyEven);
	sem_unlink(emptyOdd);
	sem_unlink(mutexRandom);
	printf("Semaphores destroied\n");
}

void consEven(){
	int item;
	int k = 0;
	while(true){
		sem_wait(mutexFlag);
		printf("Printing 20 even numbers\n");
		while(k < 20){
			item = buffer[k];
			printf("%d\n", item);
			k++;
		}
		printf("Done printing!\n");
		sem_post(mutexFlag);
	}
}

void consumer(){
	int item;
	int i = 0;
	int j = BUFFER_SIZE / 2;
	while(true){
		printf("printing even elements\n");
		sem_wait(mutexEven);
		while(i < 50){
			sem_wait(emptyEven);
			item = buffer[i];
			printf("%d\n", item);
			i++;
			sem_post(emptyEven);
		}
		sem_post(mutexEven);
		printf("printing odd elements\n");
		sem_wait(mutexOdd);
		while(j < 100){
			sem_wait(emptyOdd);
			item = buffer[j];
			printf("%d\n", item);
			j++;
			sem_post(emptyOdd);
		}
		sem_post(mutexOdd);
		printf("Resetting indeces\n");
		if(i == 50)
			i = 0;
		if(j == 100)
			j = BUFFER_SIZE / 2;
	}

}

void producer(){
	int item;
	int i = 0;
	int j = BUFFER_SIZE / 2;
	while(true){
		//accessing random number value
		sem_wait(mutexRandom);
		item = randomNumberGenerated;
		sem_post(mutexRandom);
		if(isEven(item)){
			sem_wait(mutexEven);
			sem_wait(emptyEven);
			buffer[i] = item;
			i++;
			if(i == EVEN_FLAG){
				printf("Signaling the even consumer!\n");
				sem_post(mutexFlag);
			}
			sem_post(mutexEven);
		}
		else{
			sem_wait(mutexOdd);
			sem_wait(emptyOdd);
			buffer[j] = item;
			j++;
			sem_post(mutex_odd);
		}
		if(i == (BUFFER_SIZE/2))
			i = 0;
		if(j == BUFFER_SIZE)
			j = BUFFER_SIZE / 2;
	}
}

int main(int argc, char* argv[]){
	srand(time(NULL));
	destroySemaphores();
	createSemaphores();

	pthread_t cons20;
	pthread_t cons;
	pthread_t prod;

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);
	pthread_create(&cons20, NULL, consEven, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
	pthread_join(cons20, NULL);

	destroySemaphores();
	return 0;
}