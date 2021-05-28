#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <semaphore.h>

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
static const char *muntexRandomNumber = "mutexRandomNumber";
//declaring semaphores names
static const char *emptyEven = "emptyEven";
static const char *emptyOdd= "emptyOdd";
static const char *emptyMultiple = "emptyMultiple";

int nextInt(){
	srand(time(NULL));
	int x = rand() % MAX_RAND;
	printf("\nRandom number generated: %d\n", x);
	return x;
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

}

/**
 * Unlinks the semaphores.
 * Should always be called before the process terminates.
**/
void unlinkSemaphores(){

}
/**
 * 
 * */
void producer(){
	int item;
	int i = 0; //used for accessing even numbers;
	int j = 0; //used for accessing odd numbers;
	int k = 0; //used for accessing odd numbers that are divisible by 3
	
}

void consumer(){

}

void printBuffer(){
	printf("\n--------- Printing Buffer\n");
	for(int i = 0; i < BUFFER_SIZE; i++)
		printf("%d = %d\n", i, buffer[i]);
	printf("\n--------- Done\n");
}

int main(int argc, char* argv[]){
	
	return 0;
}