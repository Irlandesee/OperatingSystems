#include<stdio.h>
main(  ){    
    int s;
    int p = getpid( );
    printf("sono %d, ora mi clono\n",p); 
    int x = fork( );

    if(x==0){
     printf("sono %d\n" , getpid( ));               
     int z = 7/x; // divisione per zero!. Errore a runtime.
     }
    else{
      int  w = wait(&s); /* il padre aspetta la terminazione del                              figlio */
      printf("sono %d, mio figlio %d ha terminato\n",getpid( ),x);
      printf("il suo stato e' %d \n"  , s);
    }
}
