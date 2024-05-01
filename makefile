CXX = g++
BIN_DIR = ./bin
FLAGS = -std=c++17

PROBLEMAS = problema2

# Regla de construcción para cada problema
$(BIN_DIR)/$(PROBLEMAS): $(PROBLEMAS)/$(PROBLEMAS).cpp
	$(CXX) $(FLAGS) -o $@.bin $<

# Regla de construcción para problema4
problema4: $(BIN_DIR)/problema4.bin

$(BIN_DIR)/problema4.bin: problema4_5/problema4.cpp $(BIN_DIR)/Laberinto.o
	$(CXX) $(FLAGS) -o $@ $^

# Regla de construcción para Laberinto.o
$(BIN_DIR)/Laberinto.o: problema4_5/Laberinto.cpp problema4_5/Laberinto.h
	@mkdir -p $(BIN_DIR)
	$(CXX) $(FLAGS) -o $@ -c $<

#Ejemplos de ejecución 
	@echo Para el problema2, pruebe a ejecutar: ./bin/problema2.bin 12345 4 
	@echo Para el problema2, pruebe a ejecutar: ./bin/problema2.bin 12345 6
# Regla para limpiar
clean:
	rm -rf $(BIN_DIR)/*.bin $(BIN_DIR)/*.o

.PHONY: all clean
