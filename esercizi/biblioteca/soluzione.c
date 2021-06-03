#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>

#define NUMERO_COPIE 50
#define LIBRO_DISPONIBILE 1
#define LIBRO_NON_DISPONIBILE 0
#define NUM_MIN_PROCESSI_IN_WAITING 5
#define NUM_MAX_LIBRI_PRENOTABILI_P1 1
#define NUM_MAX_LIBRI_PRENOTABILI_P2 2
#define NUM_MAX_LIBRI_PRENOTABILI_P3 3

//variabili condivise
int buffer[NUMERO_COPIE];
int books_P1[NUM_MAX_LIBRI_PRENOTABILI_P1];
int books_P2[NUM_MAX_LIBRI_PRENOTABILI_P2];
int books_P3[NUM_MAX_LIBRI_PRENOTABILI_P3];
int libriDisponibili = NUMERO_COPIE;
int numProcessiInWaiting_P1 = 0;
int numProcessiInWaiting_P2 = 0;
int numProcessiInWaiting_P3 = 0;
bool empty = false;
bool full = true;

//semafori
sem_t *mutex; //per mutua esclusione
sem_t *sem_P1; //semaforo per processi p1
sem_t *sem_P2; //semaforo per processi p2
sem_t *sem_P3; //semaforo per processi p3

static const char *mtx = "mutex";
static const char *semP1 = "semP1";
static const char *semP2 = "semP2";
static const char *semP3 = "semP3";

void createSemaphores(){
	printf("creating semaphores...\n");
	mutex = sem_open(mutex, O_CREAT, 0777, 1);
	sem_P1 = sem_open(semP1, O_CREAT, 0777, 0);
	sem_P2 = sem_open(semP2, O_CREAT, 0777, 0);
	sem_P3 = sem_open(semP3, O_CREAT, 0777, 0);
	printf("***** Done.\n");
}

void destroySemaphores(){
	printf("Destroying semaphores.\n");
	sem_unlink(mutex);
	sem_unlink(semP1);
	sem_unlink(semP2);
	sem_unlink(semP3);
	printf("***** Done.\n");
}

void printfBuffer(){
	printf("------ Printing Buffer.\n");
	for(int i = 0; i < NUMERO_COPIE; i++)
		printf("%d : %d\n",i, buffer[i]);
	printf("\n-----Done\n");
}

void prepareBuffer(){
	printf("\nPreparing buffer\n");
	for(int i = 0; i < NUMERO_COPIE; i++){
		buffer[i] = LIBRO_DISPONIBILE;
		printf("%d : %d\n", i, LIBRO_DISPONIBILE);
	}
	printf("\nDone\n");
}

void leggi(void *threadid){
	long tid = (long) threadid;
	printf("Il thread %u sta leggendo\n", threadid);
	printf("ora restituisce il libro/i\n");
}

/**
 * prenotazione eseguita da processi tipo p1
 * se i libri disponibili sono >= 1 allora
 * prenota la copia
 * altrimenti va in wait
 * */
void prenota_P1(){
	sem_wait(mutex);
	int books[NUM_MAX_LIBRI_PRENOTABILI_P1];
	if(full || (libriDisponibili >= 1)){
		//scansiono buffer alla ricerca di un libro prenotabile
		for(int i = 0; i < NUMERO_COPIE; i++){
			int x = buffer[i];
			if(x == LIBRO_DISPONIBILE){
				buffer[i] = LIBRO_NON_DISPONIBILE;
				books[0] = i;
				break;
			}
		}
		libriDisponibili--;
		sem_post(mutex);
	}
	else{
		if(empty){
			numProcessiInWaiting_P1++;
			sem_post(mutex);
			sem_wait(semP1);	
		}
	}
}

/**
 * prenotazione eseguita da processi tipo p2
 * se i libri disponibili sono >= 2 allora
 * prenota le copie
 * altrimenti va in wait
 * */
void prenota_P2(){
	sem_wait(mutex);
	int books[NUM_MAX_LIBRI_PRENOTABILI_P2];
	if(full || (libriDisponibili >= 2)){
		//scansiono il buffer alla ricerca di 2 libri prenotabili
		for(int i = 0; i < NUM_MAX_LIBRI_PRENOTABILI_P2; i++){
			for(int j = 0; j < NUMERO_COPIE; j++){
				int x = buffer[j];
				if(x == LIBRO_DISPONIBILE){
					buffer[j] = LIBRO_NON_DISPONIBILE;
					books[i] = j;
					break;
				}
			}
		}
		libriDisponibili-=2;
		sem_post(mutex);
	}
	else{
		if(empty || (libriDisponibili < 2)){
			numProcessiInWaiting_P2++;
			sem_post(mutex);
			sem_wait(semP2);
		}
	}
}

/**
 * prenotazione eseguita da processi tipo p3
 * se i libria disponibili sono >= 3 allora
 * prenota le copie
 * altrimenti va in wait
 * */
