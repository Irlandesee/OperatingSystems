#include <pthread.h>  /* Piccola modifica: definiamo una variabile x  */
#include <stdio.h>       /* che viene condivisa tra i vari thread */  
#include <stdlib.h>    
int x;  /* il main e tutti i thread condividono x */

void *PrintHello(void *threadid){
   long tid = (long)threadid;
   printf("Ciao, sono la thread numero #%ld!\n", tid);
   printf("x vale %d\n", x);
   x=x+1;
   pthread_exit(NULL);
}

int main( ){
   pthread_t th[5];  
   long t;
   x=10;
   for(t=0; t<5; t++){
      printf("Creo la thread numero %ld\n", t);
      pthread_create(&th[t], NULL, PrintHello, (void *)t);
   }
   pthread_exit(NULL);
}

