#problem description
Si programmi un sistema in cui un insieme di processi condivide un array A di 3 interi (indici 0, 1, 2)
I valor iniziali dell'array sono tutti 0 => A[0]=A[1]=A[2]
Esistono le seguenti classi di processi:
-> Processi scrittori: iterativamente selezionano un indice 0 <= i <= 2 ed un valore intero v ed assegnano v ad A[i].
-> Processi lettori: iterativamente calcolano A[0]+A[1]+A[2]

#constraints:
- Le race condition devono essere impossibili

- Quando uno o più lettori stanno lavorando sull'array ed uno scrittore a in waiting perchè tenta di accedere all'array (waiting per evitare race condition), da questo momento in poi al più 10 lettori che tentano di accedere all'array possono accedere prima che almeno uno scrittore in attesa venga risvegliato. 
Questa condizione garantisce che gli scrittori non rimangano in attesa all'infinito per colpa dei lettori.

- quando uno o più scrittori stanno lavorando sull'array (in posizioni diverse se si tratta di più scrittori) ed un lettore va in waiting perchè tenta di accedere all'array (waiting per evitare race condition) da questo momento in poi al più 4 scrittori che tentano di accedere ad A[0], al più 4 scrittori che tentano di accedere ad A[1] ed al più 4 scrittori che tentato di accedere ad A[2] possono accedere prima che almeno un lettore venga risvegliato.
Questa condizione garantisce che i lettori non rimangano in attesa all'infinito per colpa degli scrittori

---Notes prodCons5 

int A[3] //buffer di 3 posizioni,
A[0],A[1],A[2] //inizializzati a 1

CONST NUM_MAX_LETTORI 10 //numero massimo di lettori per array
CONST NUM_MAX_SCRITTORI 4 //numero massimo di scrittori per posizione
CONST i 0 //A[0]
CONST j 1 //A[1]
CONST k 2 //A[2]

sem mutex


scrittore sem_wait(i) //tenta di accedere all'indirizzo i
=> while(lettori < 10)
	lettore legge
	lettore++


seleziona un indice tra 0 e 2 e valore v da assegnare a A[i]
scrittore:



lettore:





mtx
sem_R semaforo per i lettori
sem_I semaforo per scrittori su A[i]

wait_R Numero lettori in waiting
wait_i numero scrittori in waiting su A[i]
run_R numero lettori working
run_i true se e solo se uno scrittore sta lavorando su A[i]
x bonus lettori
x_i bonus scrittori su i


while( (ci sono processi scrittori che stanno lavorando
	oppure ci sono processi scrittori in waiting su A[i])
	E x==0)
	numeroLettoriInWaiting++
	segnala semaforo lettori







