#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define THREAD_COUNT 5
#define RAND_MAX 100
#define DIRECTION_NORTH TRUE
#define DIRECTION_SOUTH FALSE
#define BOOL_NUMBERS 2

sem_t *mutex;
sem_t *toNorth;
sem_t *toSouth;
sem_t *genVehicles;

int vehicleCount = 10;
bool bridgeFree = true;
int bookToNorth = 0;
int bookToSouth = 0;
bool direction = true; // -> toNorth, false toSouth

static const char *semMutex = "mutex";
static const char *semToNorth = "toNorth";
static const char *semToSouth = "toSouth";
static const char *semGenVehicles = "genVehicles";

pthread_t randomVehicleGeneration;
pthread_t vehiclesGoingNorth;
pthread_t vehiclesGoingSouth;

/**
* NOT THREAD SAFE!
* */
int generateRandomInteger(){
	srand(time(NULL));
	return rand() % RAND_MAX;
}

/**
 * NOT THREAD SAFE!
 * */
int generateRandomDirection(){
	srand(time(NULL));
	int n = rand() % BOOL_NUMBERS;
	printf("Random direction generated: %d\n");
	return n;
}

/**
 * THREAD SAFE (?)
 * */
void generateVehicle(){
	int n = generateRandomDirection();
	sem_wait(&genVehicles); //acquiring lock on variables
	if(n == 0){	//0 is true
		printf("\ngenerating vehicle coming from the north!\n");
		bookToSouth++;
	}
	else{
		if(n == 1){
			printf("\ngenerating vehicle coming from the south!\n");
			bookToNorth++;
		}
		printf("\nfailed generating vehicles!\n");
	}
	sem_post(&genVehicles);
}

/**
void printCrossing(bool direction){
	if(direction)
		printf("crossing to north");
	printf("crossing to south");
}
**/
/**
void enteringNorth(){

}

void enteringSouth(){

}

void exitingSouth(){

}

void exitingNorth(){

}

void goingToNorth(){
	enteringSouth();
	printCrossing(TRUE);
	exitingNorth();
}

void goingToSouth(){
	enteringNorth();
	printCrossing(FALSE);
	exitingSouth();
}
**/
//sem_open(semname1, O_CREAT, 0777, 0);
void createSemaphores(){
	//creating semaphores
	
	mutex = sem_open(semMutex, O_CREAT, 0777, 1);
	if(mutex == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating semaphore mutex");
		return -1;
	}
	toNorth = sem_open(semToNorth, O_CREAT, 0777, 0);
	if(toNorth == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating semaphore toNorth");
		return -1;
	}
	toSouth = sem_open(semToSouth, O_CREAT, 0777, 0);
	if(toSouth == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating semaphore toSouth");
		return -1;
	}
	genVehicles = sem_open(semGenVehicles, O_CREAT, 0777, 1);
	if(genVehicles == SEM_FAILED){
		fprintf(stderr, "%s\n", "ERROR creating semaphore genVehicles");
		return -1;
	}
}

void destroySemaphores(){
	//unlinking old semaphores
	sem_unlink(mutex);
	sem_unlink(toNorth);
	sem_unlink(toSouth);
	sem_unlink(semGenVehicles);
}

void createThreads(){
	//creating thread for random vehicle generation
	pthread_create(&randomVehicleGeneration, NULL, generateVehicle, NULL);
	//creating thread for vehicels going south to north
	pthread_create(&vehiclesGoingNorth, NULL, goingToNorth, NULL);
	//creating thread for vehicles going north to south
	pthread_create(&vehiclesGoingSouth, NULL, goingToSouth, NULL);
}

/**
 * WARNING: this function destroys all threads!!!
 * */
void destroyThreads(){
	pthread_join(&randomVehicleGeneration, NULL);
	puts("\nStopped random vehicle generation thread\n");
	pthread_join(&vehiclesGoingNorth, NULL);
	puts("\nStopped thread for vehicles going south to north\n");
	pthread_join(&vehiclesGoingSouth, NULL);
	puts("\nStopped thread for vehicles going south to north\n");
}

int main(int argc, char* argv[]){

	pthread_t randomIntegerThread;

	//destroying semaphores
	destroySemaphores();

	//pthread_create(&randomIntegerThread, NULL, generateVehicle, NULL);
	//printf("sleeping for 5 seconds\n");
	
	
	printf("vehicles going north: %u\n", bookToNorth);
	printf("vehicles going south: %u\n", bookToSouth);

	//pthread_join(&randomIntegerThread, NULL);
	printf("\nStopped random vehicle generation thread!\n");
	//destroying semaphores
	destroySemaphores();

	return 0;
}