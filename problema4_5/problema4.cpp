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
void resolverLaberinto(Laberinto& laberinto,vector<pair<int,int> >& solucion, bool imprimirProceso){
    
    solucion.push_back(laberinto.getPosicionActual());

    if(imprimirProceso){
        laberinto.imprimirLaberintoRecorrido();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("clear");
    }
    
    if(!laberinto.salida() && laberinto.abajo()){
        resolverLaberinto(laberinto, solucion, imprimirProceso);
    }
        
    if(!laberinto.salida() && laberinto.derecha()){
        resolverLaberinto(laberinto, solucion, imprimirProceso);
    }
    
    if(!laberinto.salida() && laberinto.izquierda()){
        resolverLaberinto(laberinto, solucion, imprimirProceso); 
    }
    if(!laberinto.salida() && laberinto.arriba()){
        resolverLaberinto(laberinto, solucion, imprimirProceso);
    }

    if( !laberinto.salida()){
        solucion.pop_back();
        if(solucion.size() > 0){
            laberinto.setPosicionActualTo( solucion.back().first,  solucion.back().second );
        }else{
            cerr<<"No hay solución"<<endl;
        }
    } 
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
            resolverLaberinto(lab, solucion, mostrarProceso);
           
            for(int i = 0; i < solucion.size(); i++){
                cout<<"Una solución al laberinto es:"<<endl;
                sol.setPosicionActualTo( solucion[i].first, solucion[i].second);
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
