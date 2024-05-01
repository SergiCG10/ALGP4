#include <iostream>
#include <vector>
using namespace std;

#define N 4

bool esValido(int laberinto[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && laberinto[x][y] == 1);
}

bool resolverLaberintoUtil(int laberinto[N][N], int x, int y, int solucion[N][N]) {
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

bool resolverLaberinto(int laberinto[N][N]) {
    int solucion[N][N] = { { 0, 0, 0, 0 },
                           { 0, 0, 0, 0 },
                           { 0, 0, 0, 0 },
                           { 0, 0, 0, 0 } };
    if(resolverLaberintoUtil(laberinto, 0, 0, solucion) == false) {
        cout << "No existe solución";
        return false;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << solucion[i][j] << " ";
        cout << endl;
    }
    return true;
}

int main() {
    int laberinto[N][N] = { { 1, 0, 0, 0 },
                            { 1, 1, 0, 1 },
                            { 0, 1, 0, 0 },
                            { 1, 1, 1, 1 } };
    resolverLaberinto(laberinto);
    return 0;
}
