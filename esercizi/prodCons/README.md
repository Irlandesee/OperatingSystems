#problem description
Si consideri il problema dei produttori e consumatori.
Si assuma che il buffer sia un array di 10 interi gestito circolarmente.
Si assumano i seguenti vincoli aggiuntivi:
- il valore 3 non deve essere presente più di 1 volta nell'array
- il valore 5 non deve essere presente più di 2 volte nell'array

i processi che tentato di effettuare operazioini al momento non consentite devono essere messi in attesa

--notes 
BUFFER_SIZE 10
int buffer[BUFFER_SIZE]

sem_t mutex = 1
sem_t empty = 10
sem_t sem3 = 1
sem_t sem5 = 2

