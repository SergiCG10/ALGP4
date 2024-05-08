#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define NULL_NODE -1

typedef struct Bolivariano{
  vector<bool> estanSentados;
  vector<int> mesaAsignada;
  int indexUltimo;
} nodo;

void Inicializar(nodo&, const int&, int valor = NULL_NODE);
void AddComensal(const nodo&, nodo&, int);


pair<vector<int>,int> CI(const vector<vector<int>>& vProblema, 
    const nodo& ynodo);
pair<vector<int>,int> CS(const vector<vector<int>>& vProblema,
    const nodo& ynodo);
void PrintVector(const vector<int>& v);
void PrintMatriz(const vector<vector<int>>& matriz);
void SolucionProblema2(const vector<vector<int>>& preferencias, vector<int>& mesa);
int SumaPreferencias(const vector<vector<int>>& preferencias, const vector<int>& comensales);
void SentarComensales(const vector<vector<int>>& preferencias, vector<int>& mesa, int& maxpref);

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
  vector<bool> sentado(preferencias.size(), false);
  vector<int> candidatosol;
  int sum = 0;
  SentarComensales(preferencias, mesa, sum);
}

int SumaPreferencias(const vector<vector<int>>& preferencias, const vector<int>& comensales){
  int sum = 0;
  for(int i = 0; i < comensales.size() - 1; i++)
    sum += preferencias[comensales[i]][comensales[i+1]];
  sum += preferencias[comensales[comensales.size()-1]][comensales[0]];
  return sum;
}

pair<vector<int>,int> CI(const vector<vector<int>>& vProblema, 
    const nodo& ynodo){
  const int n = vProblema.size();
  pair<vector<int>, int> resultado;
  resultado.first = ynodo.mesaAsignada;
  vector<bool> estansentados = ynodo.estanSentados;
  int nasiento = ynodo.indexUltimo+1, inv1=0, inv2, maxconv, invelegido=ynodo.mesaAsignada[ynodo.indexUltimo]; //O(1)
  while(nasiento < n){ //O(n-1)*O(n-1) => O(n²)

    estansentados[invelegido] = true; //O(1) Hemos sentado el 0
    inv1=invelegido; //O(1) buscamos el invitado que más le conviene
                     //al comensal que acabamos de sentar
    maxconv = -1; //O(1)
    for(inv2 = 0; inv2 < n; inv2++){ //O(n-1)
      if(vProblema[inv1][inv2] > maxconv
          && !estansentados[inv2]){ //O(1) Si el comensal que más le conviene
                                    //no está sentado entonces establece ese 
                                    //como máximo, y busca si hay alguno mejor

        maxconv = vProblema[inv1][inv2]; //O(1)
        invelegido = inv2; //O(1)
      }
    }
    resultado.first[nasiento++]=invelegido; //O(1)
  }
  resultado.second = SumaPreferencias(vProblema, resultado.first);
  return resultado;
}

pair<vector<int>,int> CS(const vector<vector<int>>& vProblema,
    const nodo& ynodo){
  const int n = vProblema.size();
  pair<vector<int>,int> cota, temporal;
  nodo auxnodo;
  int mejor=0;
  for(int i = 0; i < n; i++){
    if(!ynodo.estanSentados[i]){
      AddComensal(ynodo, auxnodo, i);
      temporal = CI(vProblema, auxnodo);
      if(temporal.second > cota.second){
        cota = temporal;
        mejor = i;
      }
    }
  }
  
  nodo aux2nodo;
  AddComensal(ynodo, auxnodo, mejor);
  for(int i = 0; i < n; i++){
    if(!auxnodo.estanSentados[i]){
      AddComensal(auxnodo, aux2nodo, i);
      temporal = CI(vProblema, aux2nodo);
      if(temporal.second > cota.second){
        mejor = i;
        cota = temporal;
      }
    }
  }
  AddComensal(auxnodo, auxnodo, mejor);
  for(int i = 0; i < n; i++){
    if(!auxnodo.estanSentados[i]){
      AddComensal(auxnodo, aux2nodo, i);
      temporal = CI(vProblema, aux2nodo);
      if(temporal.second > cota.second){
        mejor = i;
        cota = temporal;
      }
    }
  }
  return cota;
}

void SentarComensales(const vector<vector<int>>& preferencias, vector<int>& mesa, int& maxpref){
  nodo ynodo, xnodo;
  pair<vector<int>,int> CotaInferior, CotaSuperior, Ctemporal;
  int i, preftemporal = 0;
  const int n = preferencias.size();
  Inicializar(ynodo, n, 0);
  CotaInferior = CI(preferencias, ynodo);
  preftemporal = CotaInferior.second;

  queue<nodo> nodos;
  for(i = 0; i < n; i++){
    Inicializar(ynodo, n, i);
    nodos.push(ynodo);
  }
  while(!nodos.empty()){
    xnodo = nodos.front(); //LNV
    nodos.pop(); //LNV - x
    if((CotaSuperior = CS(preferencias, xnodo)).second
        >= CotaInferior.second){ //CS(x) >= C
      for(i = 0; i < n; i++){
        if(!xnodo.estanSentados[i]){
          AddComensal(xnodo, ynodo, i); //For each hijo de x factible
          if(ynodo.indexUltimo == n-1 && (preftemporal = SumaPreferencias(preferencias, ynodo.mesaAsignada))
              >= CotaInferior.second){ //Es solución y es mejor que C
            CotaInferior.first = ynodo.mesaAsignada;
            CotaInferior.second = preftemporal;
          }
          else if(ynodo.indexUltimo < n-1 && (CotaSuperior = CS(preferencias, ynodo)).second
              >= CotaInferior.second){
            nodos.push(ynodo);
            Ctemporal = CI(preferencias, ynodo);
            if(Ctemporal.second > CotaInferior.second)
              CotaInferior = Ctemporal;
          }
        }
      }
    }
  }
  mesa = CotaInferior.first;
  maxpref = CotaInferior.second;
}


void Inicializar(nodo& elnodo, const int& n, int valor){
  elnodo.estanSentados.clear();
  elnodo.estanSentados.resize(n, false);
  elnodo.mesaAsignada.resize(n, -1);
  elnodo.indexUltimo = -1;
  if(valor != NULL_NODE){
    elnodo.indexUltimo++;
    elnodo.mesaAsignada[0] = valor;
    elnodo.estanSentados[valor] = true;
  }
}


void AddComensal(const nodo& padre, nodo& hijo, int invitado){
  if(padre.indexUltimo != padre.mesaAsignada.size()-1){
    if(&padre != &hijo){
      hijo.estanSentados = padre.estanSentados;
      hijo.estanSentados[invitado] = true;
      hijo.mesaAsignada = padre.mesaAsignada;
      hijo.indexUltimo = padre.indexUltimo+1;
      hijo.mesaAsignada[hijo.indexUltimo]=invitado;
    }else{
      hijo.indexUltimo = hijo.indexUltimo+1;
      hijo.mesaAsignada[hijo.indexUltimo] = invitado;
      hijo.estanSentados[invitado] = true;
    }
  }
}
