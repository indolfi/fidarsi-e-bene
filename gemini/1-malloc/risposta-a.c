#include <stdio.h>
#include <stdlib.h>

#define VALORE_GUASTO -999.0f

/* Prototipi delle funzioni richieste */
int conta_superiori_30(const float vett[], int n);
float calcola_media(const float vett[], int n);
float trova_massimo(const float vett[], int n);

int main(void) {
    int n, i;
    float *temperature = NULL;

    printf("Inserisci il numero di stazioni meteorologiche: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Numero di stazioni non valido.\n");
        return 1;
    }

    /* Allocazione dinamica del vettore in base al numero di stazioni */
    temperature = (float *)malloc(n * sizeof(float));
    if (temperature == NULL) {
        printf("Errore di allocazione della memoria.\n");
        return 1;
    }

    /* Lettura delle temperature */
    for (i = 0; i < n; i++) {
        printf("Stazione %d - Inserisci la temperatura (o %.0f se guasta): ", i + 1, VALORE_GUASTO);
        scanf("%f", &temperature[i]);
    }

    /* Elaborazione tramite le funzioni richieste */
    int num_sup30 = conta_superiori_30(temperature, n);
    float media = calcola_media(temperature, n);
    float massimo = trova_massimo(temperature, n);

    /* Stampa dei risultati */
    printf("\n--- RISULTATI ANALISI METEO ---\n");
    printf("1. Stazioni con temperatura superiore a 30 C: %d\n", num_sup30);
    
    if (media != VALORE_GUASTO) {
        printf("2. Temperatura media (escluse le stazioni guaste): %.2f C\n", media);
    } else {
        printf("2. Impossibile calcolare la media: tutte le stazioni risultano guaste.\n");
    }

    if (massimo != VALORE_GUASTO) {
        printf("3. Temperatura massima registrata: %.2f C\n", massimo);
    } else {
        printf("3. Nessuna temperatura valida registrata.\n");
    }

    /* Rilascio della memoria allocata */
    free(temperature);
    
    return 0;
}

/* ==========================================================================
 * Definizioni delle funzioni
 * ========================================================================== */

/* 1. Conta quante stazioni hanno registrato una temperatura > 30°C */
int conta_superiori_30(const float vett[], int n) {
    int count = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (vett[i] != VALORE_GUASTO && vett[i] > 30.0f) {
            count++;
        }
    }
    return count;
}

/* 2. Calcola la temperatura media escludendo le stazioni guaste */
float calcola_media(const float vett[], int n) {
    float somma = 0.0f;
    int validi = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (vett[i] != VALORE_GUASTO) {
            somma += vett[i];
            validi++;
        }
    }

    if (validi == 0) {
        return VALORE_GUASTO; /* Segnale di assenza di dati validi */
    }

    return somma / (float)validi;
}

/* 3. Trova la temperatura massima registrata */
float trova_massimo(const float vett[], int n) {
    float max = VALORE_GUASTO;
    int i, trovato = 0;

    for (i = 0; i < n; i++) {
        if (vett[i] != VALORE_GUASTO) {
            if (!trovato || vett[i] > max) {
                max = vett[i];
                trovato = 1;
            }
        }
    }

    return max;
}