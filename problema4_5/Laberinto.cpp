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

Laberinto::Laberinto(int l, pair<int,int> ini /**= make_pair(0,0)*/, pair<int,int> fin /**= make_pair(-1, -1)*/){
    if( l < 0){
        throw out_of_range("El numero de filas o de columnas es erróneo");
    }

    inicializar(l);
    lado = l;
    inicio = ini;
    posicionActual = ini;
    if( fin.first == -1 && fin.second == -1){
        salida = make_pair(l-1,l-1);
    }else{
        salida = fin;
    }
    
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

const pair<int,int>& Laberinto::getPosicionInicial() const{
    return inicio;
}

void Laberinto::setPosicionInicialTo(pair<int,int> p){
    if(p.first < 0 || p.first >= this->getLado() || p.second < 0 || p.second >= this->getLado()){
        throw out_of_range("setPosicionInicialTo::Valor de fila o de columna erróneo");
    }
    recorridos[p.first][p.second] = 1;
    inicio = p;
}

const pair<int,int>& Laberinto::getPosicionFinal() const{
    return salida;
}

void Laberinto::setPosicionFinalTo(pair<int,int> p){
    if(p.first < 0 || p.first >= this->getLado() || p.second < 0 || p.second >= this->getLado()){
        throw out_of_range("setPosicionInicialTo::Valor de fila o de columna erróneo");
    }
    salida = p;
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
    this->inicio = lab.inicio;
    this->salida = lab.salida;
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

    this->inicio = lab.inicio;
    this->salida = lab.salida;
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

bool Laberinto::esSalida(){
    return ( posicionActual.first == salida.first  ) && ( posicionActual.second == salida.second );
}

bool Laberinto::esSalidaPos( pair<int,int> p ){
    return ( p.first == salida.first ) && ( p.second == salida.second );
}

void Laberinto::loadLaberinto(string fichero){

    liberar();
    ifstream f(fichero);
    int lado = 0;
    int posInicialF = 0, posInicialC = 0;
    int posFinalF = 0, posFinalC = 0;
    
    
    if(f){
        f >> lado;
        f >>  posInicialF >> posInicialC;
        f >> posFinalF >> posFinalC;

    }else{
        cerr<< "Error al abrir el fichero de entrada"<<endl;
        
    }

    if(lado <= 0){
        throw out_of_range("Error, el lado del laberinto almacenado en el fichero es erróneo");
    }
    
    inicializar(lado);
    this->lado = lado;
    inicio = make_pair(posInicialF,posInicialC);
    posicionActual = inicio;
    salida = make_pair(posFinalF, posFinalC);
    recorrida( posInicialF, posInicialC) = 1;
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
        f << inicio.first << " " << inicio.second <<endl;
        f << salida.first << " " << salida.second <<endl;
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
                if( i == getPosicionInicial().first && j == getPosicionInicial().second ){
                    cout<<" ●";
                }else if( i == getPosicionFinal().first && j == getPosicionFinal().second ){
                    
                    cout<<" ○";
                }else if( this->getPosicion(i,j) == true ){
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
        cout<<"Entrada: ●"<<endl;
        cout<<"Salida: ○"<<endl;
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
                if( i == getPosicionInicial().first && j == getPosicionInicial().second ){
                    cout<<" ●";
                }else if( i == getPosicionFinal().first && j == getPosicionFinal().second ){
                    
                    cout<<" ○";
                }else if( this->recorrida(i,j) == 0 ){
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
        cout<<"Entrada: ●"<<endl;
        cout<<"Salida: ○"<<endl;
        cout<<endl<<endl;
    }else{
        cout<<"El tamaño del laberinto es demasiado pequeño, o es 0"<<endl;
    }
    
}