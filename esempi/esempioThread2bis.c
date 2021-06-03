#include <pthread.h>  /* Piccola modifica: */
#include <stdio.h>/* il main stampa il valore della variabile x */
                  /* dopo un ciclo che consuma parecchio tempo */
               /* E' altamente probabile (ma non certo) che gli */
              /* altri thread abbiano gia' complatato il lavoro */
                  /* quando il main stampa il valore di x  */ 

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
   
   for(long i=0; i<5000000000; i++){}
   printf("x vale %d\n", x);
   pthread_exit(NULL);
}

