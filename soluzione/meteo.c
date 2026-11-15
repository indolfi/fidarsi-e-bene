/*
 * Stazioni meteorologiche: una soluzione "da esame".
 *
 * Ipotesi aggiuntive, dichiarate:
 * - la rete conta al massimo MAX_STAZIONI stazioni; zero stazioni è un
 *   caso ammesso (insieme vuoto) e il programma lo gestisce;
 * - una temperatura plausibile è compresa tra MIN_T e MAX_T, che
 *   contengono i record mondiali (-89,2 °C a Vostok, 56,7 °C nella
 *   Death Valley); STAZIONE_GUASTA sta fuori da questo intervallo;
 * - un input non numerico o fuori intervallo viene rifiutato e richiesto
 *   di nuovo, senza interrompere il programma;
 * - se l'input termina (fine file, Ctrl-D), il numero di stazioni vale 0
 *   e le temperature non pervenute valgono come stazioni guaste.
 *
 * Limite noto, dichiarato: scanf("%d") non segnala un numero che non sta
 * in un int (per lo standard è comportamento indefinito; la glibc tronca,
 * e 4294967346 diventa 50). Per chiuderlo serve leggere la riga come
 * testo con fgets e convertirla con strtol, fuori dal programma del corso.
 *
 * Criteri di stile del corso: prototipi in testa, definizioni dopo il
 * main, un solo punto di uscita per ogni funzione, niente puntatori
 * espliciti né allocazione dinamica.
 */
#include <stdio.h>

#define MAX_STAZIONI 100
#define MIN_T -90.0f
#define MAX_T 60.0f
#define STAZIONE_GUASTA -999.0f
#define SOGLIA 30.0f

int leggi_numero_stazioni(void);
float leggi_temperatura(int stazione);
void scarta_riga(void);
int conta_valide(float vett[], int n);
int conta_superiori(float vett[], int n, float soglia);
float calcola_media(float vett[], int n);
float trova_massimo(float vett[], int n);

int main(void) {
    float temperature[MAX_STAZIONI];
    int n, i, valide;

    n = leggi_numero_stazioni();
    for (i = 0; i < n; i++) {
        temperature[i] = leggi_temperatura(i + 1);
    }

    valide = conta_valide(temperature, n);

    printf("\n--- RISULTATI ---\n");
    printf("1. Stazioni sopra i %.0f gradi: %d\n", SOGLIA,
           conta_superiori(temperature, n, SOGLIA));

    if (n == 0) {
        printf("2-3. Nessuna stazione: media e massimo non definiti.\n");
    } else if (valide == 0) {
        printf("2-3. Tutte le %d stazioni sono guaste: "
               "media e massimo non definiti.\n", n);
    } else {
        printf("2. Temperatura media (stazioni valide: %d su %d): %.2f\n",
               valide, n, calcola_media(temperature, n));
        printf("3. Temperatura massima: %.2f\n",
               trova_massimo(temperature, n));
    }

    return 0;
}

/* Legge n nell'intervallo 0..MAX_STAZIONI, insistendo finché è valido. */
int leggi_numero_stazioni(void) {
    int n = -1;
    int letti;
    do {
        printf("Numero di stazioni (0-%d): ", MAX_STAZIONI);
        letti = scanf("%d", &n);
        if (letti == 0) {
            scarta_riga();
        }
    } while (letti != EOF && (letti != 1 || n < 0 || n > MAX_STAZIONI));

    if (letti == EOF) {
        n = 0;
    }
    return n;
}

/*
 * Legge una temperatura: accetta STAZIONE_GUASTA oppure un valore
 * compreso tra MIN_T e MAX_T. Il controllo è scritto "in positivo"
 * perché un NaN non soddisfa nessun confronto: con la forma
 * (t < MIN_T || t > MAX_T) un "nan" digitato passerebbe.
 */
float leggi_temperatura(int stazione) {
    float t = STAZIONE_GUASTA;
    int letti;
    int accettata = 0;
    do {
        printf("Temperatura stazione %d (%.0f se guasta): ",
               stazione, STAZIONE_GUASTA);
        letti = scanf("%f", &t);
        if (letti == 1) {
            accettata = (t == STAZIONE_GUASTA) || (t >= MIN_T && t <= MAX_T);
        } else if (letti == 0) {
            scarta_riga();
        }
    } while (letti != EOF && !accettata);

    if (letti == EOF) {
        t = STAZIONE_GUASTA;
    }
    return t;
}

/* Scarta il resto della riga, fermandosi anche a fine input. */
void scarta_riga(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int conta_valide(float vett[], int n) {
    int conteggio = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (vett[i] != STAZIONE_GUASTA) {
            conteggio++;
        }
    }
    return conteggio;
}

int conta_superiori(float vett[], int n, float soglia) {
    int conteggio = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (vett[i] != STAZIONE_GUASTA && vett[i] > soglia) {
            conteggio++;
        }
    }
    return conteggio;
}

/* Precondizione: almeno una stazione valida. La somma è in double. */
float calcola_media(float vett[], int n) {
    double somma = 0.0;
    int valide = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (vett[i] != STAZIONE_GUASTA) {
            somma += vett[i];
            valide++;
        }
    }
    return (float)(somma / valide);
}

/* Precondizione: almeno una stazione valida. */
float trova_massimo(float vett[], int n) {
    float massimo = MIN_T;
    int i;
    for (i = 0; i < n; i++) {
        if (vett[i] != STAZIONE_GUASTA && vett[i] > massimo) {
            massimo = vett[i];
        }
    }
    return massimo;
}
