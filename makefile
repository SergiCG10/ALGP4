#Archivo makefile para la práctica 4 de Algorítmica

all:
	#Compilando Problema 1...
	#@g++ -o Problema1.bin Problema1.cpp -std=c++17

	#Compilando Problema 2...
	@g++ -o Problema2.bin Problema2.cpp -std=c++17
	
	#Ejecute de la siguiente manera: ./Problema2.bin 12345 10

	#Compilando Problema 3...
	#@g++ -o Problema3.bin Problema3.cpp -std=c++17

	#Compilando Problema 5...
	@g++ -o Problema5.bin Problema5.cpp -std=c++17
	
problema4: problema4/problema4.cpp problema4/Laberinto.o
	g++ -o problema4.bin problema4/problema4.cpp problema4/Laberinto.o -std=c++17

Laberinto.o: problema4/Laberinto.cpp problema4/Laberinto.h
	g++ -c problema4/Laberinto.o problema4/Laberinto.cpp

#Elimina los ejecutables
clean:
	#@rm Problema1.bin
	@rm Problema2.bin
	#@rm Problema3.bin
	@rm Problema4.bin
	@rm Laberinto.o
	@rm Problema5.bin
	
.PHONY: clean
