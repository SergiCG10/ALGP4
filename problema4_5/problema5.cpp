#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>
#include "Laberinto.h"

using namespace std;

const static int tiempo = 100;
/**
 * @brief Función resolverLaberinto. Resuelve el laberinto pasado por parámetro
 *
 * @param laberinto. Laberinto para resolver
 * @param solucion. Vector con una solucion del laberinto
 * @param imprimirProceso. Variable que indica si se quiere imprimir el proceso de obtención del resultado, por defecto en false
 */
void resolverLaberinto(Laberinto& laberinto,vector<pair<int,int> >& solucion, vector<pair<int,int>>&recorrido , int& distanciaMin, int& distanciaActual, bool imprimirProceso = false){
    
    recorrido.push_back(laberinto.getPosicionActual());
    if(distanciaMin == laberinto.getLado() * laberinto.getLado() +1 ){
        cout<<"Distancia mínima actual: - "<<endl;
    }else{
        cout<<"Distancia mínima actual: "<<distanciaMin<<endl;
    }
    cout<<"Distancia recorrida: "<<distanciaActual<<endl;
    if(imprimirProceso){
        laberinto.imprimirLaberintoRecorrido();
        std::this_thread::sleep_for(std::chrono::milliseconds(tiempo));
        system("clear");
    }
    
    if(laberinto.esSalida() && distanciaActual < distanciaMin){
        solucion = recorrido;
        distanciaMin = distanciaActual ;
    }

    if(distanciaActual < distanciaMin && laberinto.abajo()){
        distanciaActual++;
        resolverLaberinto(laberinto, solucion, recorrido, distanciaMin, distanciaActual, imprimirProceso);
    }
        
    if(distanciaActual < distanciaMin && laberinto.derecha()){
        distanciaActual++;
        resolverLaberinto(laberinto, solucion, recorrido, distanciaMin, distanciaActual, imprimirProceso);
    }
    
    if(distanciaActual < distanciaMin && laberinto.izquierda()){
        distanciaActual++;
        resolverLaberinto(laberinto, solucion, recorrido, distanciaMin, distanciaActual, imprimirProceso);
    }
    if(distanciaActual < distanciaMin && laberinto.arriba()){
        distanciaActual++;
        resolverLaberinto(laberinto, solucion, recorrido, distanciaMin, distanciaActual, imprimirProceso);
    }

    distanciaActual--;
    laberinto.recorrida( recorrido.back().first , recorrido.back().second ) =  0;
    recorrido.pop_back();
    if(recorrido.size() > 0){
        laberinto.setPosicionActualTo( recorrido.back() );
    }else if( distanciaMin == laberinto.getLado() * laberinto.getLado() +1){
        cout<<"No hay solución"<<endl;
    }
}

int main(int argc, char * argv[] ){
    bool mostrarProceso = false;
    string archivo;

    if( argc == 2 || argc == 3){
        
        if( argc == 3){
            string aux = argv[2];
            mostrarProceso = (aux == "s" ? true : false) ;
        }
               
        Laberinto lab;
        archivo = argv[1];
        lab.loadLaberinto( archivo );
        system("clear");
        cout<<"El laberinto propuesto es: "<<endl;

        lab.imprimirLaberinto();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        system("clear");

        Laberinto sol = lab;
        vector<pair<int,int>> solucion, recorrido;
        int distanciaMin = lab.getLado() * lab.getLado() +1, distanciaActual=0;

        if(lab.getLado() > 1){
            resolverLaberinto(lab, solucion, recorrido, distanciaMin, distanciaActual , mostrarProceso);

            if( solucion.size() > 0 && lab.esSalidaPos( solucion.back() ) ){
                for(int i = 0; i < solucion.size(); i++){
                    cout<<"La solución óptima para el laberinto es:"<<endl;
                    sol.setPosicionActualTo(solucion[i]);
                    sol.imprimirLaberintoRecorrido();
                    std::this_thread::sleep_for(std::chrono::milliseconds(tiempo));
                    system("clear");
                }

                cout<<"La solución óptima para el laberinto es:"<<endl;
                sol.imprimirLaberintoRecorrido();
                cout<<endl;
            }
        }
        

    }else{
        cerr<<"Error al ejecutar. Número de parámetros erróneo."<<endl;
        cerr<<"Para ejecutar uso: ./bin/problema4.bin <archivo con laberinto> "<<endl;
        cerr<<"\topcional: s para ver el proceso de obtención del resultado\n\t\totro o nada para no verlo"<<endl;
    }
    
    return 0;
}
