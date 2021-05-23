#include <pthread.h> /* Esempio con stampa di PID e TID */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int x;
void *PrintHello(void *threadid){ 
   pid_t pid = getpid();
   pthread_t tid = pthread_self( ); /*chiamata POSIX per chiedere il TID*/
   printf("Ciao, pid = %d, tid = %d \n", pid, tid);
   pthread_exit(NULL);
}
int main(  ){
   pthread_t th[5];
   long t;
   pid_t pid = getpid();
   pthread_t tid = pthread_self();
   printf("Buongiorno, sono pid = %d, tid = %d \n", pid, tid);
   for(t=0;t<5;t++){  
          printf("Creo la thread numero %ld\n", t);  
          pthread_create(&th[t], NULL, PrintHello, (void *)t);  
          printf("Il suo tid e' %d\n",th[t]);
    }
}
