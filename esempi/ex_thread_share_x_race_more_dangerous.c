
/* esempio di thread che possono dar luogo ad una race condition */

#include <pthread.h> /* Esempio 2: variabile condivisa da 3 thread */
#include <stdio.h>
#include <stdlib.h>    
long x = 100; /* x variabile globale variabile condivisa */  

void * f1(void *threadid){
   for(int i=0; i<100000; i++){x=x+5;} /* modifica di x */
   pthread_exit(NULL);
}

void * f2(void *threadid){
   for(int i=0; i<100000; i++){x = x+10;} /* modifica di x */
   pthread_exit(NULL);
}

int main( ){ /* x è nel read_set */
 pthread_t t1, t2;  
 pthread_create(&t1, NULL, f1, (void *)t1);/*x è nel write_set*/
 pthread_create(&t2, NULL, f2, (void *)t2);/*x è nel write_set*/ 
 pthread_join(t1,NULL);/*attendo che termini il primo thread*/
 pthread_join(t2,NULL);/*attendo che termini il secondo thread*/
   printf("x vale %ld\n",x); /* lettura di x */
}

