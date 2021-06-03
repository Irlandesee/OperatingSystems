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

/**
 * Apre il negozio e si mette a dormire, attendendo un cliente che lo svegli
 * quando ci sono clienti in attesa, il barbiere li chiama e li serve
 * uno alla volta
 * quando non ci sono clienti in attesa, il barbiere si rimette a dormire
 * */
void barber(){

}

/**
 * entrando nel negozio, se non ci sono sedie libere cerca un altro barbiere
 * se c'è almeno una sedia libera ne occupa una, svegliando il barbiere se sta dormendo
 * e attende di essere chiamato
 * */
void client(){

}

int main(int argc, char *argv[]){

}