#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE

//variabili condivise
int A[BUFFER_SIZE];
int wait_R = 0; //numero lettori in waiting
int wait_i = 0; //numero scrittori in waiting su i
int wait_j = 0; //numero scrittori in waiting su j
int wait_k = 0; //numero scrittori in waiting su k

int run_R = 0;  //numero lettori working
bool run_i = false; //true se solo se ce un scrittore che lavora su i
bool run_j = false; //true se solo se ce un scrittore che lavora su j
bool run_k = false; //true se solo se ce un scrittore che lavora su k
int x = 0; //bonus lettori
int x_i = 0; //bonus scrittori su i
int x_j = 0; //bonus scrittori su j
int x_k = 0; //bonus scrittori su k

//semafori
sem_t *mutex; //mutua esclusione
sem_t *sem_R; //semafori lettori su A
sem_t *sem_i; //semaforo scrittori su i
sem_t *sem_j; //semaforo scrittori su j
sem_t *sem_k; //semaforo scrittori su k

//nomi semafori
static const char *mtx = "mutex";
static const char *semReader = "semReader";
static const char *semWriter_I = "semWriter_I";
static const char *semWriter_J = "semWriter_J";
static const char *semWriter_K = "semWriter_K";

void createSemaphores(){
	printf("Creating semaphores\n");
	mutex = sem_open(mtx, O_CREAT, 0777, 1);
	sem_i = sem_open(semWriter_I, O_CREAT, 0777, 0);
	sem_j = sem_open(semWriter_J, O_CREAT, 0777, 0);
	sem_k = sem_open(semWriter_K, O_CREAT, 0777, 0);
	sem_R = sem_open(semReader, O_CREAT, 0777, 0);
	printf("Done\n");
}

void destroySemaphores(){
	printf("Destroying semaphores");
	sem_unlink(mtx);
	sem_unlink(semWriter_I);
	sem_unlink(semWriter_J);
	sem_unlink(semWriter_K);
	sem_unlink(semReader);
	printf("Done\n");
}

void initBuffer(){
	printf("Initialising buffer\n");
	for(int i = 0; i < BUFFER_SIZE; i++)
		A[i] = 0;
	printf("done\n");
}

void writer(){
	int i = generateIndex(); 
	int v = generateValue();

	sem_wait(mtx);
	while(runR > 0 || run_i || run_j || run_k || 
		(wait_R > 0 && x_i= 0 && x_j == 0 && x_k == 0)){
		wait_i++;
		wait_j++;
		wait_k++;
		sem_post(mtx);
		sem_wait(semWriter_I);
		sem_wait(semWriter_J);
		sem_wait(semWriter_K);
		sem_post(mtx);
	}

	run_i = true;
	run_j = true;
	run_k = true;

	x = 10;
	if(wait_R > 0){
		x_i--;
		x_j--;
		x_k--;
	}

	sem_post(mtx);
	A[i] = v;

	sem_wait(mtx);
	run_i = false;
	run_j = false;
	run_k = false;

	if(x_i > 0 && x_j > 0 && x_k > 0 && wait_i > 0
		&& wait_j > 0 && wait_k > 0){
		wait_i--;
		wait_j--;
		wait_k--;
		sem_post(semWriter_I);
		sem_post(semWriter_J);
		sem_post(semWriter_K);
	}

	//se non ci sono thread in running su posizioni i,j,k
	if(!()){
		x_i = 4; x_j = 4; x_k = 4;
		while(wait_R > 0){
			wait_R--;
			sem_post(sem_R);
		}
	}
	sem_post(mtx);
}

void reader(){
	while(true){
		sem_wait(mtx);
		while( (run_i || run_j || run_k) || 
			((wait_i > 0 || wait_j > 0 || wait_k > 0) && x==0 )){
			wait_R++;
			sem_post(mtx);
			sem_wait(semReader);
			sem_wait(mtx);
		}
		run_R++;
		x_i = 4; x_j = 4; x_k = 4;
		if(wait_i > 0 || wait_j > 0 || wait_k > 0)
			x--;
		sem_post(mtx);

		int ris = A[0]+A[1]+A[2];

		sem_wait(mtx);
		run_R--;
		if(run_R == 0){
			x = 10;
			for(int i = 0; i < 3; i++){
				if(wait_i > 0){
					wait_i--;
					semPost(semWriter_I);
				}
				if(wait_j > 0){
					wait_j--;
					semPost(semWriter_J);
				}
				if(wait_k > 0){
					wait_k--;
					semPost(semWriter_K);
				}
			}
		}
		sem_post(mtx);
	}
}

int main(int argc, char *argv[]){

}