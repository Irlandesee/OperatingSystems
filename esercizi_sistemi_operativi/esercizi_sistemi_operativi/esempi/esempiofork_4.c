#include<stdio.h>
main(  ){
    int p = getpid( ); 
    printf("sono %d, ora mi  clono\n",p);
    int x = fork( );     
    p = getpid( );
    
    for(int i = 0; i<500; i++){
    
    /* MOLTO PROBABILMENTE LE STAMPE DEL PADRE E DEL FIGLIO SI ALTERNANO  */


    int y = 10;  
    printf("y vale %d e io sono %d\n",y,p);  
    }

    if(x==0){   
        int f = getpid( );
        printf("sono il figlio, cioè %d\n",f);
    }
   
    else{        
        printf("sono %d, mio figlio è %d\n",getpid( ),x);
    }
}

