# bin
>_Nota: Para ver todos los siguientes ejecutables, deberá de hacer make antes en la carpeta superior_.
## :file_folder: laberintos
Dentro de esta carpeta se encuentran todos los laberintos que hemos creado de **ejemplo** para la ejecución de los problemas 4 y 5.

## :gear: problema1.bin
Ejecutable del **problema 1**.

Ejecución: 
    
    ./problema1.bin \<semilla> \<numero de personas>

Ejemplo:

    ./problema1.bin 12345 14

## :gear: problema2.bin
Ejecutable del **problema 2** usando backtracking.

Ejecución: 
    
    ./problema2.bin \<semilla> \<numero de personas>

Ejemplo:

    ./problema2.bin 12345 10

## :gear: problema2BnB.bin
Ejecutable del **problema 2** usando _branch and bound_. 

Ejecución: 
    
    ./problema2BnB.bin \<semilla> \<numero de personas>

Ejemplo:

    ./problema2BnB.bin 12345 30
## :gear: problema3.bin
Este archivo contiene el código para el problema 3. Con el ejecutable resultante se puede jugar al senku y resolver también el problema paso a paso.
    
Ejecución: 

    ./problema3.bin

## :gear: problema3PasoAPaso.bin
Este archivo contiene el código para el problema 3. Con el ejecutable resultante podemos ver la posición de un tablero de forma intermedia y su resolución posterior.

Ejecución:
 
    ./problema3PasoAPaso.bin

## :gear: generarLaberintos.bin
Este archivo se trata de un archivo auxiliar para crear los laberintos que sirven de ejemplo para tanto el problema 4 como para el problema 5.

Ejecución: 
    
    ./generarLaberintos.bin

## :gear: problema4.bin
Este archivo contiene la solución al problema 4, resuelto mediante backtracking, haciendo una exploración en profundidad y dando como solución el primer camino que se encuentre que resuelva el laberinto.

>_Nota: El camino resultante no tiene por qué ser el más corto._

Ejecución: 
    
    ./problema4.bin \<nombre del fichero de laberinto> | opcional \<s>

>Opcion s: Añadala si desea que muestre el proceso de obtención del resultado 

Ejemplo:

    ./problema4.bin laberintos/ejemplo1 s

## :gear: problema5.bin
Este archivo contiene la solución al problema 5, resueltro mediante branch and bound. Cuando encontramos una solución no nos detenemos, y continuaremos buscando una solución mejor explorando todos los nodos mientras que la distancia mínima obtenida hasta la solución, sea mayor que la distancia recorrida por las ramificaciones que estamos recorriendo, obteniendo tras la exploración el camino más corto.
    
Ejecución: 

    ./problema5.bin \<nombre del fichero de laberinto> | opcional \<s>

>Opcion s: Añadala si desea que muestre el proceso de obtención del resultado 

Ejemplo:

    ./problema5.bin laberintos/ejemplo2 s