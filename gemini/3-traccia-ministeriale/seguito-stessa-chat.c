#include <stdio.h>

#define MAX_STAZIONI 100
#define VALORE_GUASTO -999.0f

/* 
 * Prototipi delle funzioni (come richiesto dalle specifiche di progetto):
 * - Ciascun punto del problema è risolto da una funzione dedicata.
 * - I prototipi sono dichiarati prima del main.
 */
int conta_superiori_30(float temperature[], int n);
float calcola_media_valide(float temperature[], int n);
float trova_temperatura_massima(float temperature[], int n);

int main() {
    int n, i;
    float temperature[MAX_STAZIONI]; // Array statico basato sull'ipotesi progettuale

    // Acquisizione del numero di stazioni
    printf("Inserisci il numero di stazioni meteorologiche (max %d): ", MAX_STAZIONI);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_STAZIONI) {
        printf("Errore: Numero di stazioni non valido o fuori dai limiti consentiti.\n");
        return 1;
    }

    // Lettura delle temperature rilevate dalle singole stazioni
    for (i = 0; i < n; i++) {
        printf("Inserisci la temperatura registrata dalla stazione %d (o %.0f se guasta): ", 
               i + 1, VALORE_GUASTO);
        scanf("%f", &temperature[i]);
    }

    // Svolgimento dei punti richiesti tramite chiamate a funzione
    int stazioni_maggiori_30 = conta_superiori_30(temperature, n);
    float temperatura_media = calcola_media_valide(temperature, n);
    float temperatura_max = trova_temperatura_massima(temperature, n);

    // Presentazione dei risultati
    printf("\n--- REPORT ELABORAZIONE DATI METEO ---\n");
    printf("1. Stazioni con temperatura superiore a 30 C: %d\n", stazioni_maggiori_30);
    
    if (temperatura_media == VALORE_GUASTO) {
        printf("2. Temperatura media: Impossibile calcolarla (tutte le stazioni risultano guaste).\n");
    } else {
        printf("2. Temperatura media (escluse le guaste): %.2f C\n", temperatura_media);
    }

    if (temperatura_max == VALORE_GUASTO) {
        printf("3. Temperatura massima: Non disponibile (tutte le stazioni risultano guaste).\n");
    } else {
        printf("3. Temperatura massima registrata: %.2f C\n", temperatura_max);
    }

    return 0;
}

// --- Definizioni delle funzioni (posizionate dopo il main) ---

/*
 * Punto 1: Conta le stazioni con temperatura > 30°C, escludendo i guasti.
 */
int conta_superiori_30(float temperature[], int n) {
    int conteggio = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (temperature[i] != VALORE_GUASTO && temperature[i] > 30.0f) {
            conteggio++;
        }
    }
    return conteggio;
}

/*
 * Punto 2: Calcola la temperatura media escludendo le stazioni guaste (-999).
 */
float calcola_media_valide(float temperature[], int n) {
    float somma = 0.0f;
    int stazioni_valide = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (temperature[i] != VALORE_GUASTO) {
            somma += temperature[i];
            stazioni_valide++;
        }
    }

    // Gestione del caso limite: zero stazioni funzionanti
    if (stazioni_valide == 0) {
        return VALORE_GUASTO;
    }

    return somma / stazioni_valide;
}

/*
 * Punto 3: Trova la temperatura massima registrata tra le stazioni operative.
 */
float trova_temperatura_massima(float temperature[], int n) {
    float max = VALORE_GUASTO;
    int primo_valido_trovato = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (temperature[i] != VALORE_GUASTO) {
            if (!primo_valido_trovato || temperature[i] > max) {
                max = temperature[i];
                primo_valido_trovato = 1;
            }
        }
    }

    return max;
}