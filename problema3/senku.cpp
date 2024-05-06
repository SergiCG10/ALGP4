#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

//-----------------------------------------------------------------------------------

struct Movimiento {
    int i_start, j_start; // Posición inicial de la ficha
    int i_end, j_end;     // Posición final de la ficha

    Movimiento(int is, int js, int ie, int je) : i_start(is), j_start(js), i_end(ie), j_end(je) {
        ;
    }
};

//DECLARACION FUNCIONES para el juego
void inicio() ;
const int FILAS = 16; 
const int COLUMNAS = 39; 
std::unordered_map<std::string, bool> memo;
std::vector<Movimiento> movimientos;

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

//-----------------------------------------------------------------------------------

//DECLARACION FUNCIONES del juego

void printSolucion(char matriz[][39]){
    for(int i = 30 ; i >=0  ; i--){
        mover(matriz, movimientos[i].i_start, movimientos[i].j_start, movimientos[i].i_end, movimientos[i].j_end);
        system("clear");
        mostrarMatriz(matriz);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

std::string serializeBoard(char matriz[][39]) {
    std::string key;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            key.push_back(matriz[i][j]);
        }
    }
    return key;
}

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
                
                //mueve, si puede, la ficha hacia abajo
                if(validacioningreso(matriz, i, j, i+4, j)){

                    mover(matriz, i, j, i+4, j);
                    
                    if(solve(matriz)){
                        memo[serializeBoard(matriz)] = true;
                        movimientos.emplace_back(i, j, i+4, j);
                        return true;
                    }
                    
                    undoMove(matriz, i, j, i+4, j);
                    if (!movimientos.empty()) {
                        movimientos.pop_back();  // Elimina el último movimiento porque no condujo a una solución
                    }
                
                }

                //mueve, si puede, la ficha hacia la derecha
                if(validacioningreso(matriz, i, j, i, j+12)){

                    mover(matriz, i, j, i, j+12);

                    if(solve(matriz)){
                        memo[serializeBoard(matriz)] = true;
                        movimientos.emplace_back(i, j, i, j+12);
                        return true;
                    }

                    undoMove(matriz, i, j, i, j+12);
                    if (!movimientos.empty()) {
                        movimientos.pop_back();  // Elimina el último movimiento porque no condujo a una solución
                    }                
                }

                //mueve, si puede, la ficha hacia arriba
                if(validacioningreso(matriz, i, j, i-4, j)){

                    mover(matriz, i, j, i-4, j);

                    if(solve(matriz)){
                        memo[serializeBoard(matriz)] = true;
                        movimientos.emplace_back(i, j, i-4, j);
                        return true;
                    }

                    undoMove(matriz, i, j, i-4, j);
                    if (!movimientos.empty()) {
                        movimientos.pop_back();  // Elimina el último movimiento porque no condujo a una solución
                    }
                }

                //mueve, si puede, la ficha hacia la izquierda
                if(validacioningreso(matriz, i, j, i, j-12)){

                    mover(matriz, i, j, i, j-12);

                    if(solve(matriz)){
                        memo[serializeBoard(matriz)] = true;
                        movimientos.emplace_back(i, j, i, j-12);
                        return true;
                    }

                    undoMove(matriz, i, j, i, j-12);
                    if (!movimientos.empty()) {
                        movimientos.pop_back();  // Elimina el último movimiento porque no condujo a una solución
                    }
                }
                
                //comprueba si el tablero está en estado ganador
                if(validarganador(matriz)){
                    cout << "\n\nResuelto: \n\n";
                    mostrarMatriz(matriz);
                    cout << "\nMostrando el resultado obtenido: " << endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(3500));
                    return true;
                }

            }
        }
    }
    memo[state] = false;
    return false;
}

//Empezar a jugar
void juego(char matriz[][39]) 
{ 
	int ganar = 0;
	//mostrado de tablero
    	mostrarMatriz(matriz);
	while(ganar == 0)
	{
		//ingreso datos
		char cadenainicio[5];
		char cadenafinal[5];
		int filainicio,filafinal,columnainicio,columnafinal;
		cout<<"Si desea reiniciar el juego o ya no posees jugadas "; 
		cout<<"posibles, poner 00000 en los dos valores a solicitar.";
		cout<<"\nIngrese la posicion de origen con el formato (fila,columna):";
		cin>>cadenainicio;
		cout<<"\nIngrese la posicion de decision con el formato (fila,columna):";
		cin>>cadenafinal;
		filainicio=chartoint(cadenainicio[1])*2-1;
		columnainicio=chartoint(cadenainicio[3])*6-4;
		filafinal=chartoint(cadenafinal[1])*2-1;
		columnafinal=chartoint(cadenafinal[3])*6-4;

        //cout << "inicio: " << filainicio << " " << columnainicio;
        //cout << "final: " << filafinal << " " << columnafinal;

		//verificar si perdio
		if(validarperdedor(matriz,filainicio))
		{	
    		cout << "\n\n\nPERDISTEEEEEEEEEEEEEEE!\n\n\n";
    		ganar=1;
		}
		else
		{
			//validacion de datos 
			if( validacioningreso(matriz,filainicio,columnainicio,filafinal,columnafinal) )
			{
	    		mover(matriz, filainicio, columnainicio, filafinal, columnafinal);
			}

			else
			{
				//esto sucede si estan mal los datos ingresados
	    		cout << "\n\nJugada invalida\n\n";
			}
			
			//verificar si gano
			if(validarganador(matriz))
			{
                mostrarMatriz(matriz);
	    		cout << "\n\n\nGANASTEEEEEEEEEEEEEEE!\n\n\n";
	    		ganar=1;
			}
			else
			{
				//mostrado de tablero
	    		mostrarMatriz(matriz);
			}
		}
		
	}
	inicio();	
} 


//Asignar forma de juego
void inicializarTablero(int elec) { 

    char copia[FILAS][COLUMNAS], matriz[FILAS][COLUMNAS]={
        {' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '2', ' ', ' ', ' ', ' ',
            ' ', '3', ' ', ' ', ' ', ' ', ' ', '4', ' ', ' ', ' ', ' ', ' ',
            '5', ' ', ' ', ' ', ' ', ' ', '6', ' ', ' ', ' ', ' ', ' ', '7'},
        //indice arriba
        {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-',
            '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        //1
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'2', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-',
            '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        //2
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'3', ' ', '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-',
            '-', '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-',
            '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-', '0'},
        //3
        {' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|'},
        {'4', ' ', '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-',
            '-', '0', '-', '-', '-', '-', '-', '+', '-', '-', '-', '-', '-',
            '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-', '0'},
        //4
        {' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|'},
        {'5', ' ', '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-',
            '-', '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-',
            '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-', '0'},
        //5
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'6', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-',
            '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        //6
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
            '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'7', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', '0', '-', '-', '-', '-', '-', '0', '-', '-', '-', '-', '-',
            '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        //7
	};

    switch(elec){

        case 0:
            break;

        case 1:
            juego(matriz);

        case 2:
            for (int i = 0; i < FILAS; i++) 
                for (int j = 0; j < COLUMNAS; j++) 
                    copia[i][j] = matriz[i][j];
            solve(matriz);
            printSolucion(copia);
    }
} 

//Imprimir menu inicio
void inicio() 
{ 
	cout << "                  Menú - Juego Senku"<<endl;
	cout << "---------------------------------------------------------"<<endl;
	cout << "	1. Jugar"<<endl;
	cout << "	2. Resolver de forma automatica"<<endl;
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