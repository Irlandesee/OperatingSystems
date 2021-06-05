#problem description parte a
un vecchio ponte consente di attraversare un fiume nelle direzioni
nord->sud
sud->nord
con i seguenti vincoli:
- per ragioni di peso, in ogni istante al più un veicolo può passare sul ponte
-se un veicolo trova il ponte occupato, attende che si liberi. Non è previsto che il veicolo decida di rinunciare ad attraversare il ponte
-dopo che un veicolo ha attraversato il ponte in una direzione se ci sono veicoli in attesa su entrambi i lati allora deve passare per primo un eicolo che viaggia nella direzone opposta

--- notes parte a
entra_a_nord
attraversa
esci_a_sud

entra_a_nord:
if(il ponte è libero):
	ponteLibero = false
	attraversa
altrimenti
	incodatiANord
	aspetta il turno

esci_a_sud:
if(veicoli in attesa a sud)
	segnala semaforo a sud
altrimenti
	segnala semaforo a nord

#problem description parte b
Si suppone che il ponte non abbia più problemi di peso, e possa reggere più veicoli ma abbia una sola corsia:
- essendoci una sola corsia, in ogni istante tutti i veicoli sul ponte devono andare nella medesima direzione
- un veicolo può entrare sul ponte nei seguenti casi:
-> ponte è libero
-> sul ponte ci sono veicoli che stanno andando nella medesima direzione e
dall'altro non ci sono veicoli in attesa.

---- notes parte b
entra_a_nord
attraversa
esci_a_sud

sensoMarcia = false -> direzione north_to_south
sensoMarcia = true -> direzione south_to_north

entra_a_nord:
if(il ponte è libero):
	ponteLibero = false
	sensoMarcia = false
	attraversa
altrimenti:
	//ponte non è libero
	if(sensoMarcia == false e !(ci sono veicoli in attesa a sud)):
		attraversa
	altrimenti:
		aspetta

esci_a_sud:
if(ci sono veicoli in attesa a sud)
	sensoMarcia = true
	segnala semaforo sud
altrimenti
	if(ci sono veicoli in attesa a nord)
		sensoMarcia = false
		segnala semaforo nord
	altrimenti
		bridgeFree = true

#problem description parte c
Per smaltire il traffico con maggior efficienza, supponiamo ora che quando un veicolo è in attesa ad un lato del ponte perchè altri veicoli stanno andando verso il lato in cui si trova, sia consentito ad ulteriori 10 veicoli di entrare dal lato opposto

--- notes parte c
entra_a_nord
attraversa
esci_a_sud

int vehicleCount = 0; //
bool sensoMarcia = false //direzione north_to_south
bool sensoMarcia = true //direzioen south_to_north

entra_a_nord:
if(ponte è libero):
	ponteLibero = false
	sensoMarcia = false
	attraversa
altrimenti:
	//ponte non è libero
	if(sensoMarcia == false e !(ci sono veicoli in attesa a sud)):
		attraversa
	altrimenti: //ci sono veicoli in attesa dall'altra parte ne faccio //passare 10 di fila
	while(vehicleCount > 0):
		segnala  semaforo a sud

esci_a_sud:
if(ci sono veicoli in attesa a sud):
	sensoMarcia = true
	segnala semaforo sud
altrimenti: //non ci sono veicoli in attesa a sud
	if(ci sono veicoli in attesa a nord)
		sensoMarcia = false
		segnala semaforo nord
	altrimenti: //non ci sono veicoli in attesa da nessuna parte
		bridgeFree = true











