#include <iostream>
#include "Laberinto.h"

using namespace std;

int main( int argc, char* argv[] ){

    Laberinto l;
    int opcion;
    bool almacenado = false;
    string directorioGuardado;
    string aux;
    string nombre;

    if( argc != 2 && argc != 1){
        cerr<<"Error. Parámetros incorrectos."<<endl;
        cerr<<"Uso: ./generarLaberintos"<<endl;
        cerr<<"opcional: <nombreDelDirectorioDeGuardado>";
    }
    if(argc == 2){
        directorioGuardado = argv[1];
    }else{
        directorioGuardado = "problema4_5/laberintos";
    }
    
    do{
        cout<<"Que desea hacer?"<<endl;
        cout<<"\t1: crear un laberinto"<<endl;
        cout<<"\t2: editar el laberinto almacenado"<<endl;    
        cout<<"\t3: guardar el laberinto almacenado"<<endl;
        cout<<"\t4: cargar un laberinto almacenado"<<endl;
        cout<<"\t5: imprimir el laberinto almacenado"<<endl;
        cout<<"\t6: cambiar el directorio donde guardar"<<endl;
        cout<<"\totro: terminar"<<endl;
        cin>>opcion;
        switch (opcion){
            case 1:
                cout<<"De que tamaño desea crear el laberinto"<<endl;
                int lado;
                cin>>lado;

                while(lado <= 0){
                    cout<<"El valor del lado no puede ser menor que 0\t";
                    cin>>lado;
                }

                almacenado = true;
                l = Laberinto(lado);

                int i,j;

                do{
                    cout<<"¿Que posición desea hacer muro? (-1 para terminar) \t";
                    cin>>i;
                    while( i < -1 && i >= l.getLado()){
                        cout<<"Numero de fila errónea, vuelva a introducir:\t";
                        cin>>i;
                    }
                    if(i != -1){
                        cin>>j;
                        while( j < -1 && j >= l.getLado()){
                            cout<<"Numero de columna errónea, vuelva a introducir:\t";
                            cin>>j;
                        }  
                        cout<<"El valor de la posicion"<<i<<","<<j<<" pasará a ser "<<0<<endl;
                        l.setPosicion(i,j);

                    }
                    
                }while(i != -1);
                break;
            case 2:
                int f,c;
                if(almacenado){
                    do{
                        cout<<"¿Que posición desea cambiar? (-1 para terminar) \t";
                        cin>>f;
                        while( f < -1 && f >= l.getLado()){
                            cout<<"Numero de fila errónea, vuelva a introducir:\t";
                            cin>>f;
                        } 
                        if(f != -1){
                            cin>>c;
                            while( c < -1 && c >= l.getLado()){
                                cout<<"Numero de columna errónea, vuelva a introducir:\t";
                                cin>>c;
                            }
                            bool valor = l.getPosicion(f,c) == 0 ? 1 : 0;  
                            cout<<"El valor de la posicion"<<f<<","<<c<<" pasará a ser "<<valor<<endl;
                            l.setPosicion(f,c, valor);

                        }
                        
                    }while(f != -1);
                }else{
                    cout<<"No hay ningún laberinto almacenado"<<endl;
                }
                
                break;
            case 3:
                aux = directorioGuardado;
                cout<<"¿Como desea que se llame el fichero donde va a guardar el laberinto?";
                cin>>nombre;
                aux += "/" + nombre;

                l.saveLaberinto( aux );
                break;
            case 4:
                aux = directorioGuardado;
                cout<<"¿Como se llama el fichero de donde va a copiar el laberinto?";
                cin>>nombre;
                aux += "/" + nombre;

                l.loadLaberinto( aux );
                almacenado = true;
                break;
            case 5:
                l.imprimirLaberinto();
                break;
            case 6:
                cout<<"Introduzca la nueva carpeta donde guardar: \t";
                cin>>directorioGuardado;
                break;
            default :
                opcion = -1;
        }
    }while(opcion >0 && opcion <7);
}