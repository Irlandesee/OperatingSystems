#problem description
Si consideri il classico problema dei produttori e consumatori, con
il buffer implementato con un array di interi di dimensione 100.
Si assuma, per semplicita’, che gli interi prodotti e consumati
siano >=0. Si considerino le seguenti condizioni aggiuntive:
1.Gli interi pari possono occupare solo le posizioni da 0 a 49;
2.Gli interi dispari possono occupare solo le posizioni da 50 a 99;
3.Vi e’ una nuova categoria di processi, i processi ConsPari, che
consumano tutti gli interi pari, se l’array contiene almeno 20
interi pari;
Quanto un processo tenta di effettuare un’operazione al momento non
consentita (per esempio produrre un intero che il buffer non può al
momento ospitare), il processo deve essere messo in attesa.
Programmare il sistema sfruttando i semafori con la semantica
tradizionale.