# Prompt 3: la formula della seconda prova dell'Esame di Stato

Inviato come seguito, dopo i prompt 1 e 2, nella stessa chat. Risposta in `gemini/3-traccia-ministeriale/seguito-stessa-chat.*`.

> Avevo omesso una premessa alla traccia del problema. All'inizio c'è scritto: "Il candidato analizzi la realtà di riferimento e, formulate le opportune ipotesi aggiuntive, contribuisca alla stesura del progetto svolgendo i seguenti punti:"

La stessa richiesta è stata poi provata in una chat nuova, partendo da zero, con la premessa ministeriale in testa alla traccia e il vincolo sui puntatori in coda. Risposta in `gemini/3-traccia-ministeriale/chat-nuova.*`. Il codice ha la stessa struttura e gli stessi difetti di tutte le versioni precedenti.

> Il candidato analizzi la realtà di riferimento e, formulate le opportune ipotesi aggiuntive, contribuisca alla stesura del progetto svolgendo i seguenti punti:
>
> Scrivi un programma in C che risolva questo esercizio.
>
> Una rete di stazioni meteorologiche registra la temperatura massima giornaliera. Il programma chiede all'utente quante stazioni ci sono e poi legge la temperatura di ciascuna. Una stazione guasta comunica il valore convenzionale -999.
>
> Il programma deve:
> 1. contare quante stazioni hanno registrato una temperatura superiore a 30 gradi;
> 2. calcolare la temperatura media escludendo le stazioni guaste;
> 3. trovare la temperatura massima registrata.
>
> Usa una funzione per ciascun punto. I prototipi devono stare in testa al file e le definizioni delle funzioni dopo il main.
>
> Nel corso non si è svolta la parte dei puntatori e dell'allocazione dinamica della memoria.

I file `.md` contengono la risposta completa di Gemini, con l'analisi e le ipotesi; i file `.c` il solo codice.
