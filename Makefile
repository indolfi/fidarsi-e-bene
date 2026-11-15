# Fidarsi è bene, compilare con -fsanitize è meglio
# DevFest Bari 2026 - Pierangelo Indolfi
#
# Uso tipico:
#   make base                     compila il codice di Gemini senza opzioni
#   make prova CASO=lettera       lo esegue con input/lettera.txt
#   make warning                  compila con -Wall -Wextra (nessun avviso)
#   make o2                       compila con -O2 (compare l'avviso su scanf)
#   make asan CASO=lettera        AddressSanitizer + UBSan (nessuna segnalazione)
#   make valgrind CASO=lettera    valgrind (trova i valori non inizializzati)
#   make tutti                    esegue il codice di Gemini su tutti i casi
#   make precisione               la media in float su milioni di sensori
#   make soluzione                la versione corretta su tutti i casi
#   make therac                   la ricostruzione del contatore del Therac-25
#
# Per provare un'altra risposta di Gemini:
#   make prova SRC=gemini/3-traccia-ministeriale/chat-nuova.c CASO=nan

SRC    ?= gemini/2-array-fisso/risposta-a.c
MALLOC ?= gemini/1-malloc/risposta-a.c
CASO   ?= normale
BIN    := build
CC     ?= gcc

.PHONY: base prova warning o2 asan valgrind tutti precisione soluzione therac clean

$(BIN):
	mkdir -p $(BIN)

base: | $(BIN)
	$(CC) -g -o $(BIN)/meteo $(SRC)

prova: base
	./$(BIN)/meteo < input/$(CASO).txt

warning: | $(BIN)
	$(CC) -g -Wall -Wextra -o $(BIN)/meteo $(SRC)

o2: | $(BIN)
	$(CC) -g -O2 -Wall -Wextra -o $(BIN)/meteo $(SRC)

asan: | $(BIN)
	$(CC) -g -fsanitize=address,undefined -o $(BIN)/meteo-asan $(SRC)
	./$(BIN)/meteo-asan < input/$(CASO).txt

valgrind: base
	valgrind --track-origins=yes ./$(BIN)/meteo < input/$(CASO).txt

tutti: base
	@for f in input/*.txt; do \
	  echo; echo "=== $$f"; ./$(BIN)/meteo < $$f | tail -3; \
	done

# Genera i file di input al volo: un milione e cinque milioni di stazioni
# che leggono tutte 21,7 gradi. La media corretta è 21,70.
precisione: | $(BIN)
	$(CC) -O2 -o $(BIN)/meteo-malloc $(MALLOC)
	@for n in 1000000 5000000; do \
	  echo; echo "=== $$n stazioni a 21,7 gradi"; \
	  { echo $$n; yes 21.7 | head -n $$n; } > $(BIN)/sensori.txt; \
	  ./$(BIN)/meteo-malloc < $(BIN)/sensori.txt | grep media; \
	done

soluzione: | $(BIN)
	$(CC) -std=c99 -g -Wall -Wextra -O2 -o $(BIN)/soluzione soluzione/meteo.c
	@for f in input/*.txt; do \
	  echo; echo "=== $$f"; ./$(BIN)/soluzione < $$f | tail -3; \
	done

therac: | $(BIN)
	$(CC) -Wall -Wextra -fsanitize=undefined -o $(BIN)/therac therac25/contatore.c
	./$(BIN)/therac

clean:
	rm -rf $(BIN)
