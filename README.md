# ALGP4

## makefile
# make
Este comando crea todos los ejecutables. Se debe de ejecutar en la carpeta ALGP4, al mismo nivel que la carpeta bin y las carpetas de cada problema.

# make ejemplos
Utilice este comando si desea de ver los ejemplos de ejecución para cada ejecutable dentro de la carpeta bin

# make clean
Utilice este comando para borrar todos los ejecutables y archivos.o dentro de la carpeta bin

## bin
En esta carpeta se guardan los ejecutables, y los archivos.o tras hacer make

## problema1
# problema1.cpp
Este archivo código del problema 1.
Nota: La satisfacción entre comensales se establece de forma psudoaleatoria a través de una semilla.

## problema2
# problema2.cpp
Este archivo contiene el código del problema 2 solucionado mediante backtracking.
Nota: La satisfacción entre comensales se establece de forma pseudoaleatoria a través de una semilla.

# problema2BnB.cpp
Este archivo contiene el código del problema 2 solucionado con branch and bound
Nota: La satisfacción entre comensales se establece de forma pseudoaleatoria a través de una semilla.

## problema3
# senku.cpp
Este archivo contiene el código para el problema 3. Con el ejecutable resultante se puede jugar al senku y resolver también el problema paso a paso.

# PasoAPaso.cpp
Este archivo contiene el código para el problema 3. Con el ejecutable resultante podemos ver la posición de un tablero de forma intermedia y su resolución posterior.

## problema4_5
En esta carpeta se encuentran la solución al problema 4 y al 5, para los que se utilizan los archivos Laberinto.h y Laberinto.cpp, que almacenan el código de la clase Laberinto utilizada para la resolución de los ejercicios.

# problema4.cpp
Este archivo contiene la solución al problema 4, resuelto mediante backtracking, haciendo una exploración en profundidad y dando como solución el primer camino que se encuentre que resuelva el laberinto.

# problema5.cpp
Este archivo contiene la solución al problema 5, resueltro mediante branch and bound. Cuando encontramos una solución no nos detenemos, y continuaremos buscando una solución mejor explorando todos los nodos mientras que la distancia mínima obtenida hasta la solución, sea mayor que la distancia recorrida por las ramificaciones que estamos recorriendo, obteniendo tras la exploración el camino más corto.