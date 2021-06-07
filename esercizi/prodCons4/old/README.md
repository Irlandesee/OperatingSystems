#problem description
Si implementi il classico problema produttori/consumatori con le seguenti modifiche

-> esiste la classe dei consumatori "speciali" che consumano 2 elementi anzichè 1.

-> se un consumatore speciale va in waiting allora da questo momento in poi al massimo 5 consumatori normali potranno consumare prima che almeno un consumatore speciale venga risvegliato


--- notes prodCons4 

int buffer[100]
bool full = false
bool empty = true
int consCount

sem mtx //semaforo per mutua esclusione
sem prod = 0
sem cons = 0
sem specialCons = 0

void producer:
	int item; //item da mettere nel buffer
	int i; //indice per la scansione del buffer
	while(true):
		wait(mtx)
		if(full):
			signal(mtx);
		else:
			//scansiono alla ricerca di una posizione libera
			for i in 100
				if(buffer[i] == pos_libera)
					buffer[i] = item
					signal(prod)
					signal(mtx)

void consumer:
	int item; //item da consumare
	int i; //indice per la scansione del buffer
	while(true):
		wait(mtx);
		if(emtpy):
			signal(mtx);
		else:
			wait(prod)
			item = buffer[i];
			printf(item);
			signal(mtx)
			signal(prod);
			if(i == 100)
				i = 0



void special_consumer:
	int item
	int i = 0
	while(true):
		wait(mtx)
		if(empty)
			post(mtx);
		else:
			wait(specialCons)
			while(consCount < 5):
				consCount++
				signal(mtx)
				signal(cons)
			for i in 2:
				item = buffer[i]
				printf(item)
			signal(mtx)
			signal(specialCons)
			if(i == 100)
				i = 0

