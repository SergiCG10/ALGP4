#include <iostream>

#include "Laberinto.h"

using namespace std;

/**
 * @brief Funcion SkipWhitespaces. Funcion auxiliar para saltarnos los espacios
 */
char SkipWhitespaces (ifstream& f){
  char c;
  do{
    c= f.get();
  } while (isspace(c));
  f.putback(c);
  return c;
}
/**
 * @brief Funcion readHeader. Funcion auxiliar para leer la cabecera de las imagenes de los laberintos
 */
bool ReadHeader (ifstream& f, int& lado){
    int aux, aux2;
    string linea;
    while (SkipWhitespaces(f)=='#')
      f.ignore(10000,'\n');
    
    f >> aux >> aux2;
    lado = aux;
    cout<<aux<<endl;
    cout<<aux2<<endl;
    if (f && lado>0 && lado<5000 ){
        f.get(); // Saltamos separador
        return true;
    }else 
      return false;
}

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
    if(valor == false){
        recorridos[f][c] = -1;
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
    cout<<"Constructor de copia";
    this->lado = lab.getLado();
    inicializar(lado);
    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            this->setPosicion(i,j, lab.getPosicion(i,j));
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
    cout<<"Operador de asignación";
    liberar();
    this->lado = lab.getLado();
    inicializar(lado);
    for(int i = 0; i < lado; i++){
        for(int j = 0; j <lado; j++){
            setPosicion(i,j, lab.getPosicion(i,j));
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
    posible = (posicionActual.first -1 < 0 ) ? false : getPosicion(posicionActual.first - 1 , posicionActual.second ) && recorrida(posicionActual.first - 1, posicionActual.second) != 1;

    if(posible){
        setPosicionActualTo(posicionActual.first - 1, posicionActual.second);
        recorrida(posicionActual.first, posicionActual.second ) = 1;
    }

    return posible;
}

bool Laberinto::abajo(){
    bool posible = false;
    posible = (posicionActual.first +1 >= this->getLado() ) ? false : getPosicion(posicionActual.first + 1 , posicionActual.second )&& recorrida(posicionActual.first + 1, posicionActual.second) != 1;

    if(posible){
        setPosicionActualTo(posicionActual.first + 1, posicionActual.second);
        recorrida(posicionActual.first, posicionActual.second ) = 1;
    }

    return posible;
}

bool Laberinto::izquierda(){
    bool posible = false;
    posible = (posicionActual.second -1 < 0) ? false : getPosicion(posicionActual.first, posicionActual.second - 1 )&& recorrida(posicionActual.first, posicionActual.second-1) != 1;

    if(posible){
        setPosicionActualTo(posicionActual.first, posicionActual.second -1 );
        recorrida(posicionActual.first, posicionActual.second ) = 1;
    }

    return posible;
}

bool Laberinto::derecha(){
    bool posible = false;
    posible = (posicionActual.second +1 >= this->getLado() ) ? false : getPosicion(posicionActual.first, posicionActual.second + 1 )&& recorrida(posicionActual.first, posicionActual.second + 1) != 1;

    if(posible){
        setPosicionActualTo(posicionActual.first, posicionActual.second +1);
        recorrida(posicionActual.first, posicionActual.second ) = 1;
    }

    return posible;
}

bool Laberinto::salida(){
    return ( posicionActual.first == this->getLado() -1 ) && ( posicionActual.second = this->getLado()-1 );
}


void Laberinto::loadLaberinto(const char *fichero){
    liberar();
    unsigned char *res=0;
    int l =0;
    ifstream f(fichero);
        
    if (ReadHeader(f, l)){
      res= new unsigned char[l*l];
      f.read(reinterpret_cast<char *>(res),l*l);
      if (!f){
        delete[] res;
        res= 0;
        cout<<"Fallo en lectura"<<endl;
      }
    }else{
        cout<<"Valor erróneo de la imagen"<<endl;
    }
    inicializar(l);
    this->lado = l;
    unsigned char** imagen = new unsigned char * [this->getLado()];
    imagen[0] = new unsigned char [this->getLado() * this->getLado()];
    for (int i=1; i < this->getLado(); i++)
        imagen[i] = imagen[i-1] + this->getLado();

    imagen[0] = res;

    
    
    for(int i =0; i< this->getLado(); i++){
        for(int j =0; j < this->getLado(); j++){
            if( imagen[i][j] = 1){
                this->setPosicion(i,j, true);
            }else{
                this->setPosicion(i,j, false);
            }
        }
    }
    delete[] imagen[0];
    delete[] imagen;
}


void Laberinto::saveLaberinto(const char* fichero){

    unsigned char** imagen = new unsigned char * [this->getLado()];
    imagen[0] = new unsigned char [this->getLado() * this->getLado()];
    for (int i=1; i < this->getLado(); i++)
        imagen[i] = imagen[i-1] + this->getLado();

    for(int i = 0; i < getLado(); i++){
        for(int j = 0; j < getLado(); j++){
            if( this->getPosicion(i,j) == false){
                imagen[i][j] = 0;
            }else{
                imagen[i][j] = 1;
            }
        }
    }
    ofstream salida(fichero, ios::binary);
    
    if (salida){
        salida << "P4" << endl;
        salida << this->getLado() << ' ' << this->getLado() << endl;
        salida << 1 << endl;

        salida.write(reinterpret_cast<const char *>(imagen),this->getLado()*this->getLado());
    }
    salida.close();
    delete[] imagen[0];
    delete[] imagen;
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
    }else{
        cout<<"El tamaño del laberinto es demasiado pequeño, o es 0"<<endl;
    }
    
}