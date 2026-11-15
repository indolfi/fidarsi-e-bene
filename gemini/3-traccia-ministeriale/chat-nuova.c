#include <stdio.h>

#define MAX_STATIONS 100
#define VALORE_GUASTO -999.0f

// Prototipi delle funzioni richiesti in testa al file
int contaStazioniSuperiori30(float temperature[], int n);
float calcolaTemperaturaMedia(float temperature[], int n);
float trovaTemperaturaMassima(float temperature[], int n);

int main() {
    int n, i;
    float temperature[MAX_STATIONS];

    printf("Inserisci il numero di stazioni meteorologiche (max %d): ", MAX_STATIONS);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_STATIONS) {
        printf("Errore: numero di stazioni non valido.\n");
        return 1;
    }

    // Acquisizione delle temperature
    for (i = 0; i < n; i++) {
        printf("Temperatura stazione %d (inserisci %.0f se guasta): ", i + 1, VALORE_GUASTO);
        scanf("%f", &temperature[i]);
    }

    // Elaborazione tramite le funzioni richieste
    int stazioniSuperiori30 = contaStazioniSuperiori30(temperature, n);
    float temperaturaMedia = calcolaTemperaturaMedia(temperature, n);
    float temperaturaMassima = trovaTemperaturaMassima(temperature, n);

    // Stampa dei risultati
    printf("\n--- RISULTATI ANALISI METEO ---\n");
    printf("1. Stazioni con temperatura > 30 C: %d\n", stazioniSuperiori30);

    if (temperaturaMedia != VALORE_GUASTO) {
        printf("2. Temperatura media (escluse le guaste): %.2f C\n", temperaturaMedia);
    } else {
        printf("2. Impossibile calcolare la media: tutte le stazioni sono guaste.\n");
    }

    if (temperaturaMassima != VALORE_GUASTO) {
        printf("3. Temperatura massima registrata: %.2f C\n", temperaturaMassima);
    } else {
        printf("3. Nessuna temperatura valida registrata.\n");
    }

    return 0;
}

// ---------------------------------------------------------
// Definizioni delle funzioni poste dopo il main
// ---------------------------------------------------------

// Punto 1: Conta le stazioni con temperatura > 30°C (escludendo le guaste)
int contaStazioniSuperiori30(float temperature[], int n) {
    int conteggio = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (temperature[i] != VALORE_GUASTO && temperature[i] > 30.0f) {
            conteggio++;
        }
    }
    return conteggio;
}

// Punto 2: Calcola la temperatura media escludendo le stazioni guaste
float calcolaTemperaturaMedia(float temperature[], int n) {
    float somma = 0.0f;
    int stazioniValide = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (temperature[i] != VALORE_GUASTO) {
            somma += temperature[i];
            stazioniValide++;
        }
    }

    if (stazioniValide == 0) {
        return VALORE_GUASTO; // Segnale di assenza di dati validi
    }

    return somma / stazioniValide;
}

// Punto 3: Trova la temperatura massima registrata tra quelle valide
float trovaTemperaturaMassima(float temperature[], int n) {
    float max = VALORE_GUASTO;
    int trovatoValido = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (temperature[i] != VALORE_GUASTO) {
            if (!trovatoValido || temperature[i] > max) {
                max = temperature[i];
                trovatoValido = 1;
            }
        }
    }

    return max;
}