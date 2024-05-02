#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>
#include "Laberinto.h"

using namespace std;

/**
 * @brief Función resolverLaberinto. Resuelve el laberinto pasado por parámetro
 *
 * @param laberinto. Laberinto para resolver
 * @param solucion. Vector con una solucion del laberinto
 * @param imprimirProceso. Variable que indica si se quiere imprimir el proceso de obtención del resultado, por defecto en false
 */
void resolverLaberinto(Laberinto& laberinto,vector<pair<int,int> >& solucion, bool imprimirProceso,int act, int distancia){
    
    solucion.push_back(laberinto.getPosicionActual());

    if(imprimirProceso){
        laberinto.imprimirLaberintoRecorrido();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("clear");
    }
    
    if(!laberinto.salida() && laberinto.abajo() && act!=distancia){
        act++;
         resolverLaberinto(laberinto, solucion, imprimirProceso,act,distancia);
    }
        
    if(!laberinto.salida() && laberinto.derecha() && act!=distancia){
        act++;
          resolverLaberinto(laberinto, solucion, imprimirProceso,act,distancia);
    }
    
    if(!laberinto.salida() && laberinto.izquierda() && act!=distancia){
        act++;
         resolverLaberinto(laberinto, solucion, imprimirProceso,act,distancia); 
    }
    if(!laberinto.salida() && laberinto.arriba() && act!=distancia ){
        act++;
         resolverLaberinto(laberinto, solucion, imprimirProceso,act,distancia);
    }
 
    
    

    if( !laberinto.salida()){
        solucion.pop_back();
        if(solucion.size() > 0){
            laberinto.setPosicionActualTo( solucion.back() );
        }else{
            cerr<<"No hay solución"<<endl;
        }
    } 
}

void start(Laberinto& laberinto, vector<pair<int, int> >& solucion, bool imprimirProceso) {
    int distancia = laberinto.Max_tamano()+laberinto.Max_tamano()-1;
    distancia = 1000;
    int act=0;
    resolverLaberinto(laberinto, solucion, imprimirProceso,act,distancia);
    cout << distancia;
}




int main(int argc, char * argv[] ){
    bool mostrarProceso = false;
    string directorioGuardado = "problema4_5/laberintos";
    string archivo;

    if( argc == 2 || argc == 3){
        
        if( argc == 3){
            string aux = argv[2];
            mostrarProceso = (aux == "s" ? true : false) ;
        }
        
        vector<pair<int,int>> solucion;
        
        Laberinto lab;
        archivo = argv[1];
        directorioGuardado += "/" + archivo;
        lab.loadLaberinto( directorioGuardado );
        
        cout<<"El laberinto propuesto es: "<<endl;

        lab.imprimirLaberinto();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        system("clear");

        Laberinto sol = lab;

        if(lab.getLado() > 1){
            //resolverLaberinto(lab, solucion, mostrarProceso);
            start(lab, solucion, mostrarProceso);
            for(int i = 0; i < solucion.size(); i++){
                cout<<"Una solución al laberinto es:"<<endl;
                sol.setPosicionActualTo(solucion[i]);
                sol.imprimirLaberintoRecorrido();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                system("clear");
            }

            cout<<"Una solución al laberinto es:"<<endl;
            sol.imprimirLaberintoRecorrido();
            cout<<endl;
        }
        

    }else{
        cerr<<"Error al ejecutar. Número de parámetros erróneo."<<endl;
        cerr<<"Para ejecutar uso: ./bin/problema4.bin <archivo con laberinto> "<<endl;
        cerr<<"\topcional: s para ver el proceso de obtención del resultado\n\t\totro o nada para no verlo"<<endl;
    }
    
    return 0;
}


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
int Laberinto::Max_tamano(){
    return lado;
}   




#ifndef Laberinto
#define _LABERINTO

#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief Clase Laberinto. Utilizada para representar un laberinto con funciones auxiliares para su construcción y resolución
 *
 * @param laberinto. Matriz booleana que contendrá el laberinto (cuadrada según el enunciado). True para valores donde se puede pasar, false para los que no
 * @param recorridos. Matriz del mismo tamaño que el laberinto que indica si las casillas han sido recorridas o no, 0 para no, 1 para sí, -1 si son un muro
 * @param lado. Lado del laberinto cuadrado
 * @param posicionActual. Posicion actual del recorrido
 */
