#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 100 //the buffer size
#define MAX_RAND 1000 //maximum random number that can be generated (0-99)
#define EMPTY_EVEN 50 //number of even spots free at the start
#define EMPTY_MULTIPLE 17 //number of odd spots that are divisible by 3 free at the start
#define EMPTY_ODD 33//number of odd spots free at the start

int buffer[BUFFER_SIZE];
int randomNumberGenerated; //random number generated 
srand(time(NULL)); 

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
 * Thread Safe 
 * 
 * */
void nextInt(){
	sem_wait(mutexRandomNumber);
	randomNumberGenerated = rand() % MAX_RAND;
	printf("Generated random number: %d\n", randomNumberGenerated);		
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
 * Should always be called before the process terminates, otherwise
 * there is the risk of them persisting in the systems
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
 * Produces an item. If it is even, it will access an even position in the array and insert it, 
 * otherwise if it is odd but divisibile by 3 it accesses an odd position divible by 3 and inserts it there.
 * Finally if the item is odd it accesses an odd position and inserts it.
 * */
void producer(){
	int item;
	int i = 0; //used for accessing even numbers;
	int j = 0; //used for accessing odd numbers;
	int k = 0; //used for accessing odd numbers that are divisible by 3
	printf("\nConsumer is starting...\n");
	while(true){
		nextInt();
		item = randomNumberGenerated; //generates a randomNumber
		if(isEven(item)){ //checking if item is even
			sem_wait(emptyEven);
			sem_wait(mutexEven);
			printf("Produced even item :%d, inserting at: %d\n", item, i);
			buffer[i] = item;
			printf("");
			i += 2;
			sem_post(mutex_even);
		}
		else{
			if(isMultiple(item)){ //checking if item is divisible by 3
				sem_wait(emptyMultiple);
				sem_wait(mutexMultiple);
				printf("Produced odd item divisible by 3: %d, inserting at: %d\n", item, k);
				buffer[k] = item;
				k += 3;
				sem_post(mutexMultiple);
			}
			else{
				sem_wait(emptyOdd);
				sem_wait(mutexOdd);
				printf("Produced odd item: %d, inserting at: %d\n", item, j);
				buffer[j] = item;
				j += 2;
				sem_post(mutexOdd);
			}
			//resetting indeces
			if(i == 100)
				i = 0;
			if(j == 100)
				j = 0;
			if(k == 99)
				k = 0;
		}
	}
}

void consumer(){
	int item;
	int i = 0; //used for accessing even numbers;
	int j = 0; //used for accessing odd numbers;
	int k = 0; //used for accessing odd numbers that are divisible by 3
	printf("\nConsumer is starting...\n");
	while(true){
		sem_wait(mutexEven);
		item = buffer[i];
		if(isEven(item)){
			printf("Consuming even item %d\n", item);
			i+=2;
			sem_post(emptyEven);
			sem_post(mutexEven);
		}
		else{
			sem_wait(mutexMultiple);
			item = buffer[k];
			if(isMultiple(item)){
				printf("Consuming odd item divisible by 3: %d\n", item);
				k += 3;
				sem_post(emptyMultiple);
				sem_post(mutexMultiple);
			}
			else{
				sem_wait(mutexOdd);
				item = buffer[j];
				printf("Consuming odd item: %d\n", item);
				j += 2;
				sem_post(emptyOdd);
				sem_post(mutexOdd);
			}
		}
		//resetting indeces
			if(i == 100)
				i = 0;
			if(j == 100)
				j = 0;
			if(k == 99)
				k = 0;
	}
}

/**
 * NOT THREAD SAFE
 * */
void printBuffer(){
	printf("\n--------- Printing Buffer\n");
	for(int i = 0; i < BUFFER_SIZE; i++)
		printf("%d = %d\n", i, buffer[i]);
	printf("\n--------- Done\n");
}

int main(int argc, char* argv[]){
	unlinkSemaphores();
	createSemaphores();
	/*
	pthread_t randomNumberGeneratorThread;

	pthread_create(&randomNumberGeneratorThread, NULL, nextInt, NULL);

	pthread_join(randomNumberGeneratorThread, NULL);
	*/

	pthread_t prod;
	pthread_t cons;
	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

	unlinkSemaphores();
	return 0;
}