void prenota_P3(){
	sem_wait(mutex);
	int books[NUM_MAX_LIBRI_PRENOTABILI_P3];
	if(full || (libriDisponibili >= 3)){
		//scansiono il buffer alla ricerca di 3 libri prenotabili
		for(int i = 0; i < NUM_MAX_LIBRI_PRENOTABILI_P3; i++){
			for(int j = 0; j < NUMERO_COPIE; j++){
				int x = buffer[j];
				if(x == LIBRO_DISPONIBILE){
					buffer[j] = LIBRO_NON_DISPONIBILE;
					books[i] = j;
					break;
				}
			}
		}
		libriDisponibili-=3;
		sem_post(mutex);
	}
	else{
		if(empty || (libriDisponibili < 3)){
			numProcessiInWaiting_P3++;
			sem_post(mutex);
			sem_wait(semP3);
		}
	}
}

/**
 * restituzione eseguita da processi tipo p1
 * restituiscono 1 copia
 * se ci sono >= num processi di tipo diverso da p1
 * rimetteno libri nel buffer, segnala la cessione dei libri
 * altrimenti li cede a un altro processo tipo p1, segnala altro p1
 * */
void restituisci_P1(){
	sem_wait(mutex);
	if(libriDisponibili == NUMERO_COPIE)
		empty = true;
	else{
		//controllo se ci sono processi diversi da p1 che sono in attesa
		if(numProcessiInWaiting_P2 >= NUM_MIN_PROCESSI_IN_WAITING
		 || numProcessiInWaiting_P3 >= NUM_MIN_PROCESSI_IN_WAITING){
			//rimetto libri nel buffer
			int index = books_P1[0];
			buffer[index] = LIBRO_DISPONIBILE;
			libriDisponibili++;
			sem_post(mutex);
			sem_post(semP2);
			sem_post(semP3);
		}
		else{
			int index = books_P1[0];
			buffer[index] = LIBRO_DISPONIBILE;
			libriDisponibili++;
			sem_post(semP1);
		}
	}

}

/**
 * restituzione eseguita da processi tipo p2
 * restituiscono 2 copie
 * se ci sono >= num processi di tipo diverso da p2
 * rimettono libri nel buffer, segnala la cessione dei libri
 * altrimenti li cedono ad un altro processo tipo p2, segnala altro p2
 * */
void restituisci_P2(){
	sem_wait(mutex);
	if(libriDisponibili == NUMERO_COPIE)
		empty = true;
	else{
		//controllo se ci sono processi diversi da p2 in attesa
		if(numProcessiInWaiting_P1 >= NUM_MIN_PROCESSI_IN_WAITING
			|| numProcessiInWaiting_P3 >= NUM_MIN_PROCESSI_IN_WAITING){
			//rimetto libri nel buffer
			for(int i = 0; i <= books_P2[i]; i++){
				if(i == books_P2[i])
					buffer[i] = LIBRO_DISPONIBILE;
			}
			libriDisponibili+=2;
			sem_post(mutex);
			sem_post(semP1);
			sem_post(semP3);
		}
		else{
			for(int i = 0; i <= books_P2[i]; i++){
				if(i == books_P2[i])
					buffer[i] = LIBRO_DISPONIBILE;
			}
			libriDisponibili+=2;
			sem_post(mutex);
			sem_post(sem_P2);
		}
	}
}

/**
 * restituzione eseguita da processi tipo p3
 * restituiscono 3 copie
 * se ci sono >= num processi di tipo diverso da p3
 * rimettono libri nel buffer, segnala la cessione dei libri
 * altrimenti li cedono ad un altro processo tipo p3, segnala altro p3
 * */
void restituisci_P3(){
	sem_wait(mutex);
	if(libriDisponibili == NUMERO_COPIE)
		empty = true;
	else{
		//controllo se ci sono processi diversi da p3 in attesa
		if(numProcessiInWaiting_P1 >= NUM_MIN_PROCESSI_IN_WAITING
			|| numProcessiInWaiting_P2 >= NUM_MIN_PROCESSI_IN_WAITING){
			//rimetto libri nel buffer
			for(int i = 0; i <= books_P3[i]; i++){
				if(i == books_P3[i])
					buffer[i] = LIBRO_DISPONIBILE;
			}
			libriDisponibili+=3;
			sem_post(mutex);
			sem_post(semP1);
			sem_post(semP2);
		}
		else{
			for(int i = 0; i <= books_P3[i]; i++){
				if(i == books_P3[i])
					buffer[i] = LIBRO_DISPONIBILE;
			}
			libriDisponibili+=3;
			sem_post(mutex);
			sem_post(sem_P3);
		}
	}
}

/**
 * Codice eseguito da processi di tipo p1
 * */
void processi_P1(){
	prenota_P1();
	leggi(pthread_self());
	restituisci_P1();
}

/**
 * Codice eseguito da processi di tipo p2
 * */
void processi_P2(){
	prenota_P2();
	leggi(pthread_self());
	restituisci_P2();
}

/**
 * Codice eseguito da processi di tipo p3
 * */
void processi_P3(){
	prenota_P3();
	leggi(pthread_self());
	restituisci_P3();
}

int main(int argc, char *argv[]){
	destroySemaphores();
	prepareBuffer()

	destroySemaphores();
	return 0;
}