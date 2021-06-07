#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 100
//variabili condivise
int buffer[BUFFER_SIZE];
int freeSpots = BUFFER_SIZE;
int availableItems = 0;
int prod_waiting = 0;
int cons_waiting = 0;
int specCons_waiting = 0;
int priority = 0; //priorita dei consSpec sui cons

//semafori
sem_t mutex;
sem_t producer;
sem_t consumer;
sem_t specialConsumer;

//nomi semafori
static const char* mtx = "mutex";
static const char* prod = "producer";
static const char* cons = "consumer";
static const char* specCons = "specialConsumer";

void createSemaphores(){
	mutex = sem_open(mtx, O_CREAT, 0777, 1);
	producer = sem_open(prod, O_CREAT, 0777, 0);
	consumer = sem_open(cons, O_CREAT, 0777, 0);
	specialConsumer = sem_open(specCons, O_CREAT, 0777, 0);
}

void destroySemaphores(){
	sem_unlink(mtx);
	sem_unlink(prod);
	sem_unlink(cons);
	sem_unlik(specCons);
}

void producer(){
	int item = produce_item() //non implementata
	int i = 0;
	while(true){
		sem_wait(mtx);
		if(freeSpots < 0){
			prod_waiting++;
			sem_wait(prod);
			sem_post(mtx);
		}
		else{
			item = buffer[i];
			remove_item(i); //non implementata
			freeSpots--;
			availableItems++;
			sem_post(mtx);
			sem_post(cons);
			sem_post(specCons);
		}
		if(i == 100)
			i = 0;
	}
}

void consumer(){
	int item;
	int i = 0;
	while(true){
		sem_wait(mtx);
		if(availableItems < 0){
			cons_waiting++;
			sem_wait(cons);
			sem_post(mtx);
		}
		else{
			if(priority <= 5){		
				cons_waiting--;
				availableItems--;
				freeSpots++;
				item = buffer[i];
				remove_item(i); 
				i++;
				sem_post(mtx);
				sem_post(prod);
			}
			else{
				cons_waiting++;
				sem_wait(cons);
				sem_post(prod);
			}
		}
		if(i == 100)
			i = 0;
	}
}

void specialConsumer(){
	int item;
	int i = 0;
	while(true){
		sem_wait(mtx);
		if(availabeItems < 0){
			specCons_waiting++;
			priority++;
			sem_wait(specCons);
			sem_post(mtx);
		}
		else{
			int itemsConsumed = 0;
			specCons_waiting--;
			availableItems-=2;
			freeSpots+=2;
			while(itemsConsumed < 2){
				item = buffer[i];
				remove_item(i);
				i++;
				itemsConsumed++;
				sem_post(prod);
			}
		}
		if(i == 100)
			i = 0;
	}
}

int main(int argc, char* argv[]){

}