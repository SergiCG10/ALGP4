#include <iostream>
#include <vector>
using namespace std;

void PrintVector(const vector<int>& v);
void PrintMatriz(const vector<vector<int>>& matriz);
void SolucionProblema2(const vector<vector<int>>& preferencias, vector<int>& mesa);
int SumaPreferencias(const vector<vector<int>>& preferencias, const vector<int>& comensales);
void SentarComensales(const vector<vector<int>>& preferencias, vector<int>& mesa, vector<int>& candidato,
    bool sentado[], int index, int& maxpref);

int main (int argc, char *argv[]) {
  vector<vector<int>> vProblema;
  vector<int> mesa;
  int n, i, argumento, simetria=1;
  unsigned long int semilla;

  if (argc != 3){
    cerr << "\nError: El programa se debe ejecutar de la siguiente forma. \n\n";
    cerr << argv[0] << " Semilla tamCaso\n\n";
    return -1;
  }

  semilla = atoi(argv[1]);
  srand(semilla);

  n = atoi(argv[2]);
  vProblema.resize(n);
  for(i = 0; i < n; i++)
    vProblema[i].resize(n);

  for(i = 0; i < n; i++)
    vProblema[i][i] = 100;

  for(i = 0; i < n; i++, simetria++){
    for(int j = simetria; j < n; j++){
      vProblema[i][j] = rand()%101;
      vProblema[j][i] = vProblema[i][j];
    }
  }

  cout << "Matriz de las conveniencias de los comensales:" << endl;
  PrintMatriz(vProblema);
  cout << "Buscando solución..." << endl;
  SolucionProblema2(vProblema, mesa);

  cout << "En la mesa se sentarán los comensales de la siguiente manera:" << endl;
  PrintVector(mesa);
  cout << "Con una preferencia de: " << SumaPreferencias(vProblema, mesa) << endl;
  return 0;
}

void PrintVector(const vector<int>& v){
  if(v.empty())
    return;
  for(int elem: v)
    cout << elem << " ";
  cout << endl;
}

void PrintMatriz(const vector<vector<int>>& matriz){
  if(matriz.empty())
    return;
  for(vector<int> fila: matriz)
    PrintVector(fila);
}

void SolucionProblema2(const vector<vector<int>>& preferencias, vector<int>& mesa){
  mesa.clear();
  bool* sentado = new bool[preferencias.size()];
  vector<int> candidatosol;
  mesa.resize(preferencias.size());
  for(int i = 0; i < preferencias.size(); i++){
    mesa[i] = i;
    sentado[i] = false;
  }
  int preferencia_mayor = SumaPreferencias(preferencias, mesa);
  SentarComensales(preferencias, mesa, candidatosol, sentado, 0, preferencia_mayor);
  delete[] sentado;
}

int SumaPreferencias(const vector<vector<int>>& preferencias, const vector<int>& comensales){
  int sum = 0;
  for(int i = 0; i < comensales.size() - 1; i++)
    sum += preferencias[comensales[i]][comensales[i+1]];
  sum += preferencias[comensales[comensales.size()-1]][comensales[0]];
  return sum;
}

void SentarComensales(const vector<vector<int>>& preferencias, vector<int>& mesa, vector<int>& candidato,
    bool sentado[], int index, int& maxpref){
  if(candidato.size() == mesa.size()){ //Si la mesa candidata ha sentado a todos los comensales, comparamos
    int preferenciaCandidato = SumaPreferencias(preferencias, candidato);
    if(preferenciaCandidato > maxpref){
      mesa = candidato;
      maxpref = preferenciaCandidato;
    }
  }
  else{
    for(int i = 0; i < mesa.size(); i++){
      if(!sentado[i]){ //Si no es el mismo y no está sentado
        candidato.push_back(i); //Sentamos al comensal
        sentado[i] = true; //se ha sentado al comensal
        SentarComensales(preferencias, mesa, candidato, sentado, i, maxpref);
        candidato.pop_back();
        sentado[i] = false;
      }
    }
  }
}
