#problem description
In un barber shop lavora un solo barbiere, vi è una sola sedia adibita al taglio e vi sono N sedie per i clienti in attesa. Si assume N=20

-> comportamento del barbiere:
- All'apertura del negozi si mette a dormire nella sedia adibita al taglio, in attesa che un cliente entri e lo svegli
- quando ci sono clienti in attesa, il barbiere li chiama e li serve uno alla volta
- quando non ci sono clienti in attesa, il barbiere si rimette a dormire nella sedia adibita al taglio

-> Comportamento del cliente:
- Quando entra nel negozio, se non ci sono sedie libere va a cercarsi un altro barbiere
- Quando entra nel negozio, se c'è almeno una sedia libera ne occupa una, svegliando il barbiere se sta dormendo, ed attende di essere chaimato dal barbiere per il taglio

- barbiere:
if(non ci sono clienti in attesa)
	dormi
altrimenti
	prendi cliente più anziano in waiting
	taglia i capelli
	libera la sedia
	continue finchè ci sono clienti in attesa

- cliente
if(non ci sono sedie libere)
	cerca altro barbiere
altrimenti
	prendi posto su una sedia
	if(barbiere dorme)
		sveglia barbiere
		prendi posto
		attendi chiamata barbiere
		esci dal negozio
	altrimenti
		prendi posto
		attendi chiamata barbiere
		esci dal negozio