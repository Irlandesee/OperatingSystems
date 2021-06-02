#problem description
Si programmi un sistema in cui un insieme di processi condivide un
array A di 3 interi (indici 0, 1 e 2).
I valori iniziali dell'array sono tutti 0 (A[0]=A[1]=A[2] = 0).
Esistono le seguenti classi di processi:
- processi scrittori: iterativamente selezionano un indice 0 <= i <=
2 ed un valore intero v ed assegnano v ad A[i].
- processi lettori: iterativamente calcolano A[0]+A[1]+A[2].
Condizioni:
- race condition devono essere impossibili
- quando uno o piu' lettori stanno lavorando sull'array ed uno
scrittore va in waiting perche' tenta di accedere all'array (va in
waiting perche' altrimenti potrebbe verificarsi una race condition),
da questo momento in poi al piu' 10 lettori che tentano di accedere
all'array possono accedere prima che almeno uno scrittore in attesa
venga risvegliato. (Questa condizione garantisce che gli scrittori
non
rimangano in attesa all'infinito "per colpa" dei lettori).
-quando uno o piu' scrittori stanno lavorando sull'array
(ovviamente in posizioni diverse se si tratta di piu' scrittori) ed
un lettore va in waiting perche' tenta di accedere all'array (va in
waiting perche' altrimenti potrebbe verificarsi una race condition),
da questo momento in poi al piu' 4 scrittori che tentano di accedere
ad A[0], al piu' 4 scrittori che tentano di accedere ad A[1] ed al
piu' 4 scrittori che tentano di accedere ad A[2] possono accedere
prima che almeno un lettore venga risvegliato.
(Questa condizione garantisce che i lettori non rimangano in attesa
all'infinito "per colpa" degli scrittori).