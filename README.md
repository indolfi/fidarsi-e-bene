# Fidarsi è bene, compilare con -fsanitize è meglio

**Verificare il codice che non abbiamo scritto**

Materiali del talk di Pierangelo Indolfi al DevFest Bari 2026 (12 dicembre 2026).

Gli agenti IA promettono che chiunque potrà costruire software descrivendolo a parole. Ma quando tutti possono costruire, chi è in grado di controllare? Qui c'è tutto quello che serve per ripetere l'esperimento del talk: i prompt, le risposte di Gemini così come sono arrivate, i casi di prova, gli strumenti per trovare gli errori e una soluzione corretta.

## L'esperimento

A Gemini è stato chiesto di svolgere un tipico esercizio d'esame di un corso di programmazione in C: una rete di stazioni meteorologiche, la temperatura di ciascuna, il valore convenzionale -999 per le stazioni guaste, e tre funzioni per contare le temperature sopra i 30 gradi, calcolare la media e trovare il massimo.

Il prompt è stato provato in tre varianti, in chat diverse, il 15 novembre 2026 (cartella `prompt/`). Le otto risposte ottenute (cartella `gemini/`) sono ordinate, commentate, compilano senza errori e rispettano le consegne. Hanno anche, tutte, gli stessi difetti. Nemmeno la formula della seconda prova dell'Esame di Stato, *"Il candidato analizzi la realtà di riferimento e, formulate le opportune ipotesi aggiuntive..."*, cambia il codice: Gemini scrive un'analisi formalmente corretta e poi produce, riga per riga, lo stesso programma di prima.

## Che cosa si rompe, e chi se ne accorge

I risultati si riferiscono a `gemini/2-array-fisso/risposta-a.c`, compilato con GCC 13 su Linux. Ogni caso ha un file in `input/`.

| Caso | Input | Risultato | Chi lo scopre |
|---|---|---|---|
| `normale` | 25, 30, 35 | media 30,00, massimo 35,00 | corretto |
| `lettera` | 25, `abc`, 30 | media **8,33** invece di 27,50, nessun messaggio | solo valgrind |
| `sentinella-sbagliata` | -999.5, 20 | media **-489,75 gradi** | nessuno strumento |
| `nan` | 25, `nan`, 30 | media **nan**, massimo 30 | nessuno strumento |
| `inf` | 25, `inf`, 30 | media e massimo **inf** | nessuno strumento |
| `n-troncato` | 4294967346 stazioni | accetta, e chiede **50** temperature | nessuno strumento |
| `zero-stazioni` | 0 | rifiutato: l'insieme vuoto non è ammesso | lettura del codice |
| `tutte-guaste` | -999 ×3 | gestito correttamente | corretto |
| `tutte-negative` | -5, -12, -3 | massimo -3,00 | corretto |
| `troppe-stazioni` | 150 | rifiutato: limite di 100 deciso dall'IA, non dalla traccia | lettura del codice |

Con le versioni che usano `malloc` (`gemini/1-malloc/`) il limite delle 100 stazioni sparisce, e compare un altro problema: la somma accumulata in `float`. Con un milione di sensori che leggono tutti 21,7 gradi la media stampata è 21,85; con cinque milioni diventa 22,02 (`make precisione`, richiede circa un minuto).

## Gli strumenti, uno dopo l'altro

```
make prova CASO=lettera       # il programma risponde 8.33, senza lamentarsi
make warning                  # -Wall -Wextra: nessun avviso
make o2                       # -O2: compare "ignoring return value of 'scanf'"
make asan CASO=lettera        # AddressSanitizer e UBSan: nessuna segnalazione
make valgrind CASO=lettera    # "Conditional jump depends on uninitialised value"
```

Lo stesso compilatore vede cose diverse a seconda delle opzioni: l'avviso su `scanf` compare solo con l'ottimizzazione, perché attiva i controlli rinforzati della libreria standard. AddressSanitizer protegge la memoria, ma un valore mai letto non è un accesso fuori dai limiti. Valgrind trova la variabile non inizializzata. Nessuno dei tre sa che -999.5 non è una temperatura e che `nan` non è un dato meteorologico: lo sa chi conosce la realtà di riferimento.

`make tutti` esegue il programma su tutti i casi. Per provare un'altra risposta di Gemini basta indicarla: `make tutti SRC=gemini/3-traccia-ministeriale/chat-nuova.c`.

## Una soluzione corretta

`soluzione/meteo.c` risolve lo stesso esercizio dichiarando le proprie ipotesi in testa al file e rispettando i criteri di un corso introduttivo: prototipi in testa, un solo punto di uscita per ogni funzione, niente puntatori espliciti né allocazione dinamica. Rispetto al codice di Gemini:

- l'input non valido viene rifiutato e richiesto di nuovo, senza interrompere il programma, e la fine dell'input (Ctrl-D o fine file) non lo blocca in un ciclo infinito;
- le temperature accettate sono quelle comprese tra -90 e 60 gradi, oltre a -999; il controllo è scritto in positivo, `t >= MIN_T && t <= MAX_T`, perché un NaN non soddisfa nessun confronto e la forma negata lo lascerebbe passare;
- zero stazioni è un caso ammesso, e il programma distingue "nessuna stazione" da "tutte guaste";
- la media non restituisce -999 come segnale d'errore, così un dato e un errore non viaggiano più sullo stesso canale;
- la somma è accumulata in `double`.

Un limite resta, ed è dichiarato nel sorgente: `scanf("%d")` non segnala un numero troppo grande per un `int`. Per chiuderlo bisogna leggere la riga come testo con `fgets` e convertirla con `strtol`.

```
make soluzione
```

## Le altre cartelle

- `assembly/`: la funzione della media vista in assembly, con i puntatori che "non ci sono", la precisione scritta nel nome dell'istruzione e il NaN che il compilatore conosce e il programma no.
- `therac25/`: la ricostruzione del contatore a 8 bit che, nel 1987, fece saltare un controllo di sicurezza in un acceleratore per radioterapia.

## Per approfondire

-----

## Licenza

Il codice (cartelle `soluzione/`, `therac25/`, `input/` e il `Makefile`) è distribuito con licenza MIT, come indicato nel file `LICENSE`.

I testi (i file README e le note in `assembly/`) sono distribuiti con licenza [Creative Commons Attribuzione 4.0](https://creativecommons.org/licenses/by/4.0/deed.it).

I file della cartella `gemini/` sono stati generati da Google Gemini e sono riprodotti senza modifiche come oggetto di analisi; non sono coperti dalle licenze sopra indicate.


- *Errori di sistema*, la newsletter dell'autore: <https://pierangeloindolfi.substack.com>
- Nancy G. Leveson, Clark S. Turner, *An Investigation of the Therac-25 Accidents*, IEEE Computer, 1993
- Direttiva (UE) 2024/2853 sulla responsabilità per danno da prodotti difettosi, che dal 9 dicembre 2026 include esplicitamente il software: <https://eur-lex.europa.eu/eli/dir/2024/2853/oj/ita>

## Requisiti

GCC o Clang, `make`, valgrind. Su Windows funziona tutto dentro WSL.
