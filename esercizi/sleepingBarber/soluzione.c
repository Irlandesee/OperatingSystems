#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 20 //numero massimo possibile di clienti in attesa
#define SEDIA_DISPONIBILE 1
#define SEDIA_NON_DISPONIBILE 0

//variabili condivise
int buffer[BUFFER_SIZE];
int numClientiWaiting = 0;
int numSedieDisponibili = BUFFER_SIZE;
bool barber_is_sleeping;

//semafori
sem_t *mutex; //semaforo per accesso a memoria condivisa
sem_t *barber_free;
sem_t *clients_in_shop;

//nomi dei semafori
static const char *mtx = "mutex";
static const char *clientsInShop = "clientsInShop";
static const char *barberFree = "barberFree";

void createSemaphores(){
	printf("--- Creating semaphores\n");
	mutex = sem_open(mtx, O_CREAT, 0777, 1);
	barber_free = sem_open(barberFree, O_CREAT, 0777, 0);
	clients_in_shop = sem_open(clientsInShop, O_CREAT, 0777, 20);
	printf("--- Done creating semaphores\n");
}

void destroySemaphores(){
	printf("--- Destroying semaphores\n");
	sem_unlink(mtx);
	sem_unlink(barberFree);
	sem_unlink(clientsInShop);
	printf("--- Done\n");
}

void printBuffer(){
	printf("Printing buffer\n");
	for(int i = 0; i < BUFFER_SIZE; i++)
		printf("%d : %d\n", i, buffer[i]);
	printf("---- Done\n");
}

void prepareBuffer(){
	printf("Preparing buffer\n");
	for(int i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = SEDIA_DISPONIBILE;
	printf("---- Done\n");
}

void tagliaCapelli(void *threadid, int cliente){
	long tid = (long) threadid;){
	printf("il thread %u si sta tagliando i capelli", tid);
	printf("ora libera il bosto");
}

/**
 * Apre il negozio e si mette a dormire, attendendo un cliente che lo svegli. 
 * quando ci sono clienti in attesa, il barbiere li chiama e li serve
 * uno alla volta
 * quando non ci sono clienti in attesa, il barbiere si rimette a dormire
 * */
void barber(){
	//apro il negozio
	sem_wait(mtx);
	barber_is_sleeping = true;
	sem_post(mtx);
	sem_post(barberFree);

	while(true){
		sem_wait(mtx);
		if(numClientiWaiting == 0){
			barber_is_sleeping = true;
			sem_post(barberFree);
			sem_post(mtx);
		}
		else{
			while(numClientiWaiting > 0){
				sem_wait(barberFree);
				sem_wait(clients_in_shop);
				barber_is_sleeping = false;
				numClientiWaiting--;
				int cliente = pop(buffer); //pop non implementata
				tagliaCapelli(pthread_self(), cliente);
				numSedieDisponibili++;
				sem_post(mtx);
				sem_post(clientsInShop);
				sem_post(barberFree);
			}
		}
	}
}

/**
 * entrando nel negozio, se non ci sono sedie libere cerca un altro barbiere
 * se c'è almeno una sedia libera ne occupa una, svegliando il barbiere se sta dormendo
 * e attende di essere chiamato
 * */
void client(){
	while(true){
		sem_wait(clientsInShop);
		sem_wait(mtx);
		if(barber_is_sleeping = true){
			barber_is_sleeping = false;
			insert(buffer); //insert non implementata
			sem_post(barberFree);
			sem_post(mtx);
		}
		else{
			sem_wait(barberFree);
			insert(buffer);
			sem_post(mutex);
		}
	}
}

int main(int argc, char *argv[]){

}