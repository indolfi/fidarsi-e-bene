# Il contatore del Therac-25

Il Therac-25 era un acceleratore lineare per radioterapia prodotto dall'AECL (Atomic Energy of Canada Limited). Tra il 1985 e il 1987 sei incidenti noti provocarono sovradosaggi di decine di volte la dose prescritta; almeno tre pazienti morirono. Rispetto ai modelli precedenti, gli interblocchi hardware erano stati eliminati e la sicurezza era affidata interamente al software, in parte riutilizzato dal Therac-20.

Gli incidenti ebbero due cause software diverse. A Tyler, in Texas, una race condition: se l'operatore correggeva la modalità di trattamento entro pochi secondi, lo schermo si aggiornava ma la configurazione della macchina no. A Yakima, nello stato di Washington, il difetto ricostruito in `contatore.c`: una variabile di un byte, incrementata a ogni passaggio di una routine di controllo, tornava a zero ogni 256 passaggi, e in quell'istante la verifica della posizione del collimatore veniva saltata.

```
make therac
```

Il programma compila senza avvisi anche con `-Wall -Wextra -fsanitize=undefined`, perché in C l'overflow di un intero senza segno è comportamento definito: l'aritmetica è modulo 256. Nessuno strumento può segnalare un errore che, per il linguaggio, non è un errore. Il difetto sta nell'intenzione del programmatore, che voleva un indicatore "diverso da zero" e ha scritto un contatore.

`contatore.c` è una simulazione didattica in C, non il codice originale, che era scritto in assembly per il PDP-11.

## Fonte

Nancy G. Leveson, Clark S. Turner, *An Investigation of the Therac-25 Accidents*, IEEE Computer, vol. 26, n. 7, luglio 1993, pp. 18-41.
