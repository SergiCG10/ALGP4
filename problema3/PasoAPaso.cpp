#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <string>
using namespace std;

//-----------------------------------------------------------------------------------
	
//DECLARACION FUNCIONES para el juego
void inicio() ;
const int FILAS = 16; 
const int COLUMNAS = 39; 
std::unordered_map<std::string, bool> memo;

//char a int
int chartoint(char caracter)
{
 int auxiliar =0;
 auxiliar = caracter-48;
 return auxiliar;
}

//mostrarmatriz
void mostrarMatriz( char matriz[][39]) 
{ 
    system("clear");
	cout<<"\n\n\n";
	for (int i=0;i<FILAS;i++) 
	{ 
		for(int j=0;j<COLUMNAS;j++) 
		{
            if(matriz[i][j] == '0')
                cout << "◉";
            else if(matriz[i][j] == '+')
                cout << "○";
            else
			    cout<<matriz[i][j];
		} 
		cout<<endl; 
	}	
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));	 
}  

//Validar GANADOR
bool validarganador(char matriz[][39]) 
{ 	
	int contador=0;
	for (int i=0;i<FILAS;i++) 
	{ 
		for(int j=0;j<COLUMNAS;j++) 
		{
			if(matriz[i][j]=='0')
			{
				contador++;
			}
		} 
	}
	if(contador==1 && matriz[7][20]=='0')
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Validar PERDEDOR
bool validarperdedor(char matriz[][39], int valor) 
{ 	
	if(valor==-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
 

//Validar datos
bool validacioningreso(char matriz[][39], int filainicio, int columnainicio, int filafinal,  int columnafinal) 
{ 
    bool res;
	//posicion inical llena (0) posicion final vacia (+)
	if((matriz[filainicio][columnainicio] == '0') && (matriz[filafinal][columnafinal] == '+') && (matriz[(filainicio + filafinal)/2][(columnainicio + columnafinal)/2] == '0'))
	{
        res = true;
    }
	else 
	{
		res = false;
	}
    return res;
}

//Mover una pieza de una posicion a otra y eliminar la ficha del medio
void mover(char matriz[][39], int filaI, int columI, int filaF, int columF){
    //esto sucede si están bien los datos introducidos
    //cambian valores de incio y final
    matriz[filaI][columI] = '+';
    matriz[filaF][columF] = '0';
    //cambia intermedio
    matriz[(filaI+filaF)/2][(columI+columF)/2] = '+';
}

//Devolver un movimiento a su estado anterior
void undoMove(char matriz[][39], int filaI, int columI, int filaF, int columF){

    matriz[filaI][columI] = '0';
    matriz[filaF][columF] = '+';
    //cambia intermedio
    matriz[(filaI+filaF)/2][(columI+columF)/2] = '0';
}

//convertimos el tablero en un string
std::string serializeBoard(char matriz[][39]) {
    std::string key;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            key.push_back(matriz[i][j]);
        }
    }
    return key;
}
//-----------------------------------------------------------------------------------

//DECLARACION FUNCIONES del juego

//Resolver con backtracking el juego
bool solve(char matriz [][39])
{
    
    std::string state = serializeBoard(matriz);
    if (memo.find(state) != memo.end()) {
        return memo[state];  // Retorna el resultado almacenado si el estado ya fue procesado
    }
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
        
            if (matriz[i][j] == '0'){
                //Si se puede mover la canica hacia abajo:
                if(validacioningreso(matriz, i, j, i+4, j)){

                    mover(matriz, i, j, i+4, j);
                    mostrarMatriz(matriz);
                    
                    if(solve(matriz)){
                        memo[serializeBoard(matriz)] = true;
                        return true;
                    }

                    undoMove(matriz, i, j, i+4, j);
                    mostrarMatriz(matriz);
                }
                //Si se puede mover la canica hacia la derecha:
                if(validacioningreso(matriz, i, j, i, j+12)){

                    mover(matriz, i, j, i, j+12);
                    mostrarMatriz(matriz);

                    if(solve(matriz)){
                        memo[serializeBoard(matriz)] = true;
                        return true;
                    }

                    undoMove(matriz, i, j, i, j+12);
                    mostrarMatriz(matriz);
                }
                //Si se puede mover la canica hacia la izquierda:
                if(validacioningreso(matriz, i, j, i-4, j)){

                    mover(matriz, i, j, i-4, j);
                    mostrarMatriz(matriz);

                    if(solve(matriz)){
                        memo[serializeBoard(matriz)] = true;
                        return true;
                    }

                    undoMove(matriz, i, j, i-4, j);
                    mostrarMatriz(matriz);
                }
                //Si se puede mover la canica hacia arriba:
                if(validacioningreso(matriz, i, j, i, j-12)){

                    mover(matriz, i, j, i, j-12);
                    mostrarMatriz(matriz);

                    if(solve(matriz)){
                        memo[serializeBoard(matriz)] = true;
                        return true;
                    }

                    undoMove(matriz, i, j, i, j-12);
                    mostrarMatriz(matriz);
                }
                if(validarganador(matriz)){
                    return true;
                }

            }
        }
    }
    memo[state] = false;
    return false;
}

//Asignar forma de juego
void inicializarTablero(int elec) { 

    char matriz[FILAS][COLUMNAS]={
        {' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '2', ' ', ' ', ' ', ' ',
            ' ', '3', ' ', ' ', ' ', ' ', ' ', '4', ' ', ' ', ' ', ' ', ' ',
            '5', ' ', ' ', ' ', ' ', ' ', '6', ' ', ' ', ' ', ' ', ' ', '7'},
        //indice arriba
        {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '+', '-', '-', '-', '-', '-', '+', '-', '-', '-', '-', '-',
            '+', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        //1
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'2', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '+', '-', '-', '-', '-', '-', '+', '-', '-', '-', '-', '-',
            '+', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        //2
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'3', ' ', '+', '-', '-', '-', '-', '-', '+', '-', '-', '-', '-',
            '-', '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-',
            '0', '-', '-', '-', '-', '-', '+', '-', '-', '-', '-', '-', '+'},
        //3
        {' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|'},
        {'4', ' ', '+', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-',
            '-', '+', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-',
            '+', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-', '+'},
        //4
        {' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|'},
        {'5', ' ', '+', '-', '-', '-', '-', '-', '+', '-', '-', '-', '-',
            '-', '0', '-', '-', '-', '-', '-', '+', '-', '-', '-', '-', '-',
            '0', '-', '-', '-', '-', '-', '+', '-', '-', '-', '-', '-', '+'},
        //5
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'6', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '+', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-',
            '+', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        //6
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'7', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '+', '-', '-', '-', '-', '-', '+', '-', '-', '-', '-', '-',
            '+', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        //7
	};

    switch(elec){

        case 0:
            break;

        case 1:
            mostrarMatriz(matriz);
            inicio();

        case 2:
            solve(matriz);
            inicio();
    }
} 

//Imprimir menu inicio
void inicio() 
{ 
	cout << "          Menú - Senku, tablero intermedio"<<endl;
	cout << "---------------------------------------------------------"<<endl;
	cout << "	1. Ver tablero intermedio"<<endl;
	cout << "	2. Resolver de forma automatica tablero intermedio"<<endl;
	cout << "---------------------------------------------------------"<<endl;
	cout << "	0. Salir del Programa\n\n";
	cout << "	Seleccionar la opcion: ";

    int elec;
    cin >> elec;
    inicializarTablero(elec);
} 


//-----------------------------------------------------------------------------------

//PRINCIPAL

int main() {
	inicio();
	return 0;
}