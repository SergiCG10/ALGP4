#ifndef Laberinto
#define _LABERINTO

#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief Clase Laberinto. Utilizada para representar un laberinto con funciones auxiliares para su construcción y resolución
 *
 * @param laberinto. Matriz booleana que contendrá el laberinto (cuadrada según el enunciado). True para valores donde se puede pasar, false para los que no
 * @param recorridos. Matriz del mismo tamaño que el laberinto que indica si las casillas han sido recorridas o no, 0 para no, 1 para sí, -1 si son un muro
 * @param lado. Lado del laberinto cuadrado
 * @param posicionActual. Posicion actual del recorrido
 */
class Laberinto{
    private:

        bool** laberinto;
        int** recorridos;
        int lado;
        pair<int,int> posicionActual;

        /**
         * @brief Funcion privada inicializar. Inicializa el laberinto con f filas y columnas
         *
         * @param l. Lado de la matriz cuadrada
         */
        void inicializar(int l);

        /**
         * @brief Funcion liberar. Libera la memoria de la matriz
         */
        void liberar();

    public:    

        /**
         * @brief Constructor por defecto de la clase laberinto. Crea un laberinto vacío, con 0 filas y 0 columnas
         */
        Laberinto();

        /**
         * @brief Constructor por parámetro de la clase laberinto. Crea un laberinto con f filas y c columnas, con todas las posiciones a true (recorribles)
         *
         * @param l. Lado de la matriz cuadrada
         *
         */
        Laberinto(int l);

        /**
         * @brief Funcion getLado. Devuelve el tamaño del lado de la matriz cuadrada
         */
        int getLado() const;

        /**
         * @brief Funcion posicion. Devuelve la posicion actual. Función getter
         */
        const pair<int,int>& getPosicionActual() const;

        /**
         * @brief Funcion posicion. Establece la posicion actual. Función setter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        void setPosicionActualTo(pair<int,int> p);

        /**
         * @brief Funcion posicion. Devuelve el valor de una casilla (f,c). Función getter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        const bool& getPosicion(int f, int c) const;

        /**
         * @brief Funcion posicion. Establece el valor de una casilla (f,c). Función setter
         * Si el valor el false (una pared), en la matriz de recorridos lo ponemos como -1, si es al contrario
         * lo ponemos a 0 (camino)
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         * @param valor. Valor para la posición
         */
        void setPosicion(int f, int c, bool valor = false);

        /**
         * @brief Funcion recorrida. Devuelve si una casilla (f,c) ha sido recorrida  o es pared (0 no recorrida, 1 si recorrida, -1 es pared). Función getter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        const int& recorrida(int f, int c) const;

        /**
         * @brief Funcion recorrido. Devuelve si una casilla (f,c) ha sido recorrida o es pared (0 no recorrida, 1 si recorrida, -1 es pared). Función setter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        int& recorrida(int f, int c);

        /**
         * @brief Constructor de copia de la clase laberinto. Crea un laberinto a partir de otro.
         *
         * @param lab. Laberinto del que copiar el nuestro
         */
        Laberinto(const Laberinto& lab);

        /**
         * @brief Operador de asignación, copia un laberinto en otro.   
         *
         * @param lab. Laberinto del que copiar el nuestro
         */
        Laberinto& operator = (const Laberinto& lab);

        /**
         * @brief Funcion arriba. Devuelve si a partir de la posición actual podemos ir hacia arriba, en caso afirmativo, la posición actual cambia
         */
        bool arriba();

        /**
         * @brief Funcion arriba. Devuelve si a partir de la posición actual podemos ir hacia abajo, en caso afirmativo, la posición actual cambia
         */ 
        bool abajo(); 

        /**
         * @brief Funcion izquierda. Devuelve si a partir de la posición actual podemos ir hacia la izquierda, en caso afirmativo, la posición actual cambia
         */
        bool izquierda(); 

        /**
         * @brief Funcion derecha. Devuelve si a partir de la posición actual podemos ir hacia la derecha, en caso afirmativo, la posición actual cambia
         */
        bool derecha();

        /**
         * @brief Funcion salida. Determina si estás en la salida o no a partir de la posicion actual
         */
        bool salida();

        /**
         *
         */
        void loadLaberinto(string fichero);

        /**
         *
         */
        void saveLaberinto(string fichero);
        /**
         * @brief Funcion imprimirLaberinto. Imprime el laberinto por pantalla
         */
        void imprimirLaberinto();

        void imprimirLaberintoRecorrido();
};

#endif 