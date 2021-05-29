#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 100
#define MAX_RAND 100 //maximum random number generated
#define EMPTY_EVEN 50 //number of even spots free at the start
#define EMPTY_MULTIPLE 17 //number of odd spots that are divisible by 3 free at the start
#define EMPTY_ODD 33//number of odd spots free at the start

int buffer[BUFFER_SIZE];
int randomNumberGenerated; //random number generated 

//declaring mutexs
sem_t *mutex_even; //mutex for accessing even spots
sem_t *mutex_odd; //mutex for accessing odd spots
sem_t *mutex_multiple; //mutex for accesing odd spots that are divisible by 3
sem_t *mutex_randomNumber;
//declaring semaphores
sem_t *empty_even; //semaphore initialited at 50
sem_t *empty_odd; //semaphore initialited at 33
sem_t *empty_multiple; //semaphore initialited at 17

//declaring mutexs names
static const char *mutexEven = "mutexEven";
static const char *mutexOdd = "mutexOdd";
static const char *mutexMultiple = "mutexMultiple";
static const char *mutexRandomNumber = "mutexRandomNumber";
//declaring semaphores names
static const char *emptyEven = "emptyEven";
static const char *emptyOdd= "emptyOdd";
static const char *emptyMultiple = "emptyMultiple";

/**
 * Thread Safe (?)
 * */
void nextInt(){
	sem_wait(mutexRandomNumber);
	srand(time(NULL));
	int i = 0;
	while(i < BUFFER_SIZE){
		randomNumberGenerated = rand() % MAX_RAND;
		printf("Generated random number: %d\n", randomNumberGenerated);		
		i++;
	}
	sem_post(mutexRandomNumber);
}

bool isEven(int n){
	if((n % 2) == 0)
		return true;
	return false;
}

bool isMultiple(int n){
	if((n % 3) == 0)
		return true;
	return false;
}

/**
 * Initializes the semaphores.
 * Returns an error on sterr if it fails.
**/
void createSemaphores(){
	//creating mutexs
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

	mutex_multiple = sem_open(mutexMultiple, O_CREAT, 0777, 1);
	if(mutex_multiple == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating mutex: %s\n", mutexMultiple);
		exit(EXIT_FAILURE);
	}

	mutex_randomNumber = sem_open(mutexRandomNumber, O_CREAT, 0777, 1);
	if(mutex_randomNumber == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating mutex: %s\n", mutexRandomNumber);
		exit(EXIT_FAILURE);
	}

	//creating semaphores
	empty_even = sem_open(emptyEven, O_CREAT, 0777, EMPTY_EVEN);
	if(empty_even == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating semaphore: %s\n", emptyEven);
		exit(EXIT_FAILURE);
	}

	empty_odd = sem_open(emptyOdd, O_CREAT, 0777, EMPTY_ODD);
	if(empty_odd == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating semaphore: %s\n", emptyOdd);
		exit(EXIT_FAILURE);
	}

	empty_multiple = sem_open(emptyMultiple, O_CREAT, 0777, EMPTY_MULTIPLE);
	if(empty_multiple == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating semaphore: %s\n", emptyMultiple);
		exit(EXIT_FAILURE);
	}
}

/**
 * Unlinks the semaphores.
 * Should always be called before the process terminates.
**/
void unlinkSemaphores(){
	sem_unlink(mutexEven);
	sem_unlink(mutexOdd);
	sem_unlink(mutexMultiple);
	sem_unlink(mutexRandomNumber);
	sem_unlink(emptyEven);
	sem_unlink(emptyOdd);
	sem_unlink(emptyMultiple);
}
/**
 * 
 * */
/**
void producer(){
	int item;
	int i = 0; //used for accessing even numbers;
	int j = 0; //used for accessing odd numbers;
	int k = 0; //used for accessing odd numbers that are divisible by 3
	
}**/
/**
void consumer(){

}**/

void printBuffer(){
	printf("\n--------- Printing Buffer\n");
	for(int i = 0; i < BUFFER_SIZE; i++)
		printf("%d = %d\n", i, buffer[i]);
	printf("\n--------- Done\n");
}

int main(int argc, char* argv[]){
	unlinkSemaphores();
	createSemaphores();

	pthread_t randomNumberGeneratorThread;

	pthread_create(&randomNumberGeneratorThread, NULL, nextInt, NULL);

	pthread_join(randomNumberGeneratorThread, NULL);

	unlinkSemaphores();
	return 0;
}