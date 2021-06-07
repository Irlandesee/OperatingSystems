#problem description
Si consideri il classico problema dei produttori e consumatori, con il buffer implementato con un array di interi di dimensione 100
Si assuma, per semplicità che gli interi prodotti e consuamti siano tutti strettamente positivi oppure uguali a 0, vale a dire >= 0

- Condizioni aggiuntive:
1. Gli interi pari possono occupare solo le posizioni di indice pari
2. Gli interi dispari divisibili per 3 possono occupare solo le posizioni di indice dispari divisibile per 3
3. Gli interi dispari che non sono divisibili per 3 possono occupare solo le posizioni di indice dispari non divisibili per 3

Quando un processo tenta di effettuare un'operazione al momento non consentita (tradurre un intero che il buffer non può ospitare), il processo deve essere sospeso.

