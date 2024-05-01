CXX = g++
BIN_DIR = ./bin
FLAGS = -std=c++17

PROBLEMAS = problema2 problema4 problema5 generarLaberintos

all: $(PROBLEMAS)

#Regla de construcción para problema1
problema1: $(BIN_DIR)/problema1.bin

$(BIN_DIR)/problema1.bin: problema1/problema1.cpp
	$(CXX) $(FLAGS) -o $@ $^

#Regla de construcción para problema2
problema2: $(BIN_DIR)/problema2.bin

$(BIN_DIR)/problema2.bin: problema2/problema2.cpp
	$(CXX) $(FLAGS) -o $@ $^

#Regla de construcción para problema3
problema3: $(BIN_DIR)/problema3.bin

$(BIN_DIR)/problema3.bin: problema3/problema3.cpp
	$(CXX) $(FLAGS) -o $@ $^

# Regla de construcción para problema4
problema4: $(BIN_DIR)/problema4.bin

$(BIN_DIR)/problema4.bin: problema4_5/problema4.cpp $(BIN_DIR)/Laberinto.o
	$(CXX) $(FLAGS) -o $@ $^

# Regla de construcción para Laberinto.o
$(BIN_DIR)/Laberinto.o: problema4_5/Laberinto.cpp problema4_5/Laberinto.h
	@mkdir -p $(BIN_DIR)
	$(CXX) $(FLAGS) -o $@ -c $<
	
# Regla de construcción para problema4
generarLaberintos: $(BIN_DIR)/generarLaberintos.bin

$(BIN_DIR)/generarLaberintos.bin: problema4_5/generarLaberintos.cpp $(BIN_DIR)/Laberinto.o
	$(CXX) $(FLAGS) -o $@ $^

# Regla de construcción para Laberinto.o
$(BIN_DIR)/Laberinto.o: problema4_5/Laberinto.cpp problema4_5/Laberinto.h
	@mkdir -p $(BIN_DIR)
	$(CXX) $(FLAGS) -o $@ -c $<

# Regla de construcción para problema5
problema5: $(BIN_DIR)/problema5.bin

$(BIN_DIR)/problema5.bin: problema4_5/problema5.cpp
	$(CXX) $(FLAGS) -o $@ $^

#Ejemplos de ejecución 
	@echo
	@echo Para el problema2, pruebe a ejecutar: ./bin/problema2.bin 12345 4 
	@echo Para el problema2, pruebe a ejecutar: ./bin/problema2.bin 12345 6
	@echo
ejemplos:
	@echo
	@echo Para el problema2, pruebe a ejecutar: ./bin/problema2.bin 12345 4 
	@echo Para el problema2, pruebe a ejecutar: ./bin/problema2.bin 12345 6
	@echo
# Regla para limpiar
clean:
	rm -rf $(BIN_DIR)/*.bin $(BIN_DIR)/*.o

.PHONY: all clean ejemplos
