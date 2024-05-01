#include <cstdlib>
#include <iostream>
using namespace std;

int N = 0;

void BorrarMatriz(int **matriz){
  for(int i = 0; i < N; i++)
    delete [] matriz[i];
  delete[] matriz; 
}

bool esValidoEscribir(int **laberinto, int x, int y) {
  return (x >= 0 && x < N && y >= 0 && y < N && laberinto[x][y] == 0);
}
bool esValido(int **laberinto, int x, int y) {
  return (x >= 0 && x < N && y >= 0 && y < N && laberinto[x][y] == 1);
}

void generarCasilla(int x, int y, int **laberinto){
  if(esValido(laberinto, x, y)){
    if(esValidoEscribir(laberinto, x-1, y)){
      laberinto[x-1][y] = rand()%101 >= 50 ? 0: 1;
      generarCasilla(x-1, y, laberinto);
    }
    if(esValidoEscribir(laberinto, x+1, y)){
      laberinto[x+1][y] = rand()%101 >= 50 ? 0: 1;
      generarCasilla(x+1, y, laberinto);
    }
    if(esValidoEscribir(laberinto, x, y-1)){
      laberinto[x][y-1] = rand()%101 >= 50 ? 0: 1;
      generarCasilla(x, y-1, laberinto);
    }
    else if(esValidoEscribir(laberinto, x, y+1)){
      laberinto[x][y+1] = rand()%101 >= 50 ? 0: 1;
      generarCasilla(x, y+1, laberinto);
    }
  }
}
void generarLaberinto(int **laberinto){
  //tiene que haber una entrada y una salida
  laberinto[0][0] = 1;
  laberinto[N-1][N-1] = 1;
  generarCasilla(0, 0, laberinto);
}

bool resolverLaberintoUtil(int **laberinto, int x, int y, int** solucion) {
    if(x == N-1 && y == N-1 && laberinto[x][y] == 1) {
        solucion[x][y] = 1;
        return true;
    }
    if(esValido(laberinto, x, y)) {
        solucion[x][y] = 1;
        if (resolverLaberintoUtil(laberinto, x+1, y, solucion))
            return true;
        if (resolverLaberintoUtil(laberinto, x, y+1, solucion))
            return true;
        solucion[x][y] = 0;
        return false;
    }
    return false;
}

bool resolverLaberinto(int** laberinto) {
  int** solucion = new int*[N];
  for(int i = 0; i < N; i++){
    solucion[i] = new int[N];
    for(int j = 0; j < N; j++)
      solucion[i][j] = 0;
  }
    if(resolverLaberintoUtil(laberinto, 0, 0, solucion) == false) {
        cout << "No existe solución" << endl;
        BorrarMatriz(solucion);
        return false;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << solucion[i][j] << " ";
        cout << endl;
    }
    
    BorrarMatriz(solucion);
    return true;
}

int main() {
  while (N <= 4)
    cin >> N;
  int **laberinto;
  laberinto = new int*[N];
  for(int i = 0; i < N; i++){
    laberinto[i] = new int[N];
    for(int j = 0; j < N; j++)
      laberinto[i][j] = 0;
  }
  generarLaberinto(laberinto);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      cout << laberinto[i][j] << " ";
    cout << endl;
  }
  cout << endl << endl;
  resolverLaberinto(laberinto);
  for(int i = 0; i < N; i++)
    delete [] laberinto[i];
  delete [] laberinto;
    return 0;
}
