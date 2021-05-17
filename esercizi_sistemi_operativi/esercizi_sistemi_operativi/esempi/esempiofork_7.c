#include<stdio.h>


main(  ){
    int p = getpid( ); 
    printf("sono %d, ora mi  clono\n",p);
   
    int x = fork( );     
    p = getpid( );
    
    while(10==10){
    if(x==0){   
        int f = getpid( );
        printf("sono il figlio, cioè %d\n",f);
    }
   
    else{        
        printf("sono %d, mio figlio è %d\n",getpid( ),x);
    }
    }

}

