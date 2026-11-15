/* La funzione calcola_media di Gemini (cartella gemini/2-array-fisso),
 * isolata per Compiler Explorer. */
#define VALORE_GUASTO -999.0f

float calcola_media(float vett[], int n) {
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
        return VALORE_GUASTO;
    }

    return somma / (float)validi;
}
