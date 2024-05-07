# ALGP4
A continuación mostramos el uso del **makile** y añadimos un breve resumen de los archivos que se encuentran dentro de cada una de las carpetas

## :hammer: makefile
### comando _"make"_
El comando _"make"_ crea todos los ejecutables. Se debe de ejecutar en la carpeta ALGP4, al mismo nivel que la carpeta bin y las carpetas de cada problema.

### comando _"make ejemplos"_
El comando _"make ejemplos"_ muestra los ejemplos de ejecución para cada ejecutable dentro de la carpeta bin

### comando _"make clean"_
El comando _"make clean"_ sirve para borrar todos los ejecutables y archivos.o dentro de la carpeta bin

## :file_folder: bin
En esta carpeta se guardan los ejecutables, y los archivos.o tras hacer make
### :file_folder: laberintos
Dentro de esta carpeta se encuentran todos los laberintos que hemos creado de **ejemplo** para la ejecución de los problemas 4 y 5.

## :file_folder: problema1
### :page_facing_up: problema1.cpp
Este archivo código del **problema 1**.

>_Nota: La satisfacción entre comensales se establece de forma pseudoaleatoria a través de una semilla._

## :file_folder: problema2
### :page_facing_up: problema2.cpp
Este archivo contiene el código del **problema 2** solucionado mediante backtracking.

>_Nota: La satisfacción entre comensales se establece de forma pseudoaleatoria a través de una semilla._

### :page_facing_up: problema2BnB.cpp
Este archivo contiene el código del **problema 2** solucionado con _branch and bound_. 

>_Nota: La satisfacción entre comensales se establece de forma pseudoaleatoria a través de una semilla._

## :file_folder: problema3
### :page_facing_up: senku.cpp
Este archivo contiene el código para el problema 3. Con el ejecutable resultante se puede jugar al senku y resolver también el problema paso a paso.

### :page_facing_up: PasoAPaso.cpp
Este archivo contiene el código para el problema 3. Con el ejecutable resultante podemos ver la posición de un tablero de forma intermedia y su resolución posterior.

## :file_folder: problema4_5
En esta carpeta se encuentran la solución al problema 4 y al 5, para los que se utilizan los archivos Laberinto.h y Laberinto.cpp, que almacenan el código de la clase Laberinto utilizada para la resolución de los ejercicios.

>_Nota: El ejecutable del problema 4 en general es el más rápido para todos los casos, sobre todo cuando no hay solución._

### :page_facing_up: generarLaberintos.cpp
Este archivo se trata de un archivo auxiliar para crear los laberintos que sirven de ejemplo para tanto el problema 4 como para el problema 5.

### :page_facing_up: problema4.cpp
Este archivo contiene la solución al problema 4, resuelto mediante backtracking, haciendo una exploración en profundidad y dando como solución el primer camino que se encuentre que resuelva el laberinto.

>_Nota: El camino resultante no tiene por qué ser el más corto._

### :page_facing_up: problema5.cpp
Este archivo contiene la solución al problema 5, resueltro mediante branch and bound. Cuando encontramos una solución no nos detenemos, y continuaremos buscando una solución mejor explorando todos los nodos mientras que la distancia mínima obtenida hasta la solución, sea mayor que la distancia recorrida por las ramificaciones que estamos recorriendo, obteniendo tras la exploración el camino más corto.

