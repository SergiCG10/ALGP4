#ifndef Laberinto
#define _LABERINTO

/**
 * @brief Clase Laberinto. Utilizada para representar un laberinto con funciones auxiliares para su construcción y resolución
 *
 * @param laberinto. Matriz booleana que contendrá el laberinto (cuadrada según el enunciado). True para valores donde se puede pasar, false para los que no
 * @param filas. Numero de filas del laberinto
 * @param columnas. Numero de columnas del laberinto
 */
class Laberinto{
    private:

        bool** laberinto;
        int lado;

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
         * @brief Funcion posicion. Devuelve el valor de la posicion (f,c). Función getter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        const bool& posicion(int f, int c) const;

        /**
         * @brief Funcion posicion. Devuelve una referencia a la posicion (f,c). Función setter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        bool& posicion(int f, int c);

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
         * @brief Funcion arriba. Devuelve si a partir de la posición pasada por parámetro podemos ir hacia arriba
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        bool arriba(int f, int c);

        /**
         * @brief Funcion abajo. Devuelve si a partir de la posición pasada por parámetro podemos ir hacia abajo
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */ 
        bool abajo(int f, int c); 

        /**
         * @brief Funcion izquierda. Devuelve si a partir de la posición pasada por parámetro podemos ir hacia la izquierda
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        bool izquierda(int f, int c); 

        /**
         * @brief Funcion derecha. Devuelve si a partir de la posición pasada por parámetro podemos ir hacia la derecha
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        bool derecha(int f, int c); 

        /**
         * @brief Funcion salida. Determina si estás en la salida o no
         *
         * @param f. Fila de la posición de la que comprobar
         * @param c. Columna de la posicón de la que comprobar
         */
        bool salida(int f, int c);

        /**
         * @brief Funcion imprimirLaberinto. Imprime el laberinto por pantalla
         */
        void imprimirLaberinto();

};

#endif 