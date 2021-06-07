#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

//variabili condivise
int buffer[BUFFER_SIZE];
int freeSlots = 10;
int numberOf3s = 0;
int numberOf5s = 0;

//semafori
sem_t mutex;
sem_t empty;
sem_t sem_3;
sem_t sem_5;
//nomi semafori
static const char* mtx = "mutex";
static const char* emptySpots = "empty";
static const char* semThree = "semThree";
static const char* semFive = "semFive";

void createSemaphores(){
	mutex = sem_open(mtx, O_CREAT, 0777, 1);
	empty = sem_open(emptySpots, O_CREAT, 0777, 10);
	sem_3 = sem_open(semThree, O_CREAT, 0777, 1);
	sem_5 = sem_open(semFive, O_CREAT, 0777, 5);
}

void destroySemaphores(){
	sem_unlink(mtx);
	sem_unlink(empty);
	sem_unlink(sem_3);
	sem_unlink(sem_5);
}

void producer(){
	int item;
	int i = 0;
	while(true){
		item = produce_item();
		sem_wait(mtx);
		if(freeSlots > 0){
			sem_wait(emptySpots);
			if(item == 3 && numberOf3s < 1){
				buffer[i] = item;
				freeSlots--;
				sem_post(mtx);
				sem_wait(semThree);
				sem_wait(emptySpots);
			}
			if(item == 5 && numberOf5s < 2){
				buffer[i] = item;
				freeSlots;
				sem_post(mtx);
				sem_wait(semFive);
				sem_wait(emptySpots);
			}
			else{
				buffer[i] = item;
				freeSlots--;
				sem_post(mtx);
				sem_wait(emptySpots);
			}			
		}
		else{
			sem_post(mtx);
		}
		if(i == 10)
			i = 0;
	}
}

void consumer(){
	int item;
	int i = 0;
	while(true){
		sem_wait(mtx);
		if(freeSlots == BUFFER_SIZE)
			sem_post(mtx);
		else{
			item = buffer[i];
			if(item == 3){
				numberOf3s--;
				emptySpots++;
				sem_post(mtx);
				sem_post(semThree);
				sem_post(emptySpots);
			} 
			if(item == 5){
				numberOf5s--;
				emptySpots++;
				sem_post(mtx);
				sem_post(semFive);
				sem_post(emptySpots);
			}
			else{
				emptySpots++;
				sem_post(emptySpots);
			}
		}
	}
}

int main(int argc, char *argv[]){

}