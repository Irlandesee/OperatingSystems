#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

//variabili condivise
bool bridgeFree;
bool sensoMarcia; //true per south_to_north, false per north_to_south
int numVehiclesWaiting_North; //number of vehicles waiting to cross south
int numVehiclesWaiting_South; //number of vehicles waiting to cross north

//semafori
sem_t mutex;
sem_t sem_north;
sem_t sem_south;

//nomi semafori
static const char *mtx = "mutex";
static const char *semNorth = "semNorth";
static const char *semSouth = "semSouth";

void createSemaphores(){
	printf("Creating semaphores\n");
	mutex = sem_open(mtx, O_CREAT, 0777, 1);
	sem_north = sem_open(semNorth, O_CREAT, 0777, 0);
	sem_south = sem_open(semSouth, O_CREAT, 0777, 0);
	printf("---- Done\n");
}

void destroySemaphores(){
	printf("Destroying semaphores\n");
	sem_unlink(mtx);
	sem_unlink(semNorth);
	sem_unlink(semSouth);
	printf("---- Done\n");
}


void enteringNorth(){
	sem_wait(mtx);
	if(bridgeFree){
		bridgeFree = false;
		sensoMarcia = false;
		sem_post(mtx);
	}
	else{
		if(sensoMarcia == false && !(numVehiclesWaiting_South == 0))
			sem_post(mtx);
		else{
			numVehiclesWaiting_North++;
			sem_post(mtx);
			sem_wait(semSouth);
		}
	}
}

void enteringSouth(){
	sem_wait(mtx);
	if(bridgeFree){
		bridgeFree = false;
		sensoMarcia = true;
		sem_post(mtx);
	}
	else{
		if(sensoMarcia == true && !(numVehiclesWaiting_North == 0))
			sem_post(semNorth);
		else{
			numVehiclesWaiting_South++;
			sem_post(mtx);
			sem_wait(semNorth);
		}
	}
}

void exitingNorth(){
	sem_wait(mtx);
	if(numVehiclesWaiting_North > 0){
		sensoMarcia = false;
		numVehiclesWaiting_North--;
		sem_post(mtx);
		sem_post(semNorth);
	}
	else{
		if(numVehiclesWaiting_South > 0){
			sensoMarcia = true;
			numVehiclesWaiting_South--;
			sem_post(mtx);
			sem_post(semSouth);
		}
		else{
			bridgeFree = true;
			sem_post(mtx);
		}
	}
}

void exitingSouth(){
	sem_wait(mtx);
	if(numVehiclesWaiting_South > 0){
		sensoMarcia = true;
		numVehiclesWaiting_South--;
		sem_post(mtx);
		sem_post(semSouth);
	}
	else{
		if(numVehiclesWaiting_North > 0){
			sensoMarcia = false;
			numVehiclesWaiting_North--;
			sem_post(mtx);
			sem_post(semNorth);
		}
		else{
			bridgeFree = true;
			sem_post(mtx);
		}
	}
}

void crossing(void *threadId){

}

void goNorth(){
	enteringSouth();
	crossing();
	exitingNorth();
}

void goSouth(){
	enteringNorth();
	crossing();
	exitingSouth();
}

int main(int argc, char *argv[]){

}