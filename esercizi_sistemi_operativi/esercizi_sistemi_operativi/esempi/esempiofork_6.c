#include<stdio.h>
main(  ){
    int p = getpid( ); 
    printf("sono %d, ora mi  clono\n",p);
    int x = fork( );     
    p = getpid( );
    
    for(long i = 0; i<5000000000; i++){
     
      /* perdo tempo */ 
      /* IN ALCUNE ESECUZIONI STAMPA PRIMA IL PADRE, IN ALTRE IL FIGLIO*/ 
    }
    if(x==0){   
        int f = getpid( );
        printf("sono il figlio, cioè %d\n",f);
    }
   
    else{        
        printf("sono %d, mio figlio è %d\n",getpid( ),x);
    }


}

