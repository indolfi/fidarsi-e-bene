#include <stdio.h>
#include <stdlib.h>

#define STAZIONE_GUASTA -999.0f

// Prototipi delle funzioni
int conta_superiori_30(const float vett[], int n);
float calcola_media(const float vett[], int n);
float trova_massimo(const float vett[], int n);

int main() {
    int n, i;
    float *temperature;

    printf("Inserisci il numero di stazioni meteorologiche: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Errore: inserire un numero valido di stazioni.\n");
        return 1;
    }

    // Allocazione dinamica dell'array in base al numero inserito
    temperature = (float *)malloc(n * sizeof(float));
    if (temperature == NULL) {
        printf("Errore di allocazione della memoria.\n");
        return 1;
    }

    // Lettura delle temperature
    for (i = 0; i < n; i++) {
        printf("Inserisci la temperatura della stazione %d (inserisci -999 se guasta): ", i + 1);
        scanf("%f", &temperature[i]);
    }

    // Elaborazione tramite le funzioni richieste
    int num_superiori_30 = conta_superiori_30(temperature, n);
    float media = calcola_media(temperature, n);
    float massimo = trova_massimo(temperature, n);

    // Stampa dei risultati
    printf("\n=== RISULTATI RILEVAZIONI METEO ===\n");
    printf("1. Stazioni con temperatura superiore a 30 C: %d\n", num_superiori_30);

    if (media != STAZIONE_GUASTA) {
        printf("2. Temperatura media (escluse le guaste): %.2f C\n", media);
    } else {
        printf("2. Impossibile calcolare la media: tutte le stazioni sono guaste.\n");
    }

    if (massimo != STAZIONE_GUASTA) {
        printf("3. Temperatura massima registrata: %.2f C\n", massimo);
    } else {
        printf("3. Nessuna temperatura valida registrata (tutte le stazioni sono guaste).\n");
    }

    // Rilascio della memoria allocata
    free(temperature);
    return 0;
}

// ==========================================
// DEFINIZIONE DELLE FUNZIONI
// ==========================================

// 1. Conta quante stazioni hanno registrato una temperatura > 30°C
int conta_superiori_30(const float vett[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (vett[i] != STAZIONE_GUASTA && vett[i] > 30.0f) {
            count++;
        }
    }
    return count;
}

// 2. Calcola la temperatura media escludendo le stazioni guaste
float calcola_media(const float vett[], int n) {
    float somma = 0.0f;
    int stazioni_valide = 0;

    for (int i = 0; i < n; i++) {
        if (vett[i] != STAZIONE_GUASTA) {
            somma += vett[i];
            stazioni_valide++;
        }
    }

    if (stazioni_valide == 0) {
        return STAZIONE_GUASTA; // Valore di flag per indicare l'assenza di dati validi
    }

    return somma / stazioni_valide;
}

// 3. Trova la temperatura massima registrata
float trova_massimo(const float vett[], int n) {
    float max = STAZIONE_GUASTA;
    int trovato_valido = 0;

    for (int i = 0; i < n; i++) {
        if (vett[i] != STAZIONE_GUASTA) {
            if (!trovato_valido || vett[i] > max) {
                max = vett[i];
                trovato_valido = 1;
            }
        }
    }

    return max; // Restituisce STAZIONE_GUASTA se non ci sono letture valide
}