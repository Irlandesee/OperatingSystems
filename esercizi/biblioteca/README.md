#problem description
Si consideri una biblioteca che dispone di 50 copie dei promessi sposi.
Abbiamo 3 tipi di processi-utenti della biblioteca, P_1, P_2, P_3
Il processo di tipi P_i noleggia i copie, se disponibili, altrimenti va in attesa.
Al momento della restituzione dei libri, il processo di tipo P_i non può cedere libri a processi del medesimo tipo P_i se ci sono almeno 5 processi di tipo diverso da P_i in attesa.
Programmare l'acquisizione e la restituzione dei libri da parte dei processi P_1, P_2, P_3 garantendo che non ci siano attese non motivate.

#notes
--- ricerca indice prenotabile
[0,1,0,1,1,0,0]
i = 1
[0,0,0,1,1,0,0]