class Laberinto{
    private:

        bool** laberinto;
        int** recorridos;
        int lado;
        pair<int,int> posicionActual;

        /**
         * @brief Funcion privada inicializar. Inicializa el laberinto con f filas y columnas
         *
         * @param l. Lado de la matriz cuadrada
         */
        void inicializar(int l);

        /**
         * @brief Funcion liberar. Libera la memoria de la matriz
         */
        void liberar();

    public:    

        /**
         * @brief Constructor por defecto de la clase laberinto. Crea un laberinto vacío, con 0 filas y 0 columnas
         */
        Laberinto();

        /**
         * @brief Constructor por parámetro de la clase laberinto. Crea un laberinto con f filas y c columnas, con todas las posiciones a true (recorribles)
         *
         * @param l. Lado de la matriz cuadrada
         *
         */
        Laberinto(int l);

        /**
         * @brief Funcion getLado. Devuelve el tamaño del lado de la matriz cuadrada
         */
        int getLado() const;

        /**
         * @brief Funcion posicion. Devuelve la posicion actual. Función getter
         */
        const pair<int,int>& getPosicionActual() const;

        /**
         * @brief Funcion posicion. Establece la posicion actual. Función setter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        void setPosicionActualTo(pair<int,int> p);

        /**
         * @brief Funcion posicion. Devuelve el valor de una casilla (f,c). Función getter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        const bool& getPosicion(int f, int c) const;

        /**
         * @brief Funcion posicion. Establece el valor de una casilla (f,c). Función setter
         * Si el valor el false (una pared), en la matriz de recorridos lo ponemos como -1, si es al contrario
         * lo ponemos a 0 (camino)
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         * @param valor. Valor para la posición
         */
        void setPosicion(int f, int c, bool valor = false);

        /**
         * @brief Funcion recorrida. Devuelve si una casilla (f,c) ha sido recorrida  o es pared (0 no recorrida, 1 si recorrida, -1 es pared). Función getter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        const int& recorrida(int f, int c) const;

        /**
         * @brief Funcion recorrido. Devuelve si una casilla (f,c) ha sido recorrida o es pared (0 no recorrida, 1 si recorrida, -1 es pared). Función setter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        int& recorrida(int f, int c);

        /**
         * @brief Constructor de copia de la clase laberinto. Crea un laberinto a partir de otro.
         *
         * @param lab. Laberinto del que copiar el nuestro
         */
        Laberinto(const Laberinto& lab);

        /**
         * @brief Operador de asignación, copia un laberinto en otro.   
         *
         * @param lab. Laberinto del que copiar el nuestro
         */
        Laberinto& operator = (const Laberinto& lab);

        /**
         * @brief Funcion arriba. Devuelve si a partir de la posición actual podemos ir hacia arriba, en caso afirmativo, la posición actual cambia
         */
        bool arriba();

        /**
         * @brief Funcion arriba. Devuelve si a partir de la posición actual podemos ir hacia abajo, en caso afirmativo, la posición actual cambia
         */ 
        bool abajo(); 

        /**
         * @brief Funcion izquierda. Devuelve si a partir de la posición actual podemos ir hacia la izquierda, en caso afirmativo, la posición actual cambia
         */
        bool izquierda(); 

        /**
         * @brief Funcion derecha. Devuelve si a partir de la posición actual podemos ir hacia la derecha, en caso afirmativo, la posición actual cambia
         */
        bool derecha();

        /**
         * @brief Funcion salida. Determina si estás en la salida o no a partir de la posicion actual
         */
        bool salida();

        /**
         *
         */
        void loadLaberinto(string fichero);

        /**
         *
         */
        void saveLaberinto(string fichero);
        /**
         * @brief Funcion imprimirLaberinto. Imprime el laberinto por pantalla
         */
        void imprimirLaberinto();

        void imprimirLaberintoRecorrido();
        int Max_tamano();
};

#endif 

