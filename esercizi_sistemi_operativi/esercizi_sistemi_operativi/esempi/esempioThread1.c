#include <pthread.h>  /* Esempio di thread in POSIX */
#include <stdio.h>       
#include <stdlib.h>      

void *PrintHello(void *threadid){     /* "programma" per i thread */
   long tid = (long)threadid;
   printf("Ciao, sono la thread numero #%ld!\n", tid);
   pthread_exit(NULL); 
}


int main(  ){
   pthread_t th[5];   
   long t;
   for(t=0; t<5; t++){  /* creo 5 thread, ognuno esegue PrintHello*/
      printf("Creo la thread numero %ld\n", t);
      /**
      * &th[t] -> Memory address ove memorizzare il thread creato
      *NULL -> Attributi: null forza l'uso degli attributi di default
      *PrintHello -> Funzione tipo *void -> *void che deve essere eseguita dal thread creato
      *(void *)t -> parametro void da passare alla funzione.
      **/
      pthread_create(&th[t], NULL, PrintHello, (void *)t); 
   
   }
   pthread_exit(NULL); 
}

