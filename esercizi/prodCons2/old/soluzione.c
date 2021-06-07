#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>


//variabili condivise
int attesaProd = 0;
int attesaCons = 0;
int attesaCons20 = 0;
int numPari = 0;

//semafori
sem_t *sem_cons;
sem_t *sem_prod;
sem_t *sem_cons20;
sem_t *sem_mutexPari;

//nomi semafori
static const char* semCons = "semCons";
static const char* semProd = "semProd";
static const char* semCons20 = "semCons20";
static const char* semMutexPari = "semMutexPari";

bool isEven(int item){
	if((item % 2) == 0)
		return true;
	return false;
}

void producer(){
	while(true){
		int item = produceItem();
		if(isEven(item)){
			sem_wait(mutexPari);
			if(numPari == 50){
				attesaProd++;
				sem_post(mutexPari);
				sem_wait(semProd);
				sem_wait(mutexPari);
			}
			buffer[i] = item;
			i = (i + 1) % 50;
			numPari++;
			if(attesaCons > 0){
				attesaCons--;
				sem_post(semCons);
			}
			if(numPari == 20 && attesaCons20 > 0){
				attesaCons20--;
				sem_post(semCons);
			}
			sem_post(mutexPari);
		}
		else{
			/**
			 * Item is odd
			 * */
		}
	}
}

void consumer(bool pari){
	if(pari){
		sem_wait(mutexPari);
		while(numPari == 0){
			attesaCons++;
			sem_post(mutexPari);
			sem_wait(semCons);
			sem_wait(mutexPari);
		}
		int item = buffer[j];
		j = (j + 1) % 50;
		numPari--;
		if(attesProd > 0){
			attesaProd--;
			sem_post(semProd);
		}
		sem_post(mutexPari);
	}
	else{
		/***
		* Item is odd
		*/
	}
}

void cons20(){
	while(mutexPari){
		while(numPari < 20){
			attesaCons++;
			sem_post(mutexPari);
			sem_wait(semCons20);
			sem_wait(mutexPari);
		}
		consumaTutto();
		j = 0; numPari = 0; int k = 0;
		while(attesaProd > 0 && k < 50){
			attesaProd--;
			sem_post(semProd);
			k++;
		}
		sem_post(mutexPari);
	}

}

void createSemaphores(){
	printf("******* Creating semaphores!\n");
	sem_mutexPari = sem_open(semMutexPari, O_CREAT, 0777, 1);
	sem_cons = sem_open(semCons, O_CREAT, 0777, 0);
	sem_cons20 = sem_open(semCons20, O_CREAT, 0777, 0);
	sem_prod = sem_open(semProd, O_CREAT, 0777, 0);
	printf("***** Done\n");
}

void destroySemaphores(){
	printf("******** Destroying semaphores!\n");
	sem_unlink(semMutexPari, NULL);
	sem_unlink(semCons, NULL);
	sem_unlink(semCons20, NULL);
	sem_unlink(semProd, NULL);
	printf("***** Done\n");
}

int main(int argc, char *argv[]){

}