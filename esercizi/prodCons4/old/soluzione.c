#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 100

//variabili condivise
int buffer[BUFFER_SIZE];
int posLibere = BUFFER_SIZE;
int posOccupate = 0;
int consCount = 0;

//semafori
sem_t mutex;
sem_t prod;
sem_t cons;
sem_t specialCons;

//nomi semafori
static const char *mtx = "mutex";
static const char *producer = "producer";
static const char *consumer = "consumer";
static const char *specialConsumer = "specialConsumer";

void createSemaphores(){
	mutex = sem_open(mtx, O_CREAT, 0777, 1);
	prod = sem_open(producer, O_CREAT, 0777, 0);
	cons = sem_open(consumer, O_CREAT, 0777, 0);
	specialCons = sem_open(specialConsumer, O_CREAT, 0777, 0);
}

void destroySemaphores(){
	sem_unlink(mtx);
	sem_unlink(producer);
	sem_unlink(consumer);
	sem_unlink(specialConsumer);
}

void producer(){
	int item;
	int i = 0;
	while(true){
		sem_wait(mtx);
		if(posLibere == 0)
			sem_post(mtx);
		else{
			sem_wait(producer);
			buffer[i] = item;
			posLibere--;
			posOccupate++;
			i++;
			if(i == 100)
				i = 0;
			sem_post(mtx);
			sem_post(producer);
		}
	}
}

void consumer(){
	int item;
	int i = 0;
	while(true){
		sem_wait(mtx);
		if(posOccupate == 0)
			sem_post(mtx);
		else{
			sem_wait(consumer);
			item = buffer[i];
			posLibere++;
			posOccupate--;
			printf("%d\n", item);
			if(i == 100)
				i = 0;
			sem_post(mtx);
			sem_post(consumer);
		}
	}
}

void specialConsumer(){
	int item;
	int i = 0;
	while(true){
		sem_wait(mtx);
		if(posOccupate < 2)
			sem_post(mtx);
		else{
			sem_wait(specialConsumer);
			while(consCount < 5){
				consCount++;
				sem_post(mtx);
				sem_post(consumer);
			}
			int itemsConsumed = 0;
			while(itemsConsumed < 2){
				itemsConsumed++;
				item = buffer[i];
				printf("%d\n", item);
				i++;
				if(i == 100)
					i = 0;
			}
			posLibere+=2;
			posOccupate-=2;
			sem_post(mtx);
			sem_post(specialConsumer);
		}
	}
}

int main(int argc, char *arv[]){

}