#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

#define NUMBER_OF_PARKING_SPOTS 30
#define SPOT_AVAILABLE 1
#define SPOT_NOT_AVAILABLE 0

//variabili condivise 
int buffer[NUMBER_OF_PARKING_SPOTS];
int bookParkingSpotA = 0;
int bookParkingSpotB = 0;
int totalParkingSpotsBooked = 0;
bool empty = true;
bool full  = true;

//semafori
sem_t *mutex;
sem_t *sem_A;
sem_t *sem_B;

//nomi dei semafori
static const char *mtx = "mutex";
static const char *semA = "semA";
static const char *semB = "semB";

void createSemaphores(){
	printf("Creating semaphores\n...");
	mutex = sem_open(mutex, O_CREAT, 0777, 1);
	semA = sem_open(semA, O_CREAT, 0777, 0);
	semB = sem_open(semB, O_CREAT, 0777, 0);
	printf("---- Done\n");
}

void destroySemaphores(){
	printf("Destroying semaphores\n");
	sem_unlink(mutex);
	sem_unlink(semA);
	sem_unlink(semB);
	printf("---- Done\n");
}

void enter_A(){
	sem_wait(semA);
	if(empty || totalParkingSpotsBooked < NUMBER_OF_PARKING_SPOTS){
		empty = false;
		totalParkingSpotsBooked++;
		sem_post(mutex);
	}
	else{
		if(full){
			bookParkingSpotA++;
			sem_post(mutex);
			sem_wait(semA);
		}
	}
}

void enter_B(){
	sem_wait(semB);
	if(empty || totalParkingSpotsBooked < NUMBER_OF_PARKING_SPOTS){
		empty = false;
		totalParkingSpotsBooked++;
		sem_post(mutex);
	}
	else{
		if(full){
			bookParkingSpotB++;
			sem_post(mutex);
			sem_wait(semB);
		}
	}
}

void parkCar(){

}

void exit(){
	sem_wait(mutex);
	if(totalParkingSpotsBooked == 0)
		empty = true;
	else{
		if(totalParkingSpotsBooked > 0 && totalParkingSpotsBooked < NUMBER_OF_PARKING_SPOTS){
			empty = false;
			full = false;
		}
		if(totalParkingSpotsBooked >= NUMBER_OF_PARKING_SPOTS-1)
			full = true;
		while(totalParkingSpotsBooked > 0){
			if(bookParkingSpotA > 0){
				bookParkingSpotA--;
				totalParkingSpotsBooked--;
				sem_post(mutex);
				sem_post(semA);
			}
			else{
				if(bookParkingSpotB > 0){
					bookParkingSpotB--;
					totalParkingSpotsBooked--;
					sem_post(mutex);
					sem_post(semB);
				}
			}
		}
		//non ci sono veicoli in attesa 
		sem_post(mutex);
	}
}

void park_entrance_A(){
	enter_A();
	parkCar();
	exit();
}

void park_entrance_B(){
	enter_B();
	parkCar();
	exit();
}

void prepareBuffer(){
	printf("\n---- Preparing buffer\n");
	for(int i = 0; i < NUMBER_OF_PARKING_SPOTS; i++)
		buffer[i] = 1;
	printf("\n---- Done");
}

void printBuffer(){
	printf("\nPrinting buffer\n");
	for(int i = 0; i < NUMBER_OF_PARKING_SPOTS; i++)
		printf("%d : %d\n", i, buffer[i]);
	printf("\n---- Done\n");
}

int main(int argc, char *argv[]){

}