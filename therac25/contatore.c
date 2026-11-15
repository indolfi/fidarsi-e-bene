/*
 * Therac-25, incidente di Yakima (1987): ricostruzione didattica.
 *
 * Questo NON è il codice originale, scritto in assembly per il PDP-11.
 * È una simulazione in C del meccanismo descritto da Nancy Leveson e
 * Clark Turner ("An Investigation of the Therac-25 Accidents",
 * IEEE Computer, luglio 1993).
 *
 * Durante la preparazione del trattamento una routine veniva ripetuta
 * di continuo. A ogni passaggio una variabile di un byte (chiamata
 * Class3 nell'analisi) veniva INCREMENTATA invece di essere impostata a
 * un valore fisso. Se era diversa da zero, il software controllava la
 * posizione del collimatore; se valeva zero, il controllo veniva
 * saltato. Un byte torna a zero ogni 256 incrementi: se l'operatore
 * premeva il tasto "set" proprio in quel passaggio, il fascio poteva
 * partire con la macchina in una configurazione non verificata.
 *
 * La correzione del produttore: assegnare un valore costante diverso
 * da zero invece di incrementare.
 *
 * Compilare con:  gcc -Wall -Wextra -fsanitize=undefined contatore.c
 * Nessun warning e nessuna segnalazione: in C l'overflow di un intero
 * senza segno è comportamento DEFINITO (aritmetica modulo 256).
 * Il difetto è nella logica, e lo trova solo chi ragiona sul codice.
 */
#include <stdio.h>
#include <stdint.h>

#define PASSAGGI 1000

int main(void) {
    uint8_t class3 = 0;          /* un solo byte, come nell'originale */
    int saltati = 0;
    int passaggio;

    for (passaggio = 1; passaggio <= PASSAGGI; passaggio++) {
        class3++;                /* il difetto: incrementa invece di assegnare */
        /* class3 = 1; */        /* la correzione */

        if (class3 != 0) {
            /* qui il software verificava la posizione del collimatore */
        } else {
            saltati++;
            printf("Passaggio %4d: class3 = %3u, controllo SALTATO\n",
                   passaggio, (unsigned)class3);
        }
    }

    printf("\nSu %d passaggi, controllo di sicurezza saltato %d volte.\n",
           PASSAGGI, saltati);
    return 0;
}
