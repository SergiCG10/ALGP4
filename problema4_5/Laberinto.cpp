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

void Laberinto::setPosicionActualTo(pair<int,int> p){
    if(p.first < 0 || p.first >= this->getLado() || p.second < 0 || p.second >= this->getLado()){
        throw out_of_range("setPosicionActualTo::Valor de fila o de columna erróneo");
    }
    recorridos[p.first][p.second] = 1;
    posicionActual = p;
}

const bool& Laberinto::getPosicion(int f, int c) const{
    if(f < 0 || f >= this->getLado() || c < 0 || c >= this->getLado()){
        throw out_of_range("getPosicion::Valor de fila o de columna erróneo");
    }
    return laberinto[f][c];
}

void Laberinto::setPosicion(int f, int c, bool valor /**= false*/ ){
    if(f < 0 || f >= this->getLado() || c < 0 || c >= this->getLado()){
        throw out_of_range("setPosicion::Valor de fila o de columna erróneo");
    }
    if(valor == false){
        recorridos[f][c] = -1;
    }

    laberinto[f][c] = valor; 
}

const int& Laberinto::recorrida(int f, int c) const{
    if(f < 0 || f >= this->getLado() || c < 0 || c >= this->getLado()){
        throw out_of_range("recorrida::Valor de fila o de columna erróneo");
    }
    return recorridos[f][c];
}

int& Laberinto::recorrida(int f, int c){
    if(f < 0 || f >= this->getLado() || c < 0 || c >= this->getLado()){
        throw out_of_range("recorrida::Valor de fila o de columna erróneo");
    }
    return recorridos[f][c];
}

Laberinto::Laberinto(const Laberinto& lab){
    this->lado = lab.getLado();
    inicializar(lado);
    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            this->setPosicion(i,j, lab.getPosicion(i,j));
        }
    }
    posicionActual = lab.posicionActual;

    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            recorridos[i][j] = lab.recorridos[i][j];
        }
    }
}

Laberinto& Laberinto::operator = (const Laberinto& lab){
    liberar();
    this->lado = lab.getLado();
    inicializar(lado);
    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            setPosicion(i,j, lab.getPosicion(i,j));
        }
    }

    posicionActual = lab.posicionActual;

    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            recorridos[i][j] = lab.recorridos[i][j];
        }
    }

    return *this;
}

bool Laberinto::arriba(){
    bool posible = false;
    posible = (posicionActual.first -1 < 0 ) ? false : getPosicion(posicionActual.first - 1 , posicionActual.second ) && recorrida(posicionActual.first - 1, posicionActual.second) != 1;

    if(posible){

        setPosicionActualTo(make_pair(posicionActual.first - 1, posicionActual.second));
        recorrida(posicionActual.first, posicionActual.second ) = 1;
        
    }

    return posible;
}

bool Laberinto::abajo(){
    bool posible = false;
    posible = (posicionActual.first +1 >= this->getLado() ) ? false : getPosicion(posicionActual.first + 1 , posicionActual.second )&& recorrida(posicionActual.first + 1, posicionActual.second) != 1;

    if(posible){
        setPosicionActualTo( make_pair(posicionActual.first + 1, posicionActual.second));
        recorrida(posicionActual.first, posicionActual.second ) = 1;
        
    }

    return posible;
}

bool Laberinto::izquierda(){
    bool posible = false;
    posible = (posicionActual.second -1 < 0) ? false : getPosicion(posicionActual.first, posicionActual.second - 1 )&& recorrida(posicionActual.first, posicionActual.second-1) != 1;

    if(posible){
        setPosicionActualTo( make_pair(posicionActual.first, posicionActual.second -1 ));
        recorrida(posicionActual.first, posicionActual.second ) = 1;
        
    }

    return posible;
}

bool Laberinto::derecha(){
    bool posible = false;
    posible = (posicionActual.second +1 >= this->getLado() ) ? false : getPosicion(posicionActual.first, posicionActual.second + 1 )&& recorrida(posicionActual.first, posicionActual.second + 1) != 1;

    if(posible){
        setPosicionActualTo( make_pair(posicionActual.first, posicionActual.second +1));
        recorrida(posicionActual.first, posicionActual.second ) = 1;
        
    }

    return posible;
}

bool Laberinto::salida(){
    return ( posicionActual.first == this->getLado() -1 ) && ( posicionActual.second == this->getLado()-1 );
}

void Laberinto::loadLaberinto(string fichero){

    liberar();
    ifstream f(fichero);
    int lado = 0;
    
    
    if(f){
        f >> lado;
    }else{
        cerr<< "Error al abrir el fichero de entrada"<<endl;
        
    }

    if(lado <= 0){
        throw out_of_range("Error, el lado del laberinto almacenado en el fichero es erróneo");
    }
    
    inicializar(lado);
    this->lado = lado;
    posicionActual = make_pair(0,0);
    recorrida(0,0) = 1;
    bool aux;
    for(int i =0 ; i< lado; i++){
        for(int j = 0; j < lado; j++){
            f>> aux;
            this->setPosicion(i,j, aux);
        }
    }
    f.close();
}

void Laberinto::saveLaberinto(string fichero){

    ofstream f(fichero);

    if(f){
        f << this->getLado();
        f <<endl;
        for(int i = 0; i < this->getLado(); i++){
            for(int j = 0; j < this->getLado(); j++){
                f << getPosicion(i,j) << " ";
            }
        }
    }
    f.close();
}

void Laberinto::imprimirLaberinto(){
    if(this->lado >1){
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
    }else{
        cout<<"El tamaño del laberinto es demasiado pequeño, o es 0"<<endl;
    }
    
}

void Laberinto::imprimirLaberintoRecorrido(){
    if(this->lado > 1){
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
                if( this->recorrida(i,j) == 0 ){
                    cout<<"  ";
                }else if( this->recorrida(i,j) == -1){
                    cout<<" ■";
                }else{
                    cout<<" □";
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
    }else{
        cout<<"El tamaño del laberinto es demasiado pequeño, o es 0"<<endl;
    }
    
}