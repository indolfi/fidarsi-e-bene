# Guardare sotto il cofano

`media.c` contiene la funzione `calcola_media` di Gemini, isolata. I file `media-O0.s` e `media-O2.s` sono l'assembly x86-64 prodotto da GCC 13 (sintassi Intel), senza ottimizzazioni e con `-O2`.

Per vederli affiancati al sorgente, con le righe colorate in corrispondenza, si incolla `media.c` su [Compiler Explorer](https://godbolt.org), si sceglie "x86-64 gcc 13" e si aggiungono le opzioni `-O0 -masm=intel` oppure `-O2 -masm=intel`.

Oppure in locale:

```
gcc -O2 -S -masm=intel -fno-asynchronous-unwind-tables -o - media.c
```

## Cosa guardare

**I puntatori che "non ci sono".** Il parametro `float vett[]` arriva nel registro `rdi`, a 64 bit: è un indirizzo. Con `-O2` il ciclo diventa `add rdi, 4`, cioè il puntatore che avanza di un `float` (4 byte) alla volta. La sintassi del C nasconde il puntatore; la macchina lo usa.

**La precisione nel nome dell'istruzione.** La somma è `addss`, *add scalar single*: un `float` a 32 bit, circa sette cifre significative. Dichiarando `double somma` diventa `addsd`, *add scalar double*. È la causa della media sbagliata con milioni di sensori (`make precisione`).

**La sentinella è uno schema di bit.** Il valore -999.0f compare come `.long -998653952`: gli stessi 32 bit letti come intero (0xC479C000). Il confronto `vett[i] != VALORE_GUASTO` confronta 32 bit esatti, quindi -999.5 è un'altra cosa.

**Il NaN che il compilatore conosce.** Il confronto con la sentinella è `ucomiss` seguito da `jp`, un salto sul flag di parità. Il processore segnala così un confronto "non ordinato", cioè con un NaN. Il compilatore lo gestisce; il programma no. Infatti `scanf("%f")` accetta come input le parole `nan` e `inf` (`make prova CASO=nan`).

**Un'uscita sola, poi due.** I due `return` del C, con `-O0`, diventano un salto verso un'unica uscita: un solo `ret`. Con `-O2` l'ottimizzatore duplica il `ret` per risparmiare un salto. La regola dell'uscita unica serve a chi legge e verifica il sorgente; la macchina segue altre convenienze.
