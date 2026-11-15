#include <stdio.h>
#include <stdlib.h>

#define VALORE_GUASTO -999.0f

// Prototipi delle funzioni richieste
int conta_superiori_30(const float temperature[], int n);
float calcola_media_valide(const float temperature[], int n);
float trova_temperatura_massima(const float temperature[], int n);

int main() {
    int n, i;
    float *temperature = NULL;

    printf("Inserisci il numero di stazioni meteorologiche: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Numero di stazioni non valido.\n");
        return 1;
    }

    // Allocazione dinamica dell'array per le temperature
    temperature = (float *)malloc(n * sizeof(float));
    if (temperature == NULL) {
        printf("Errore di allocazione della memoria.\n");
        return 1;
    }

    // Lettura delle temperature
    for (i = 0; i < n; i++) {
        printf("Inserisci la temperatura registrata dalla stazione %d (o %.0f se guasta): ", 
               i + 1, VALORE_GUASTO);
        scanf("%f", &temperature[i]);
    }

    // 1. Contare le stazioni con temperatura > 30 gradi
    int stazioni_maggiori_30 = conta_superiori_30(temperature, n);

    // 2. Calcolare la temperatura media escludendo le guaste
    float temperatura_media = calcola_media_valide(temperature, n);

    // 3. Trovare la temperatura massima registrata
    float temperatura_max = trova_temperatura_massima(temperature, n);

    // Stampa dei risultati
    printf("\n--- RIEPILOGO DATI METEO ---\n");
    printf("1. Stazioni con temperatura superiore a 30 C: %d\n", stazioni_maggiori_30);
    
    if (temperatura_media == VALORE_GUASTO) {
        printf("2. Temperatura media: Non calcolabile (tutte le stazioni sono guaste).\n");
    } else {
        printf("2. Temperatura media (escluse le guaste): %.2f C\n", temperatura_media);
    }

    if (temperatura_max == VALORE_GUASTO) {
        printf("3. Temperatura massima: Non disponibile (tutte le stazioni sono guaste).\n");
    } else {
        printf("3. Temperatura massima registrata: %.2f C\n", temperatura_max);
    }

    // Pulizia della memoria allocata
    free(temperature);

    return 0;
}

// --- Definizioni delle funzioni ---

// 1. Conta quante stazioni hanno registrato una temperatura > 30 (escludendo i guasti)
int conta_superiori_30(const float temperature[], int n) {
    int conteggio = 0;
    for (int i = 0; i < n; i++) {
        if (temperature[i] != VALORE_GUASTO && temperature[i] > 30.0f) {
            conteggio++;
        }
    }
    return conteggio;
}

// 2. Calcola la temperatura media escludendo le stazioni guaste (-999)
float calcola_media_valide(const float temperature[], int n) {
    float somma = 0.0f;
    int stazioni_valide = 0;

    for (int i = 0; i < n; i++) {
        if (temperature[i] != VALORE_GUASTO) {
            somma += temperature[i];
            stazioni_valide++;
        }
    }

    if (stazioni_valide == 0) {
        return VALORE_GUASTO; // Restituisce il codice guasto se non ci sono dati validi
    }

    return somma / stazioni_valide;
}

// 3. Trova la temperatura massima registrata tra quelle valide
float trova_temperatura_massima(const float temperature[], int n) {
    float max = VALORE_GUASTO;
    int primo_valido_trovato = 0;

    for (int i = 0; i < n; i++) {
        if (temperature[i] != VALORE_GUASTO) {
            if (!primo_valido_trovato || temperature[i] > max) {
                max = temperature[i];
                primo_valido_trovato = 1;
            }
        }
    }

    return max;
}