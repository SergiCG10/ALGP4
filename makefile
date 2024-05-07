CXX = g++
BIN_DIR = ./bin
FLAGS = -std=c++17

PROBLEMAS = problema1 problema2 problema2BnB problema3 problema3PasoAPaso problema4 problema5 generarLaberintos

all: $(PROBLEMAS)

#Regla de construcción para problema1
problema1: $(BIN_DIR)/problema1.bin

$(BIN_DIR)/problema1.bin: problema1/problema1.cpp
	$(CXX) $(FLAGS) -o $@ $^


#Regla de construcción para problema2
problema2: $(BIN_DIR)/problema2.bin

$(BIN_DIR)/problema2.bin: problema2/problema2.cpp
	$(CXX) $(FLAGS) -o $@ $^


#Regla de construcción para problema2BnB
problema2BnB: $(BIN_DIR)/problema2BnB.bin

$(BIN_DIR)/problema2BnB.bin: problema2/problema2BnB.cpp
	$(CXX) $(FLAGS) -o $@ $^


#Regla de construcción para problema3
problema3: $(BIN_DIR)/problema3.bin

$(BIN_DIR)/problema3.bin: problema3/senku.cpp
	$(CXX) $(FLAGS) -o $@ $^


#Regla de construcción para problema3PasoAPaso
problema3PasoAPaso: $(BIN_DIR)/problema3PasoAPaso.bin

$(BIN_DIR)/problema3PasoAPaso.bin: problema3/PasoAPaso.cpp
	$(CXX) $(FLAGS) -o $@ $^


# Regla de construcción para Laberinto.o
$(BIN_DIR)/Laberinto.o: problema4_5/Laberinto.cpp problema4_5/Laberinto.h
	$(CXX) $(FLAGS) -o $@ -c $<


# Regla de construcción para problema4
problema4: $(BIN_DIR)/problema4.bin

$(BIN_DIR)/problema4.bin: problema4_5/problema4.cpp $(BIN_DIR)/Laberinto.o
	$(CXX) $(FLAGS) -o $@ $^
	

# Regla de construcción para generarLaberintos
generarLaberintos: $(BIN_DIR)/generarLaberintos.bin

$(BIN_DIR)/generarLaberintos.bin: problema4_5/generarLaberintos.cpp $(BIN_DIR)/Laberinto.o
	$(CXX) $(FLAGS) -o $@ $^


# Regla de construcción para problema5
problema5: $(BIN_DIR)/problema5.bin

$(BIN_DIR)/problema5.bin: problema4_5/problema5.cpp $(BIN_DIR)/Laberinto.o
	$(CXX) $(FLAGS) -o $@ $^


#Ejemplos de ejecución 
	make ejemplos
	
ejemplos:
	@echo
	@echo "Problema 1\n"
	@echo "\tPara el problema1, pruebe a ejecutar: \n\t\t./bin/problema1.bin 12345 4\n"
	@echo "\tOtro ejemplo: \n\t\t./bin/problema1.bin 33 14\n"
	@echo "\t(Nota: Para valores mayores de 14 la duración de la ejecución crece de forma exponencial)\n"
	@echo "Problema 2\n"
	@echo "\tPara el problema2, pruebe a ejecutar este caso con branch and bound: \n\t\t./bin/problema2BnB.bin 12345 15\n"
	@echo "\tOtro ejemplo \n\t\t./bin/problema2BnB.bin 12345 30\n"
	@echo "\tOtro ejemplo pero sin branch and bound: \n\t\t./bin/problema2.bin 12345 15\n"
	@echo "Problema 3\n"
	@echo "\tPara el problema3 pruebe a ejecutar: \n\t\t./bin/problema3.bin\n"
	@echo "\t\tDespués de esto, añada "2" para que se resuelva el tablero paso a paso"
	@echo "\n\tPara ver la búsqueda de la solución desde una posición intermedia, ejecute así: \n\t\t./bin/problema3PasoAPaso.bin\n"
	@echo "\t\tDespués de esto, añada "2" para que se resuelva el tablero paso a paso\n"
	@echo "Problemas 4 y 5\n"
	@echo "\tProblema 4:\n"
	@echo "\t Para los problemas 4 y 5, la llamada es igual, utilice el programa ./bin/problema4.bin o ./bin/problema5.bin" 
	@echo "\t A continuación el archivo con el laberinto almacenado que se encuentran en la carpeta bin/laberintos"
	@echo "\t Si desea ver la ejecución añada un segundo parámetro "s" \n"
	@echo
	@echo "\t Para el problema4, pruebe a ejecutar así: \n\t\t./bin/problema4.bin bin/laberintos/ejemplo1\n" 
	@echo "\t Si desea que muestre el proceso para encontrar la solución ejecutelo así: \n\t\t./bin/problema4.bin bin/laberintos/ejemplo1 s\n"
	@echo 
	@echo "\t Otro ejemplo pero esta vez más grande: \n\t\t./bin/problema4.bin bin/laberintos/ejemploGrande\n"
	@echo
	@echo "\tProblema 5:\n"
	@echo "\t Para el problema5, pruebe a ejecutar así: \n\t\t./bin/problema5.bin bin/laberintos/ejemplo3\n"
	@echo "\t Si desea que muestre el proceso para encontrar la solución ejecutelo así: \n\t\t./bin/problema5.bin bin/laberintos/ejemplo3 s\n"
	@echo 
	@echo "\t Otro ejemplo pero esta vez más grande: \n\t\t./bin/problema5.bin bin/laberintos/ejemploGrande\n"
	@echo
	@echo "\t Un ejemplo con un laberinto sin solución: \n\t\t./bin/problema4.bin bin/laberintos/ejemplo2"
	@echo "\t\t./bin/problema5.bin bin/laberintos/ejemplo2\n"
	@echo 
	@echo "\t Si desea probar más ejemplos dentro de la carpeta bin/laberintos/ encontrará más ejemplos para la ejecución de ambos programas"
	@echo "\t Tan solo sustituya nombreDelEjemplo por los laberintos de la carpeta mencionada anteriormente:"
	@echo
	@echo "\t\t./bin/problema4.bin bin/laberintos/nombreDelEjemplo para el problema 4"
	@echo "\t\t./bin/problema5.bin bin/laberintos/nombreDelEjemplo para el problema 5"
	@echo "\t(Nota: Si desea ver el proceso añada "s" como segundo parámetro a ambos)"
	@echo
# Regla para limpiar
clean:
	rm -rf $(BIN_DIR)/*.bin $(BIN_DIR)/*.o

.PHONY: all clean ejemplos
