#include <stdlib.h>
#include <stdio.h>
#include <semaphores.h>
#include <pthread.h>

#define BUFFER_SIZE 3

//variabili condivise
int wait_R = 0; //numero lettori in waiting 
int wait_i = 0; //numero scrittori in waitings
int run_R = 0; //numero lettori working
int run_i = 0; //numero scrittori working
int x = 0;
int x_i = 0;

int buffer[BUFFER_SIZE];

//semafori
sem_t *mutex; //semafori per la mutua esclusione
sem_t *sem_R: //semaforo lettori
sem_t *sem_i;  //semafori scrittori

//nomi semafori
static const char* mutex = "mutex";
static const char* semReader = "semReader";
static const char* semWriter = "semWriter";

void writer(){

}

void reader(){

}


int main(int argc, char* argv){

}