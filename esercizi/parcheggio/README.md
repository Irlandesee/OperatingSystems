#problem description
Un parcheggio ha 30 posti, 2 ingressi con sbarra A e B e 1 uscita
Quando un veicolo si presenta ad uno dei due ingressi, se c'è almeno un posto libero entra, parcheggia ed esce dal parcheggio, altrimenti prenota l'ingresso ed attende di poter entrare.
Se ci sono veicoli in attesa ad entrambi gli ingressi, vengono fatti entrare quando altri veicoli escono dal pargheggio, aprendo le sbarre alternativamente.
Quando un veicolo esce dal parcheggio, se ci sono veicoli in atesa ad almeno uno dei 2 ingressi, ne fa entrare uno.

#notes parte a 

park_A(){
	entrance_A();
	park()
	exit();
}

park_B(){
	entrance_B();
	park();
	exit();
}

entrance_A(){
	if(numero posti disponibili > 0){
		parcheggia
	}
	altrimenti:
		prenota posto
		attendi che si liberi un posto
}

entrance_B(){
	if(numero posti disponibili > 0)
		parcheggia
	altrimenti:
		prenota posto
		attendi che si liberi un posto
}

exit(){
	if(ci sono veicoli in attesa):
		while(veicoliInAttesa > 0)
			apri sbarra A
			apri sbarra B
	altrimenti
		parcheggio è libero
}

se ce un posto libero
	entra
	parcheggia
	esce
altrimenti
	prentoa ingresso

se ci sono veicoli ad entrambi gli ingressi
	entrano alternativamente

in uscita, se ci sono veicoli in attesa ad almeno un ingresso
	ne fa entrare uno