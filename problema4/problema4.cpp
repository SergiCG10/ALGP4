#include <iostream>

#include "Laberinto.h"

using namespace std;

int main(){
    Laberinto lab(10);

    lab.posicion(1,1) = false;
    lab.posicion(1,2) = false;
    lab.posicion(1,4) = false;
    lab.posicion(1,6) = false;
    lab.posicion(1,7) = false;
    lab.posicion(1,8) = false;
    lab.posicion(2,1) = false;
    lab.posicion(2,4) = false;
    lab.posicion(2,8) = false;
    lab.posicion(3,1) = false;
    lab.posicion(3,3) = false;
    lab.posicion(3,4) = false;
    lab.posicion(3,5) = false;
    lab.posicion(3,6) = false;
    lab.posicion(3,7) = false;
    lab.posicion(3,8) = false;
    lab.posicion(4,1) = false;
    lab.posicion(4,3) = false;
    lab.posicion(5,1) = false;
    lab.posicion(5,5) = false;
    lab.posicion(5,7) = false;
    lab.posicion(5,8) = false;
    lab.posicion(5,9) = false;
    lab.posicion(6,1) = false;
    lab.posicion(6,3) = false;
    lab.posicion(6,4) = false;
    lab.posicion(6,5) = false;
    lab.posicion(6,9) = false;
    lab.posicion(7,1) = false;
    lab.posicion(7,5) = false;
    lab.posicion(7,7) = false;
    lab.posicion(8,1) = false;
    lab.posicion(8,3) = false;
    lab.posicion(8,5) = false;
    lab.posicion(8,7) = false;
    lab.posicion(8,8) = false;
    lab.posicion(8,9) = false;
    lab.posicion(9,5) = false;
    lab.imprimirLaberinto();
}
