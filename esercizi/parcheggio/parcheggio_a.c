#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

#define POSTI_DISPONIBILI 30
#define POSTO_DISPONIBILE 1
#define POSTO_NON_DISPONIBILE 0

//variabili condivise
int buffer[POSTI_DISPONIBILI];
int numeroPostiDisponibili = POSTI_DISPONIBILI;
int prenotaIngresso_A = 0;
int prenotaIngresso_B = 0;
bool turn

//semafori
sem_t *mutex;
sem_t *sem_A;
sem_t *sem_B;

//nomi dei semafori
static const char *mtx = "mutex";
static const char *semA = "semA";
static const char *semB = "semB";

void createSemaphores(){
	mutex = sem_open(mtx, O_CREAT, 0777, 1);
	sem_A = sem_open(semA, O_CREAT, 0777, 15);
	sem_B = sem_open(semB, O_CREAT, 0777, 15);
}

void destroySemaphores(){
	sem_unlink(mtx);
	sem_unlink(semA);
	sem_unlink(semB);
}

void entrance_A(){
	sem_wait(mtx);
	if(numeroPostiDisponibili > 0){
		sem_wait(semA);
		numeroPostiDisponibili--;
		sem_post(mtx);
	}
	else{
		//prenoto un ingresso
		prenotaIngresso_A++;
		sem_post(mtx);
	}
}

void entrance_B(){
	sem_wait(mtx);
	if(numeroPostiDisponibili > 0){
		sem_wait(semB);
		numeroPostiDisponibili--;
		sem_post(mtx);
	}
	else{
		//prenoto un ingresso
		prenotaIngresso_B++;
		sem_post(mtx);
	}
}

void exit(){
	sem_wait(mtx);
	if(numeroPostiDisponibili == 0){
		if(turn){
			turn = false;
			prenotaIngresso_A--;
			numeroPostiDisponibili++;
			sem_post(semA);
		}
		else{
			if(!(turn)){
				turn = true;
				prenotaIngresso_B--;
				numeroPostiDisponibili++;
				sem_post(semB);
			}
		}
		sem_post(mtx);
	}
}

void park(void *threadID){

}

void park_A(){
	entrance_A();
	park();
	exit();
}

void park_B(){
	entrance_B();
	park();
	exit();
}

int main(int argc, char *argv[]){

}