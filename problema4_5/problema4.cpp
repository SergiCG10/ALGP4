#include <iostream>

#include "Laberinto.h"

using namespace std;

void operator <<( const ostream& os, const pair<int,int>& p){
    cout<<"["<<p.first<<", "<<p.second <<"]";
}

int main(){
    Laberinto lab(10);
    lab.setPosicion(1,1);
    lab.setPosicion(1,2)  ;
    lab.setPosicion(1,4)  ;
    lab.setPosicion(1,6)  ;
    lab.setPosicion(1,7)  ;
    lab.setPosicion(1,8)  ;
    lab.setPosicion(2,1)  ;
    lab.setPosicion(2,4)  ;
    lab.setPosicion(2,8)  ;
    lab.setPosicion(3,1)  ;
    lab.setPosicion(3,3)  ;
    lab.setPosicion(3,4)  ;
    lab.setPosicion(3,5)  ;
    lab.setPosicion(3,6)  ;
    lab.setPosicion(3,7)  ;
    lab.setPosicion(3,8)  ;
    lab.setPosicion(4,1)  ;
    lab.setPosicion(4,3)  ;
    lab.setPosicion(5,1)  ;
    lab.setPosicion(5,5)  ;
    lab.setPosicion(5,7)  ;
    lab.setPosicion(5,8)  ;
    lab.setPosicion(5,9)  ;
    lab.setPosicion(6,1)  ;
    lab.setPosicion(6,3)  ;
    lab.setPosicion(6,4)  ;
    lab.setPosicion(6,5)  ;
    lab.setPosicion(6,9)  ;
    lab.setPosicion(7,1)  ;
    lab.setPosicion(7,5)  ;
    lab.setPosicion(7,7)  ;
    lab.setPosicion(8,1)  ;
    lab.setPosicion(8,3)  ;
    lab.setPosicion(8,5)  ;
    lab.setPosicion(8,7)  ;
    lab.setPosicion(8,8)  ;
    lab.setPosicion(8,9)  ;
    lab.setPosicion(9,5)  ;
    lab.imprimirLaberinto();

    lab.saveLaberinto("prueba.pbm");
    Laberinto cargado;
    cargado.loadLaberinto("prueba.pbm");
    cargado.imprimirLaberinto();
    
}
