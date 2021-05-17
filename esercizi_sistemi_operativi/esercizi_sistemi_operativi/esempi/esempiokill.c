#include<stdio.h>
#include<signal.h>

main(  ){
 int p = getpid( );/*getpid is a system call that returns the PID*/
    printf("sono %d, ora mi  clono\n",p);
    int x = fork( );/*returns 0 al figlio e l’ID del figlio al padre*/
    /*ora abbiamo 2 processi (2 PCB), il loro programma è uguale*/
    int y = 10; /*istruzione eseguita da entrambi padre e figlio*/ 
    printf("y vale %d\n",y); /*anche questa*/ 
   
    if(x==0){   /*ramo eseguito solo dal figlio*/
        int f = getpid( );
        printf("sono il figlio, cioè %d\n",f);
        for(int i=0;;i++){printf("ciao, %d \n ",i);}
   }
   
    else{         /*ramo eseguito solo dal padre*/
        printf("sono %d, mio figlio è %d\n",getpid( ),x);
        for(int i=1;i<500000;i++){}
        kill(x,SIGKILL);
    }
    
}

