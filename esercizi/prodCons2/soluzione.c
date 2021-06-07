#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 100
//variabiabili condivise
int buffer[BUFFER_SIZE];
int freeSpots = BUFFER_SIZE;
int emptyEvenSpots = 50;
int emptyOddSpots = 33;
int emptyOddDivSpots = 17;
bool empty = true;
bool full = false;

//semafori
sem_t mutex;
sem_t evenMutex;
sem_t oddMutex;
sem_t oddDivMutex;
sem_t evenSpots;
sem_t oddSpots;
sem_t oddDivSpots;

//nomi semafori
static const char* mtx = "mutex";
static const char* evenMtx = "evenMutex";
static const char* oddMtx = "oddMutex";
static const char* oddDivMtx = "oddDivMutex";
static const char* semEven = "evenSpots";
static const char* semOdd = "oddSpots";
static const char* semOddDiv = "oddDivSpots";

void createSemaphores(){
	mutex = sem_open(mtx, O_CREAT, 0777, 1);
	evenMutex = sem_open(evenMtx, O_CREAT, 0777, 1);
	oddMutex = sem_open(oddMtx, O_CREAT, 0777, 1);
	oddDivMutex = sem_open(oddDivMtx, O_CREAT, 0777, 1);
	evenSpots = sem_open(semEven, O_CREAT, 0777, 50);
	oddSpots = sem_open(semOdd, O_CREAT, 0777, 33);
	oddDivSpots = sem_open(semOddDiv, O_CREAT, 0777, 17);
}

void destroySemaphores(){
	sem_unlink(mtx);
	sem_unlink(evenMtx);
	sem_unlink(oddMtx);
	sem_unlink(oddDivMtx);
	sem_unlink(semEven);
	sem_unlink(semOdd);
	sem_unlink(semOddDiv);
}

bool isEven(item){
	if((item % 2)== 0)
		return true;
	return false;
}

bool isMultiple(item){
	if((item % 3)== 0)
		return true;
	return false;
}

void producer(){
	int item = produce_item(); //non implementata
	int i = 0; //indice accesso pos pari
	int j = 1; //indice accesso pos dispari
	int k = 0; //indice accesso pos dispari multiple 3
	while(true){
		if(isEven(item)){
			sem_wait(semEven);
			sem_wait(evenMtx);
			buffer[i] = item;
			freeSpots--;
			emptyEvenSpots--;
			i+=2;
			sem_post(evenMtx);
		}
		else{
			if(isMultiple){
				sem_wait(semOddDiv);
				sem_wait(oddDivMtx);
				buffer[k] = item;
				freeSpots--;
				emptyOddDivSpots--;
				k+=3;
				sem_post(oddDivMtx);
			}
			else{
				sem_wait(semOdd);
				sem_wait(oddMtx);
				buffer[j] = item;
				freeSpots--;
				emptyOddSpots--;
				j+=2;
				sem_post(oddMtx);
			}
		}
		//resetting indeces
		if(i == 100)
			i = 0;
		if(j == 100)
			j = 100;
		if(k == 99)
			k = 0;
	}
}

void consumer(){
	int item;
	while(true){
		sem_wait(evenMtx);
		sem_wait(oddMtx);
		sem_wait(oddDivMtx);

		if(freeSpots == BUFFER_SIZE){
			//buffer is empty
			sem_post(evenMtx);
			sem_post(oddMtx);
			sem_post(oddDivMtx);
		}
		else{
			for(int i = 0; i < BUFFER_SIZE; i++){
				item = buffer[i];
				if(item(isEven))
					sem_post(semEven);
				else{
					if(isMultiple(item))
						sem_post(semOddDiv);
					else
						sem_post(semOddDiv);
				}
			}
		}
		sem_post(evenMtx);
		sem_post(oddMtx);
		sem_post(oddDivMtx);
	}
}

int main(int argc, char* argv[]){

}