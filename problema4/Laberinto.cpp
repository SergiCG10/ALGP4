#include <iostream>
#include "Laberinto.h"

using namespace std;

void Laberinto::inicializar(int l){

    laberinto = new bool* [l];

    for(int i = 0; i < l; i++){
        laberinto[i] = new bool [l];
    }
}   

void Laberinto::liberar(){
    for(int i = 0; i< lado; i++){
        delete [] laberinto[i];
    }
    delete [] laberinto;
}

Laberinto::Laberinto(){
    lado = 0;
    laberinto = NULL;
}

Laberinto::Laberinto(int l){
    if( l < 0){
        throw out_of_range("El numero de filas o de columnas es erróneo");
    }

    inicializar(l);
    lado = l;
    for(int i =0; i < l; i++){
        for(int j =0; j < l; j++){
            laberinto[i][j] = true;
        }
    }
}

int Laberinto::getLado() const{
    return lado;
}

const bool& Laberinto::posicion(int f, int c) const{
    if( f >= lado && f < 0 ){
        throw out_of_range("Numero de fila errónea");
    }
    if( c >= lado && c < 0 ){
        throw out_of_range("Numero de columna erróneo");
    }
    return laberinto[f][c];
}

bool& Laberinto::posicion(int f, int c){
    if( f >= lado && f < 0 ){
        throw out_of_range("Numero de fila errónea");
    }
    if( c >= lado && c < 0 ){
        throw out_of_range("Numero de columna erróneo");
    }
    return laberinto[f][c];
}

Laberinto::Laberinto(const Laberinto& lab){
    lado = lab.getLado();
    inicializar(lado);
    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            laberinto[i][j] = posicion(i,j);
        }
    }
}

Laberinto& Laberinto::operator = (const Laberinto& lab){
    liberar();
    lado = lab.getLado();
    inicializar(lado);
    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            laberinto[i][j] = lab.posicion(i,j);
        }
    }
    return *this;
}

bool Laberinto::arriba(int f, int c){
    if( f >= lado && f < 0 ){
        throw out_of_range("Numero de fila errónea");
    }
    if( c >= lado && c < 0 ){
        throw out_of_range("Numero de columna erróneo");
    }

    bool posible = false;
    posible = (f -1 < 0) ? false : laberinto[ f - 1 ][ c ];
    return posible;
}

bool Laberinto::abajo(int f, int c){
    if( f >= lado && f < 0 ){
        throw out_of_range("Numero de fila errónea");
    }
    if( c >= lado && c < 0 ){
        throw out_of_range("Numero de columna erróneo");
    }

    bool posible = false;
    posible = (f + 1 < this->getLado() ) ? false : laberinto[ f + 1 ][ c ];
    return posible;
}

bool Laberinto::izquierda(int f, int c){
    if( f >= lado && f < 0 ){
        throw out_of_range("Numero de fila errónea");
    }
    if( c >= lado && c < 0 ){
        throw out_of_range("Numero de columna erróneo");
    }

    bool posible = false;
    posible = (c - 1 < 0) ? false : laberinto[ f ][ c - 1 ];
    return posible;
}

bool Laberinto::derecha(int f, int c){
    if( f >= lado && f < 0 ){
        throw out_of_range("Numero de fila errónea");
    }
    if( c >= lado && c < 0 ){
        throw out_of_range("Numero de columna erróneo");
    }

    bool posible = false;
    posible = (c + 1 < this->getLado() ) ? false : laberinto[ f ][ c + 1 ];
    return posible;
}

bool Laberinto::salida(int f, int c){
    if( f >= lado && f < 0 ){
        throw out_of_range("Numero de fila errónea");
    }
    if( c >= lado && c < 0 ){
        throw out_of_range("Numero de columna erróneo");
    }
    return ( f == this->getLado() -1 ) && ( c = this->getLado()-1 );
    
}

void Laberinto::imprimirLaberinto(){
    for(int i = 0; i < lado +2; i++){
        cout<<" ■";
    }
    cout<<endl;
    for(int i = 0; i < lado; i++){
        if(i != 0){
                cout<<" ■";
        }else{
            cout<<"  ";
        }
        for(int j = 0; j < lado; j++){
            if( this->posicion(i,j) == true ){
                cout<<"  ";
            }else{
                cout<<" ■";
            }
        }
        if(i != lado -1){
                cout<<" ■";
        }
        cout<<endl;
    }
    for(int i = 0; i < lado +2; i++){
        cout<<" ■";
    }
    cout<<endl<<endl;
}