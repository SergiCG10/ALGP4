> [!WARNING]
> Este fichero aún no ha sido cotejado ni terminado, por lo que puede contener erróres

# bin
>_Nota: Para ver todos los siguientes ejecutables, deberá de hacer make antes en la carpeta superior_.
### laberintos
Dentro de esta carpeta se encuentran todos los laberintos que hemos creado de **ejemplo** para la ejecución de los problemas 4 y 5.

## problema1.bin
Ejecutable del **problema 1**.

## problema2.bin
Ejecutable del **problema 2** usando backtracking.

## problema2BnB.bin
Ejecutable del **problema 2** usando _branch and bound_. 

## senku.bin
Este archivo contiene el código para el problema 3. Con el ejecutable resultante se puede jugar al senku y resolver también el problema paso a paso.

## PasoAPaso.bin
Este archivo contiene el código para el problema 3. Con el ejecutable resultante podemos ver la posición de un tablero de forma intermedia y su resolución posterior.

## generarLaberintos.bin
Este archivo se trata de un archivo auxiliar para crear los laberintos que sirven de ejemplo para tanto el problema 4 como para el problema 5.

## problema4.bin
Este archivo contiene la solución al problema 4, resuelto mediante backtracking, haciendo una exploración en profundidad y dando como solución el primer camino que se encuentre que resuelva el laberinto.

>_Nota: El camino resultante no tiene por qué ser el más corto._

## problema5.bin
Este archivo contiene la solución al problema 5, resueltro mediante branch and bound. Cuando encontramos una solución no nos detenemos, y continuaremos buscando una solución mejor explorando todos los nodos mientras que la distancia mínima obtenida hasta la solución, sea mayor que la distancia recorrida por las ramificaciones que estamos recorriendo, obteniendo tras la exploración el camino más corto.

