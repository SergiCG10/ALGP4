#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

int SumarPreferencias (vector<pair<int,int>> & parejas, const vector<vector<int>> & preferencias)
{
    int sumalocal=0;
    for(int i=0;i<parejas.size();i++)
        sumalocal+=preferencias[parejas[i].first][parejas[i].second];
    
    return sumalocal;

}

void EncontrarParejas (const vector<vector<int>> & preferencias, const int & n, vector<pair<int,int>> & parejas, 
vector<pair<int,int>> & Candidato, vector<bool> & libres, int & maxpref)
{
    
    if(parejas.size()==Candidato.size()){
        int sumacandidato=SumarPreferencias(parejas,preferencias);
        //cout<<sumacandidato<<endl;
        if(sumacandidato>maxpref){
            maxpref=sumacandidato;
            Candidato=parejas;
   
        }
    }
    else{
        int maximo=-1,candidato=-1;
        for(int i=0;i<n;i++){
            if(libres[i]){
                for(int j=0;j<n;j++){
                    if(i!=j){   //no es el mismo estudiante y está libre
                        if(libres[j])
                        {
                            candidato=j;
                        }    
                    }
                }
                if(libres[candidato]){
                    pair<int,int> aux(i,candidato);
                    parejas.push_back(aux);
                    //cout<<"Pareja "<<i<<": "<<parejas[i].first<<" "<<parejas[i].second<<endl;
                    libres[i]=false;
                    libres[candidato]=false;
                }
                EncontrarParejas(preferencias, n, parejas, Candidato, libres, maxpref);
                parejas.pop_back();
                libres[i]=true;
                libres[candidato]=true;
            }
        }
    }

}

void ImprimeMatriz(const vector<vector<int>> & preferencias, int n)
{
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<preferencias[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void SolucionProblema1(const vector<vector<int>> & preferencias,const int & n,vector<pair<int,int>> & parejas)
{
    
    parejas.clear();
    vector<bool> libres(n,true);
    vector<pair<int,int>> Candidato(n/2);
    int max=0;
    EncontrarParejas(preferencias, n, parejas, Candidato, libres,max);
    cout<<"Se han formado las siguientes parejas"<<endl;
    for(int i=0;i<Candidato.size();i++)
        cout<<Candidato[i].first<<" y "<<Candidato[i].second<<endl;
    
    int ST=SumarPreferencias(Candidato,preferencias);
    cout<<"La satisfacción total es:"<<ST<<endl;

}




const int MAX_PREF=10;
int main(int argc, char * argv[])
{
    //filtro de argumentos
    if(argc!=3){
        cout<<"Debe de haber tres argumentos: >prompt <semilla> <num_estudiantes>"<<endl;
        return 0;
    }
    int semilla=atoi(argv[1]);
    int num_estudiantes=atoi(argv[2]);
    if(num_estudiantes%2!=0 || num_estudiantes<0)
    {
        cout<<"argv[1] debe ser un numero par"<<endl;
        return 0;
    }
    //crear la matriz nxn
    vector<vector<int>> matriz;
    matriz.resize(num_estudiantes);
    for(int i=0;i<num_estudiantes;i++)
        matriz[i].resize(num_estudiantes);

    srand(semilla);      

    for(int i=0;i<num_estudiantes;i++){//inicializar la matriz con valores random
        for(int j=0;j<num_estudiantes;j++){
            if(i==j)
                matriz[i][j]=MAX_PREF;    //asumimos que la preferencia de estar cada uno consigo mismo es máxima
            else{
                matriz[i][j]=rand()%10 +1;  //numeros entre 1 y 10
            }     
        }
    }   

    //crear matriz de preferencias (i,j)*(j,i)     
    vector<vector<int>> preferencias;
    preferencias.resize(num_estudiantes);
    
    for(int i=0;i<num_estudiantes;i++)
        preferencias[i].resize(num_estudiantes);
    for(int i=0;i<num_estudiantes;i++){
        for(int j=0;j<num_estudiantes;j++)
            preferencias[i][j]=matriz[i][j]*matriz[j][i];
    }
    cout<<"Matriz de preferencias (i,j)*(j,i):\n"<<endl;
    ImprimeMatriz(preferencias,num_estudiantes);                                                                                                
    
    vector<pair<int,int>> parejas;
    SolucionProblema1(preferencias,num_estudiantes,parejas);
    
    return 0;
}