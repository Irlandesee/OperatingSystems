#include<stdio.h>

main(  ){
    int p = getpid( ); 
    printf("sono %d, ora mi  clono\n",p);
    int x = fork( );     
    p = getpid( );
    
    int y = 10;  
    printf("y vale %d e io sono %d\n",y,p);  
   
    if(x==0){   
        int f = getpid( );
        printf("sono il figlio, cioè %d\n",f);
        y=y+4;/* IL FIGLIO STAMPA 14  */ 
        printf("y vale %d e io sono %d\n",y,p);
    }
   
    else{        
        printf("sono %d, mio figlio è %d\n",getpid( ),x);
        y=y+700; /* IL PADRE STAMPA 704 */ 
        printf("y vale %d e io sono %d\n",y,p);
    }
}

