#include <iostream>

#include "Laberinto.h"

using namespace std;

void Laberinto::inicializar(int l){

    laberinto = new bool* [l];

    for(int i = 0; i < l; i++){
        laberinto[i] = new bool [l];
    }

    recorridos = new int* [l];

    for(int i = 0; i < l; i++){
        recorridos[i] = new int [l];
    }
}   

void Laberinto::liberar(){
    for(int i = 0; i< lado; i++){
        delete [] laberinto[i];
    }
    delete [] laberinto;

    for(int i = 0; i< lado; i++){
        delete [] recorridos[i];
    }
    delete [] recorridos;
}

Laberinto::Laberinto(){
    lado = 0;
    laberinto = NULL;
    posicionActual = make_pair(0,0);
}

Laberinto::Laberinto(int l){
    if( l < 0){
        throw out_of_range("El numero de filas o de columnas es erróneo");
    }

    inicializar(l);
    lado = l;
    posicionActual = make_pair(0,0);
    

    for(int i =0; i < l; i++){
        for(int j =0; j < l; j++){
            laberinto[i][j] = true;
        }
    }

    for(int i =0; i < l; i++){
        for(int j =0; j < l; j++){
            recorridos[i][j] = 0;
        }
    }
    recorridos[0][0] = 1;
}

int Laberinto::getLado() const{
    return lado;
}

const pair<int,int>& Laberinto::getPosicionActual() const{
    return posicionActual;
}

void Laberinto::setPosicionActualTo(int f, int c){
    if(f < 0 || f >= this->getLado() || c < 0 || c >= this->getLado()){
        throw out_of_range("Valor de fila o de columna erróneo");
    }
    posicionActual = make_pair(f,c);
}

const bool& Laberinto::getPosicion(int f, int c) const{
    if(f < 0 || f >= this->getLado() || c < 0 || c >= this->getLado()){
        throw out_of_range("Valor de fila o de columna erróneo");
    }
    return laberinto[f][c];
}

void Laberinto::setPosicion(int f, int c, bool valor /**= false*/ ){
    if(f < 0 || f >= this->getLado() || c < 0 || c >= this->getLado()){
        throw out_of_range("Valor de fila o de columna erróneo");
    }
    if( valor == false){
        recorridos[f][c] = -1;
    }else{
        recorridos[f][c] = 0;
    }
    laberinto[f][c] = valor; 
}

const int& Laberinto::recorrida(int f, int c) const{
    if(f < 0 || f >= this->getLado() || c < 0 || c >= this->getLado()){
        throw out_of_range("Valor de fila o de columna erróneo");
    }
    return recorridos[f][c];
}

int& Laberinto::recorrida(int f, int c){
    if(f < 0 || f >= this->getLado() || c < 0 || c >= this->getLado()){
        throw out_of_range("Valor de fila o de columna erróneo");
    }
    return recorridos[f][c];
}

Laberinto::Laberinto(const Laberinto& lab){
    lado = lab.getLado();
    inicializar(lado);
    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            laberinto[i][j] = lab.getPosicion(i,j);
        }
    }

    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            recorridos[i][j] = lab.recorridos[i][j];
        }
    }
    posicionActual = lab.posicionActual;
}

Laberinto& Laberinto::operator = (const Laberinto& lab){
    liberar();
    lado = lab.getLado();
    inicializar(lado);
    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            laberinto[i][j] = lab.getPosicion(i,j);
        }
    }

    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            recorridos[i][j] = lab.recorridos[i][j];
        }
    }
    posicionActual = lab.posicionActual;

    return *this;
}

bool Laberinto::arriba(){
    bool posible = false;
    posible = (posicionActual.first -1 < 0 ) ? false : getPosicion(posicionActual.first - 1 , posicionActual.second );

    if(posible){
        setPosicionActualTo(posicionActual.first - 1, posicionActual.second);
        recorrida(posicionActual.first, posicionActual.second ) = 1;
    }

    return posible;
}

bool Laberinto::abajo(){
    bool posible = false;
    posible = (posicionActual.first +1 >= this->getLado() ) ? false : getPosicion(posicionActual.first + 1 , posicionActual.second );

    if(posible){
        setPosicionActualTo(posicionActual.first + 1, posicionActual.second);
        recorrida(posicionActual.first, posicionActual.second ) = 1;
    }

    return posible;
}

bool Laberinto::izquierda(){
    bool posible = false;
    posible = (posicionActual.second -1 < 0) ? false : getPosicion(posicionActual.first, posicionActual.second - 1 );

    if(posible){
        setPosicionActualTo(posicionActual.first, posicionActual.second -1 );
        recorrida(posicionActual.first, posicionActual.second ) = 1;
    }

    return posible;
}

bool Laberinto::derecha(){
    bool posible = false;
    posible = (posicionActual.second +1 >= this->getLado() ) ? false : getPosicion(posicionActual.first, posicionActual.second + 1 );

    if(posible){
        setPosicionActualTo(posicionActual.first, posicionActual.second +1);
        recorrida(posicionActual.first, posicionActual.second ) = 1;
    }

    return posible;
}

bool Laberinto::salida(){
    return ( posicionActual.first == this->getLado() -1 ) && ( posicionActual.second = this->getLado()-1 );
}

void Laberinto::imprimirLaberinto(){
    cout<<endl;
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
            if( this->getPosicion(i,j) == true ){
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
void Laberinto::imprimirLaberintoRecorrido(){
    for(int i = 0; i < lado +2; i++){
        cout<<" ■";
    }
    cout<<endl;
    for(int i = 0; i < lado; i++){
        cout<<" ■";
        for(int j = 0; j < lado; j++){
            if( this->recorrida(i,j) == 0 ){
                cout<<"  ";
            }else if( this->recorrida(i,j) == -1){
                cout<<" ■";
            }else{
                cout<<" ·";
            }
        }
        
        cout<<" ■";
        
        cout<<endl;
    }
    for(int i = 0; i < lado +2; i++){
        cout<<" ■";
    }
    cout<<endl<<endl;
}